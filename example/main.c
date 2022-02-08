#include "linkedlist.h" 
int main(){

    linkedlist * ll = ll_create(0);

    ll_append(ll, 5);

    ll_append(ll,65);

    ll_dump(ll, true);
    ll_free(ll);
}