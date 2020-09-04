#ifndef DVI_H
#define DVI_H

#include "globals.h"

typedef int dviindex; // 0..dvibufsize

constexpr int dvibufsize = 800;

enum
{
	set1 = 128, //!< typeset a character and move right
	set_rule = 132, //!< typeset a rule and move right
	put_rule = 137, //!< typeset a rule
	bop = 139, //!< beginning of page
	eop = 140, //!< ending of page
	push = 141, //!< save the current positions
	pop = 142, //!< restore previous positions
	right1 = 143, //!< move right
	down1 = 157, //!< move down
	fnt_num_0 = 171, //!< set current font to 0
	fnt1 = 235, //!< set current font
	xxx1 = 239, //!< extension to DVI primitives
	xxx4 = 242, //!< potentially long extension to DVI primitives
	fnt_def1 = 243, //!< define the meaning of a font number
	pre = 247, //!< preamble
	post = 248, //!< postamble beginning
	post_post = 249 //!< postamble ending
};

inline bytefile dvifile;
inline dviindex dviptr = 0;
inline scaled dvih, dviv;
inline scaled curh, curv;
inline internalfontnumber dvif;
inline int dvioffset = 0;
inline int lastbop = -1;

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

#endif
