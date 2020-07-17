#ifndef NOEUD_H
#define NOEUD_H

#include "globals.h"

halfword newcharacter(internalfontnumber, eightbits);
halfword newchoice(void);
halfword newdisc(void);
void newfont(smallnumber, halfword);
halfword newglue(halfword);
void newgraf(bool, halfword);
void newhyphexceptions(halfword);
void newinteraction(halfword);
halfword newkern(scaled);
halfword newligature(quarterword, quarterword, halfword);
halfword newligitem(quarterword);
halfword newmath(scaled, smallnumber);
halfword newnoad(void);
halfword newnullbox(void);
halfword newparamglue(smallnumber);
void newpatterns(halfword, halfword);
halfword newpenalty(int);
halfword newrule(void);
void newsavelevel(groupcode);
halfword newskipparam(smallnumber);
halfword newspec(halfword);
halfword newstyle(smallnumber);
quarterword newtrieop(smallnumber, smallnumber, quarterword);
void newwhatsit(smallnumber, smallnumber);
void newwritewhatsit(smallnumber, halfword, halfword);
halfword copynodelist(halfword);
void flushnodelist(halfword);
void freenode(halfword, halfword);
halfword getnode(int);
triepointer trienode(triepointer);
void appendchoices(halfword);
void appenddiscretionary(halfword, halfword);
void appendglue(halfword, halfword);
void appenditaliccorrection(void);
void appendkern(halfword, halfword);
void appendpenalty(halfword);
void appendtovlist(halfword);
void appspace(halfword &, fontindex &);

#endif
