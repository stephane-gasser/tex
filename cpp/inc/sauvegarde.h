#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include "globals.h"
#include "equivalent.h"
#include "token.h"

void saveforafter(halfword);
void newsavelevel(groupcode);
void unsave(void);
void offsave(Token);

inline groupcode curgroup = 0;

#endif


