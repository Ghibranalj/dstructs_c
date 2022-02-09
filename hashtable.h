#pragma once

// TODO make the key generic
// #ifndef LL_KEY_TYPE
// #error LL_KEY_TYPE not defined
// #endif

#ifndef HT_VALUE_TYPE
#error HT_VALUE_TYPE not defined
#endif

#include "generic.h"
#include <string.h>

#define TABLE_SIZE 10000
typedef struct tableentry {
    char *key;
    HT_VALUE_TYPE *value;

    struct tableentry *next;
} tableentry;

typedef struct hashtable {
    tableentry **entries;
} hashtable;

#define TABLE_SIZE 10000

#define HASHTABLE ht_create

unsigned int __hash(const char *key) {
    unsigned long int value = 0;
    int keyLen = strlen(key);

    for (unsigned int i = 0; i < keyLen; i++) {
        value = value * 16 + key[i];
    }

    value = value % TABLE_SIZE;

    return value;
}

hashtable *ht_create() {
    hashtable *ht = malloc(sizeof(hashtable));

    ht->entries = malloc(TABLE_SIZE * sizeof(tableentry));

    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->entries[i] = NULL;
    }

    return ht;
}

tableentry *createEntry(const char *key, HT_VALUE_TYPE value) {

    tableentry *entry = malloc(sizeof(tableentry));

    entry->key = malloc(strlen(key) + 1);

    HT_VALUE_TYPE * val = malloc(sizeof(HT_VALUE_TYPE));
    *val = value;
    entry->value = val;

    strcpy(entry->key, key);
    *entry->value = value;

    entry->next = NULL;
    return entry;
}

void freeEntry(tableentry *entry) {
    free(entry->key);
    free(*entry->value);
    free(entry->value);
    free(entry);
}

void ht_free(hashtable *table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        tableentry *entry = table->entries[i];
        while (entry != NULL) {
            freeEntry(entry);
            entry = entry->next;
        }
    }
    free(table->entries);
    free(table);
}

void ht_set(hashtable *ht, const char *key, HT_VALUE_TYPE value) {

    unsigned int slot = __hash(key);

    tableentry *entry = ht->entries[slot];

    if (entry == NULL) {
        ht->entries[slot] = createEntry(key, value);
        return;
    }

    // find a match then change it to the new value
    tableentry *prev;
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            free(entry->value);
            entry->value = malloc(sizeof(HT_VALUE_TYPE));
            *entry->value = value;
            return;
        }

        // walk
        prev = entry;
        entry = entry->next;
    }

    // theres no match create new next
    prev->next = createEntry(key, value);
}

HT_VALUE_TYPE *GetHT(hashtable *ht, const char *key) {
    unsigned int slot = __hash(key);

    tableentry *entry = ht->entries[slot];

    if (entry == NULL) {
        return NULL;
    }

    // walk through entries
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    // theres no match;
    return NULL;
}

void ht_del(hashtable *ht, const char *key) {
    unsigned int slot = __hash(key);

    tableentry *entry = ht->entries[slot];

    if (entry == NULL) {
        return;
    }

    tableentry *prev = NULL;

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {

            // one and only entry
            if (entry->next == NULL && prev == NULL) {
                // just delete
                freeEntry(entry);
                ht->entries[slot] = NULL;
            }

            // no prev has next
            if (prev == NULL && entry->next != NULL) {
                ht->entries[slot] = entry->next;
                freeEntry(entry);
            }

            // has prev no next
            if (entry->next == NULL && prev != NULL) {
                freeEntry(entry);
                ht->entries[slot] = NULL;
                prev->next = NULL;
            }

            // has prev has next
            if (entry->next != NULL && prev != NULL) {
                tableentry *next = entry->next;
                prev->next = next;
                freeEntry(entry);
            }

            return;
        }

        prev = entry;
        entry = entry->next;
    }
}

void ht_dump(hashtable *ht) {
    for (int i = 0; i < TABLE_SIZE; ++i) {

        tableentry *entry = ht->entries[i];

        if (entry == NULL)
            continue;

        while (entry != NULL) {
            //TODO change that to generic
            printf("(%s,%s) ", entry->key, *entry->value);
            entry = entry->next;
        }
        printf("\n");
    }
}

HT_VALUE_TYPE ht_get(hashtable *ht, const char *key) {
  unsigned int slot = __hash(key);

  tableentry *entry = ht->entries[slot];

  if (entry == NULL) {
    return NULL;
  }

  // walk through entries
  while (entry != NULL) {
    if (strcmp(entry->key, key) == 0) {
      return *entry->value;
    }
    entry = entry->next;
  }
  // theres no match;
  return NULL;
}


#undef TABLE_SIZE