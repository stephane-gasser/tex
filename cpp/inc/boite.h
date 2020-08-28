#ifndef BOITE_H
#define BOITE_H

#include "globals.h"

BoxNode *rebox(BoxNode*, scaled);
BoxNode *cleanbox(NoadContent&, smallnumber);
void alterboxdimen(halfword);
void beginbox(int, Token);
void boxend(int);
BoxNode *charbox(const Font&, quarterword);
void ensurevbox(eightbits);
BoxNode *vpackage(LinkedNode*, scaled, smallnumber, scaled);
BoxNode *vpack(LinkedNode*, scaled, smallnumber);
BoxNode *hpack(LinkedNode*, scaled, smallnumber);
void package(smallnumber, Token);
void unpackage(halfword);

#endif
