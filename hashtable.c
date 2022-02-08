#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "hashtable.h"


#define TABLE_SIZE 10000

tableEntry *createEntry(const char *key, const char *value);
void freeEntry(tableEntry *entry);
// void appendEntry(tableEntry *entry, tableEntry *next);

unsigned int hash(const char *key) {
  unsigned long int value = 0;
  int keyLen = strlen(key);

  for (unsigned int i = 0; i < keyLen; i++) {
    value = value * 16 + key[i];
  }

  value = value % TABLE_SIZE;

  return value;
}

HashTable *CreateHT() {
  HashTable *ht = malloc(sizeof(HashTable));

  ht->entries = malloc(TABLE_SIZE * sizeof(tableEntry));

  for (int i = 0; i < TABLE_SIZE; i++) {
    ht->entries[i] = NULL;
  }

  return ht;
}

void SetHT(HashTable *ht, const char *key, const char *value) {

  unsigned int slot = hash(key);

  tableEntry *entry = ht->entries[slot];

  if (entry == NULL) {
    ht->entries[slot] = createEntry(key, value);
    return;
  }

  // find a match then change it to the new value
  tableEntry *prev;
  while (entry != NULL) {
    if (strcmp(entry->key, key) == 0) {
      free(entry->value);
      entry->value = malloc(strlen(value) + 1);
      strcpy(entry->value, value);
      return;
    }

    // walk
    prev = entry;
    entry = entry->next;
  }

  // theres no match create new next
  prev->next = createEntry(key, value);
}

tableEntry *createEntry(const char *key, const char *value) {

  tableEntry *entry = malloc(sizeof(tableEntry));

  entry->key = malloc(strlen(key) + 1);
  entry->value = malloc(strlen(value) + 1);

  strcpy(entry->key, key);
  strcpy(entry->value, value);

  entry->next = NULL;
  return entry;
}

char *GetHT(HashTable *ht, const char *key) {
  unsigned int slot = hash(key);

  tableEntry *entry = ht->entries[slot];

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

void DelHT(HashTable *ht, const char *key) {
  unsigned int slot = hash(key);

  tableEntry *entry = ht->entries[slot];

  if (entry == NULL) {
    return;
  }

  tableEntry *prev = NULL;

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
        tableEntry *next = entry->next;
        prev->next = next;
        freeEntry(entry);
      }

      return;
    }

    prev = entry;
    entry = entry->next;
  }
}

void DumpHT(HashTable *ht) {
  for (int i = 0; i < TABLE_SIZE; ++i) {

    tableEntry *entry = ht->entries[i];

    if (entry == NULL)
      continue;

    while (entry != NULL) {
      printf("(%s,%s) ", entry->key, entry->value);
      entry = entry->next;
    }
    printf("\n");
  }
}

void freeEntry(tableEntry *entry) {
  free(entry->key);
  free(entry->value);
  free(entry);
}

void FreeHT(HashTable *table) {
  for (int i = 0; i < TABLE_SIZE; i++) {
    tableEntry *entry = table->entries[i];
    while (entry != NULL) {
      // printf("Freed (%s,%s) ", entry->key, entry->value);
      freeEntry(entry);
      entry = entry->next;
    }
  }
  free(table->entries);
  free(table);
}
