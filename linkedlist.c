#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"
#define LL_NULL (linkedlist *)NULL

linkedlist *alloc_node(int data, linkedlist *prev, linkedlist *next);

linkedlist *ll_create(int init) {
    linkedlist *ptr = alloc_node(init, LL_NULL, LL_NULL);
    return ptr;
}

void ll_append(linkedlist *list, int data) {



    linkedlist *tail = list;

    while (tail->next != LL_NULL) {
        tail = tail->next;
    }

    tail->next = alloc_node(data, tail, LL_NULL);
}

linkedlist *alloc_node(int data, linkednode *prev, linkednode *next) {
    linkedlist *ptr = malloc(sizeof(linkedlist));
    ptr->val = data;
    ptr->prev = prev;
    ptr->next = next;
    return ptr;
}

void ll_del(linkedlist *list, const linkedlist *head) {
    // TODO implement this
}

void free_node(linkedlist *list) {
    // free a single node
    free(list);
}

linkedlist *ll_gethead(linkedlist *list) {
    linkedlist *curr = list;
    while (curr->prev != NULL) {
        curr = curr->prev;
    }
    return curr;
}

void ll_dump(linkedlist *list, bool from_head) {
    linkedlist *curr = list;

    if (from_head) {
        curr = ll_gethead(curr);
    }
    printf("HEAD");
    while (curr != LL_NULL) {
        printf(" =>> %d", curr->val);
        curr = curr->next;
    }

    printf("\n");
}

void ll_forward(linkedlist **list) { *list = (*list)->next; }

void ll_backward(linkedlist **list) { *list = (*list)->prev; }

void ll_free(linkedlist *ll) {
    linkedlist *curr = ll_gethead(ll);
    while (curr != LL_NULL) {
        linkedlist *next = curr->next;
        free(curr);
        curr = next;
    }
}

int ll_length(linkedlist *ll, bool from_head) {
    linkedlist *curr = ll;
    if (from_head) {
        curr = ll_gethead(curr);
    }
    int i = 0;
    while (curr != LL_NULL) {
        i++;
        curr = curr->next;
    }
    return i;
}