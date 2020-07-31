#ifndef NOEUD_H
#define NOEUD_H

#include "globals.h"

[[deprecated]] void flushlist(halfword);
void flushlist(LinkedNode*);
CharNode* newcharacter(internalfontnumber, eightbits);
void newfont(smallnumber);
halfword newglue(halfword);
void newgraf(bool);
void newhyphexceptions(void);
void newinteraction(Token);
halfword newligature(quarterword, quarterword, halfword);
halfword newligitem(quarterword);
halfword newmath(scaled, smallnumber);
halfword newnoad(void);
halfword newnullbox(void);
halfword newparamglue(smallnumber);
halfword newpenalty(int);
halfword newrule(void);
void newsavelevel(groupcode);
halfword newskipparam(smallnumber);
halfword newspec(halfword);
halfword newstyle(smallnumber);
void newwhatsit(smallnumber, smallnumber);
void newwritewhatsit(smallnumber, Token);
[[deprecated]] halfword copynodelist(halfword);
LinkedNode* copynodelist(LinkedNode*);
[[deprecated]] void flushnodelist(halfword);
void flushnodelist(LinkedNode*);
void freenode(halfword, halfword);
halfword getnode(int);
void appendchoices(void);
void appenddiscretionary(halfword);
void appendglue(halfword);
void appenditaliccorrection(void);
void appendkern(halfword);
void appendpenalty(void);
void appendtovlist(halfword);
void appspace(halfword &, fontindex &);

#endif
