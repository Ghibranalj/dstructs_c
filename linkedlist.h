#pragma once

#include <stdbool.h>

typedef struct linkednode linkednode;
typedef struct linkednode linkedlist;

struct linkednode {
    int val;
    linkednode *next;
    linkednode *prev;
};

void ll_append(linkedlist *list, int data);

linkedlist *ll_create(int init);
linkedlist *ll_gethead(linkedlist *list);

// void ll_shiftF(linkedlist **list, int times);
// void ll_shiftB(linkedlist *list, int times);
void ll_forward(linkedlist **list);
void ll_backward(linkedlist **list);


void ll_dump(linkedlist *list, bool from_head);
void ll_free(linkedlist *ll);

int ll_length(linkedlist *ll, bool from_head);
