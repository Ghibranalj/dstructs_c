#include <stdbool.h>
#include <stddef.h>

#include "hashset.h"
#include "hashtable.h"


bool hs_contains(hashset* hs, const char* key){
    return GetHT(hs, key) != NULL;
}

void hs_del(hashset* hs, const char* key){
    DelHT(hs, key);
}

hashset* hs_create(){
    return CreateHT();
}

void hs_free(hashset* hs){
    FreeHT(hs);
}

void hs_dump(hashset* hs){
    DumpHT(hs);
}

void hs_insert(hashset* hs, const char* key){
    SetHT(hs, key, "SET");
}

void helloworld(){
    printf("helloworld");
}
