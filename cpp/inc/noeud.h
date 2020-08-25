#ifndef NOEUD_H
#define NOEUD_H

#include "globals.h"

[[deprecated]] void flushlist(halfword);
void flushlist(LinkedNode*);
CharNode* newcharacter(internalfontnumber, eightbits);
void newfont(smallnumber);
void newgraf(bool);
void newhyphexceptions(void);
void newinteraction(Token);
halfword newnoad(void);
void newsavelevel(groupcode);
GlueNode* newskipparam(smallnumber);
[[deprecated]] halfword newspec(halfword);
GlueSpec *newspec(GlueSpec*);
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
