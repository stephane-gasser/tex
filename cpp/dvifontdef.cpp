#include "dvifontdef.h"
#include "dviswap.h"
#include "dvifour.h"

void dvifontdef(internalfontnumber f)
{
	dvi_out(fnt_def1);
	dvi_out(f-1);
	dvi_out(fontcheck[f].b0);
	dvi_out(fontcheck[f].b1);
	dvi_out(fontcheck[f].b2);
	dvi_out(fontcheck[f].b3);
	dvifour(fontsize[f]);
	dvifour(fontdsize[f]);
	dvi_out(fontarea[f].size());
	dvi_out(fontname[f].size());
	for (auto c: fontarea[f])
		dvi_out(c);
	for (auto c: fontname[f])
		dvi_out(c);
}
