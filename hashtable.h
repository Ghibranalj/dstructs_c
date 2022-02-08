#pragma once

typedef struct tableEntry
{
    char *key;
    char *value;

    struct tableEntry *next;
} tableEntry;

typedef struct HashTable
{
    tableEntry **entries;
} HashTable;



HashTable *CreateHT();

void SetHT(HashTable *ht, const char *key, const char *value);

char *GetHT(HashTable *ht, const char *key);

void DelHT(HashTable *ht, const char *key);

void DumpHT(HashTable *ht);

void FreeHT(HashTable *table);