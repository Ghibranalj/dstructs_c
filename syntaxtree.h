#pragma once

typedef enum { BOLD, PAR, ITA, HTML, NONE, TEXT, BR, H1, H2, H3, H4, H5, H6} syntax;


typedef struct syntaxtree syntaxtree;
struct syntaxtree {
    syntax syntax;
    char *val;
    int children_len;
    syntaxtree **children;
};



void st_free(syntaxtree *tree);
void st_dump(syntaxtree *tree, char* tab);

void st_add_child(syntaxtree *tree, syntaxtree *child);

syntaxtree* st_create();

char *s_getname(syntax s);

