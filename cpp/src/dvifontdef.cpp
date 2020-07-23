#include "dvifontdef.h"
#include "dviswap.h"
#include "dvifour.h"
#include "police.h"

void dvifontdef(internalfontnumber f)
{
	dvi_out(fnt_def1);
	dvi_out(f-1);
	dvi_out(fonts[f].check.b0);
	dvi_out(fonts[f].check.b1);
	dvi_out(fonts[f].check.b2);
	dvi_out(fonts[f].check.b3);
	dvifour(fonts[f].size);
	dvifour(fonts[f].dsize);
	dvi_out(fonts[f].area.size());
	dvi_out(fonts[f].name.size());
	for (auto c: fonts[f].area)
		dvi_out(c);
	for (auto c: fonts[f].name)
		dvi_out(c);
}
