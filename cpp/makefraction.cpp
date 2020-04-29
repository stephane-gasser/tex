#include "makefraction.h"
#include "cleanbox.h"
#include "rebox.h"
#include "half.h"
#include "newnullbox.h"
#include "fractionrule.h"
#include "newkern.h"
#include "vardelimiter.h"
#include "hpack.h"

void makefraction(halfword q)
{
	if (mem[q+1].int_ == 1073741824)
		mem[q+1].int_ = fontinfo[8+parambase[eqtb[3938+cursize].hh.rh]].int_;
	auto x = cleanbox(q+2, curstyle+2-2*(curstyle/6));
	auto z = cleanbox(q+3, 2*(curstyle/2)+3-2*(curstyle/6));
	if (mem[x+1].int_ < mem[z+1].int_)
		x = rebox(x, mem[z+1].int_);
	else
		z = rebox(z, mem[x+1].int_);
	scaled shiftup, shiftdown;
	if (curstyle < 2)
	{
		shiftup = fontinfo[8+parambase[eqtb[3937+cursize].hh.rh]].int_;
		shiftdown = fontinfo[11+parambase[eqtb[3937+cursize].hh.rh]].int_;
	}
	else
	{
		shiftdown = fontinfo[12+parambase[eqtb[3937+cursize].hh.rh]].int_;
		if (mem[q+1].int_)
			shiftup = fontinfo[9+parambase[eqtb[3937+cursize].hh.rh]].int_;
		else
			shiftup = fontinfo[10+parambase[eqtb[3937+cursize].hh.rh]].int_;
	}
	scaled clr, delta;
	if (mem[q+1].int_ == 0)
	{
		if (curstyle < 2)
			clr = 7*fontinfo[8+parambase[eqtb[3938+cursize].hh.rh]].int_;
		else
			clr = 3*fontinfo[8+parambase[eqtb[3938+cursize].hh.rh]].int_;
		delta = half(clr-((shiftup-mem[x+2].int_)-(mem[z+3].int_-shiftdown)));
		if (delta > 0)
		{
			shiftup += delta;
			shiftdown += delta;
		}
	}
	else
	{
		if (curstyle < 2)
			clr = 3*mem[q+1].int_;
		else
			clr = mem[q+1].int_;
		delta = half(mem[q+1].int_);
		scaled delta1 = clr-(shiftup-mem[x+2].int_-(fontinfo[22+parambase[eqtb[3937+cursize].hh.rh]].int_+delta));
		scaled delta2 = clr-(fontinfo[22+parambase[eqtb[3937+cursize].hh.rh]].int_-delta-(mem[z+3].int_-shiftdown));
		if (delta1 > 0)
			shiftup += delta1;
		if (delta2 > 0)
			shiftdown += delta2;
	}
	auto v = newnullbox();
	type(v) = 1;
	mem[v+3].int_ = shiftup+mem[x+3].int_;
	mem[v+2].int_ = mem[z+2].int_+shiftdown;
	mem[v+1].int_ = mem[x+1].int_;
	halfword p;
	if (mem[q+1].int_ == 0)
	{
		p = newkern((shiftup-mem[x+2].int_)-(mem[z+3].int_-shiftdown));
		link(p) = z;
	}
	else
	{
		auto y = fractionrule(mem[q+1].int_);
		p = newkern((fontinfo[22+parambase[eqtb[3937+cursize].hh.rh]].int_-delta)-(mem[z+3].int_-shiftdown));
		link(y) = p;
		link(p) = z;
		p = newkern((shiftup-mem[x+2].int_)-(fontinfo[22+parambase[eqtb[3937+cursize].hh.rh]].int_+delta));
		link(p) = y;
	}
	link(x) = p;
	link(v+5) = x;
	if (curstyle < 2)
		delta = fontinfo[20+parambase[eqtb[3937+cursize].hh.rh]].int_;
	else
		delta = fontinfo[21+parambase[eqtb[3937+cursize].hh.rh]].int_;
	x = vardelimiter(q+4, cursize, delta);
	link(x) = v;
	z = vardelimiter(q+5, cursize, delta);
	link(v) = z;
	mem[q+1].int_ = hpack(x, 0, 1);
}
