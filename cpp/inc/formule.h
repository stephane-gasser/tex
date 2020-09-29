#ifndef FORMULE_H
#define FORMULE_H

#include "globals.h"
#include "noeud.h"
#include "calcul.h"

inline smallnumber curstyle;
inline bool mlistpenalties;

int& fam_fnt(halfword);
int axis_height(smallnumber);
int math_quad(smallnumber);
BoxNode *overbar(BoxNode*, scaled, scaled);
void mlisttohlist(void);
Noad *finmlist(Noad*);
void setCurSize(smallnumber style, bool setMu = true);

#endif
