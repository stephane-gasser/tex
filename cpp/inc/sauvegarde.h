#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include "globals.h"
#include "equivalent.h"

void eqsave(AnyNode*, quarterword);
void saveforafter(AnyNode *t);
void newsavelevel(groupcode);
void unsave(void);

#endif


