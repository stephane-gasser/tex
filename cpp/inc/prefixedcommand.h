#ifndef PREFIXEDCOMMAND_H
#define PREFIXEDCOMMAND_H

#include "globals.h"
#include "token.h"

inline Token aftertoken;

void prefixedcommand(char&, Token, int&, int&, bool = true);

#endif
