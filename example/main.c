#define LL_TYPE char*
#include "linkedlist.h"
#undef LL_TYPE
int main(){

    linkedlist * ll = LINKEDLIST();
    
    ll_append(ll, "hello world");
    ll_append(ll, "gggg");
    ll_append(ll, "amazing");

    ll_insertat(ll,"first", 0);

    ll_dump(ll);
    ll_free(ll);
}