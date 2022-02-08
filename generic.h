#ifndef DSTRUCTS_C_GENERIC_H
#define DSTRUCTS_C_GENERIC_H

#include <stdio.h>

void print_int(int x) { printf("%d", x); }
void print_float(float x) { printf("%f", x); }
void print_str(char* x) { printf("%s", x); }
void print_pointer(void* x) { printf("%p", x); }

#define printtype(X)                                                           \
  _Generic((X), int: print_int, \
                float : print_float, \
                char* : print_str,\
                default : print_pointer)(X)
#endif