#ifndef NOEUD_H
#define NOEUD_H

#include "globals.h"

halfword newcharacter(internalfontnumber, eightbits);
halfword newchoice(void);
halfword newdisc(void);
void newfont(smallnumber);
halfword newglue(halfword);
void newgraf(bool);
void newhyphexceptions(void);
void newinteraction(void);
halfword newkern(scaled);
halfword newligature(quarterword, quarterword, halfword);
halfword newligitem(quarterword);
halfword newmath(scaled, smallnumber);
halfword newnoad(void);
halfword newnullbox(void);
halfword newparamglue(smallnumber);
void newpatterns(void);
halfword newpenalty(int);
halfword newrule(void);
void newsavelevel(groupcode);
halfword newskipparam(smallnumber);
halfword newspec(halfword);
halfword newstyle(smallnumber);
quarterword newtrieop(smallnumber, smallnumber, quarterword);
void newwhatsit(smallnumber, smallnumber);
void newwritewhatsit(smallnumber);

#endif
