#ifndef FORMULE_H
#define FORMULE_H

#include "globals.h"

BoxNode *overbar(BoxNode*, scaled, scaled);
void makefraction(FractionNoad*);
void makemathaccent(AccentNoad*);
scaled makeop(Noad*);
void makeord(Noad*);
void makeover(Noad*);
void makeradical(RadicalNoad*);
void makescripts(Noad*, scaled);
void makeunder(Noad*);
void makevcenter(Noad*);
smallnumber makeleftright(LeftRightNoad*, smallnumber, scaled, scaled);
void mlisttohlist(void);

#endif
