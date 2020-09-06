#ifndef FORMULE_H
#define FORMULE_H

#include "globals.h"
#include "noeud.h"

inline smallnumber curstyle;
inline smallnumber cursize;
inline scaled curmu;
inline bool mlistpenalties;

int& fam_fnt(halfword);
int axis_height(smallnumber);
int math_quad(smallnumber);
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
Noad *finmlist(Noad*);

#endif
