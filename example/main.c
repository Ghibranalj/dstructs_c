#include <string.h>


#define LL_TYPE char*
#include "linkedlist.h"
#undef LL_TYPE

#define HT_VALUE_TYPE char*
#include "hashtable.h"
#undef HT_VALUE_TYPE

int main(){

    linkedlist * ll = LINKEDLIST();
    
    ll_append(ll, "hello world");
    ll_append(ll, "gggg");
    ll_append(ll, "amazing");

    ll_insertat(ll,"first", 0);

    ll_dump(ll);
    ll_free(ll);

    // testing hashtable

    hashtable * ht = HASHTABLE();
    char* text = malloc(strlen("hello world") * sizeof(char) + 1);
    strcpy(text, "hello world");
    ht_set(ht,"hello world", text);
    ht_dump(ht);

    char * out = ht_get(ht,"hello world");
    printf("%s\n", out);

    ht_free(ht);
}