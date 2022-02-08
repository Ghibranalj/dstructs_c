
#ifndef LL_TYPE
#error LL_TYPE not defined
#endif

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "generic.h"

typedef struct linkednode linkednode;
struct linkednode {
    LL_TYPE *val;
    linkednode *next;
    linkednode *prev;
};

typedef struct linkedlist linkedlist;
struct linkedlist {
    linkednode *head;
    linkednode *tail;
    int size;
};

linkednode *ln_create(LL_TYPE data) {
    LL_TYPE *val = malloc(sizeof(LL_TYPE));

    linkednode *node = malloc(sizeof(linkednode));

    *val = data;
    node->val = val;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

void ln_free(linkednode *ln) {
    if (ln == NULL)
        return;

    ln_free(ln->next);

    free(ln->val);
    free(ln);
}

void ln_dump(linkednode *ln) {
    if (ln == NULL) {
        printf("\n");
        return;
    }

    printf("=>(");
    printtype(*ln->val);
    printf(")");
    ln_dump(ln->next);
}

#define LINKEDLIST ll_create

linkedlist *ll_create() {
    linkedlist *ll = malloc(sizeof(linkedlist));
    ll->size = 0;
    ll->head = NULL;
    ll->tail = NULL;

    return ll;
}

void ll_append(linkedlist *ll, LL_TYPE val) {

    linkednode *n_node = ln_create(val);

    ll->size++;
    if (ll->head == NULL && ll->tail == NULL) {
        ll->head = n_node;
        ll->tail = n_node;
        return;
    }

    linkednode *prev = ll->tail;
    prev->next = n_node;
    n_node->prev = prev;

    ll->tail = n_node;
}

void ll_insertat(linkedlist *ll, LL_TYPE val, int index) {
    // last node
    if (index == ll->size - 1) {
        ll_append(ll, val);
        return;
    }

    linkednode *curr = ll->head;
    // ln_dump(curr);
    ll->size++;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }

    printf("\n");

    linkednode *n_node = ln_create(val);

    linkednode *next = curr;
    linkednode *prev = curr->prev;

    n_node->next = next;

    if (prev != NULL) {
        prev->next = n_node;
    }
    // first node
    if (prev == NULL) {
        ll->head = n_node;
    }
    next->prev = n_node;
}

void ll_delat(linkedlist *ll, int index) {
    linkednode *curr = ll->head;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }

    // ln_dump(curr);

    linkednode *prev = curr->prev;
    linkednode *next = curr->next;

    // first node
    if (prev == NULL) {
        ll->head = next;
        ll->head->prev = NULL;
    }
    // not first node
    if (prev != NULL) {
        prev->next = next;
    }
    // last node
    if (next == NULL) {
        ll->tail = prev;
        ll->tail->next = NULL;
    }
    // not last node
    if (next != NULL) {
        next->prev = prev;
    }

    free(curr->val);
    free(curr);
    ll->size--;
}

void ll_free(linkedlist *ll) {
    linkednode *head = ll->head;
    ln_free(head);
    free(ll);
}

void ll_dump(linkedlist *ll) {
    linkednode *head = ll->head;
    ln_dump(head);
}