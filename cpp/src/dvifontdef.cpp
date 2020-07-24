#include "dvifontdef.h"
#include "dviswap.h"
#include "dvifour.h"
#include "police.h"

void dvifontdef(internalfontnumber f)
{
	dvi_out(fnt_def1);
	dvi_out(f-1);
	auto &ft = fonts[f];
	dvi_out(ft.check.b0);
	dvi_out(ft.check.b1);
	dvi_out(ft.check.b2);
	dvi_out(ft.check.b3);
	dvifour(ft.size);
	dvifour(ft.dsize);
	dvi_out(ft.area.size());
	dvi_out(ft.name.size());
	for (auto c: ft.area)
		dvi_out(c);
	for (auto c: ft.name)
		dvi_out(c);
}
