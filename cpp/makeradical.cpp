#include "makeradical.h"
#include "cleanbox.h"
#include "vardelimiter.h"
#include "half.h"
#include "overbar.h"
#include "hpack.h"

void makeradical(halfword q)
{
	auto x = cleanbox(q+1, 2 *(curstyle/2)+1);
	scaled clr;
	if (curstyle < 2)
		clr = fontinfo[8+parambase[eqtb[3938+cursize].hh.rh]].int_+abs(fontinfo[5+parambase[eqtb[3937+cursize].hh.rh]].int_)/4;
	else
	{
		clr = fontinfo[8+parambase[eqtb[3938+cursize].hh.rh]].int_;
		clr += abs(clr)/4;
	}
	auto y = vardelimiter(q+4, cursize, mem[x+3].int_+mem[x+2].int_+clr+fontinfo[8+parambase[eqtb[3938+cursize].hh.rh]].int_);
	scaled delta = mem[y+2].int_-(mem[x+3].int_+mem[x+2].int_+clr);
	if (delta > 0)
		clr += half(delta);
	mem[y+4].int_ = -(mem[x+3].int_+clr);
	link(y) = overbar(x, clr, mem[y+3].int_);
	info(q+1) = hpack(y, 0, 1);
	link(q+1) = 2;
}
