#ifndef EQUIVALENT_H
#define EQUIVALENT_H

#include "globals.h"

void eqworddefine(halfword, int);
void word_define(int, halfword, int);
void geqworddefine(halfword, int);
void define(int a, halfword, quarterword, halfword);
void eqdefine(halfword, quarterword, halfword);
void geqdefine(halfword, quarterword, halfword);
void eqdestroy(memoryword);

#endif
