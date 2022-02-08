#pragma once
#include <stdbool.h>

#include "hashtable.h"

typedef struct HashTable hashset;

hashset* hs_create();

void hs_insert(hashset* hs, const char* key);
bool hs_contains(hashset* hs, const char* key);

void hs_del(hashset* hs, const char* key);

void hs_free(hashset* hs);
void hs_dump(hashset* hs);



