#ifndef DVI_H
#define DVI_H

#include "globals.h"

void dvifontdef(internalfontnumber);
void dvifour(uint32_t);
void dvipop(int);
void dvi_out(eightbits);
void writedvi(dviindex, dviindex);
void movement(scaled, eightbits);
void synch_v(void);
void synch_h(void);
void prunemovements(int);
void closefilesandterminate(void);
void specialout(NotOpenWriteWhatsitNode *);

#endif
