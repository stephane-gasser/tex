#include "makeop.h"
#include "fetch.h"
#include "cleanbox.h"
#include "half.h"
#include "newnullbox.h"
#include "rebox.h"
#include "freenode.h"
#include "newkern.h"

scaled makeop(halfword q)
{
	if (subtype(q) == 0 && curstyle < 2)
		subtype(q) = 1;
	scaled delta;
	if (link(q+1) == 1)
	{
		fetch(q+1);
		if (curstyle < 2 && curi.b2%4 == 2)
		{
			auto c = curi.b3;
			auto i = fontinfo[charbase[curf]+c].qqqq;
			if (i.b0 > 0)
			{
				curc = c;
				curi = i;
				subtype(q+1) = c;
			}
		}
		delta = fontinfo[italicbase[curf]+curi.b2/4].int_;
		auto x = cleanbox(q+1, curstyle);
		if (link(q+3) && subtype(q) != 1)
		mem[x+1].int_ -= delta;
		mem[x+4].int_ = half(mem[x+3].int_-mem[x+2].int_)-fontinfo[22+parambase[fam_fnt(2+cursize)]].int_;
		link(q+1) = 2;
		info(q+1) = x;
	}
	else
		delta = 0;
	if (subtype(q) == 1)
	{
		auto x = cleanbox(q+2, 2*(curstyle/4)+4+curstyle%2);
		auto y = cleanbox(q+1, curstyle);
		auto z = cleanbox(q+3, 2*(curstyle/4)+5);
		auto v = newnullbox();
		type(v) = 1;
		mem[v+1].int_ = mem[y+1].int_;
		if (mem[x+1].int_ > mem[v+1].int_)
			mem[v+1].int_ = mem[x+1].int_;
		if (mem[z+1].int_ > mem[v+1].int_)
			mem[v+1].int_ = mem[z+1].int_;
		x = rebox(x, mem[v+1].int_);
		y = rebox(y, mem[v+1].int_);
		z = rebox(z, mem[v+1].int_);
		mem[x+4].int_ = half(delta);
		mem[z+4].int_ = -mem[x+4].int_;
		mem[v+3].int_ = mem[y+3].int_;
		mem[v+2].int_ = mem[y+2].int_;
		if (link(q+2) == 0)
		{
			freenode(x, 7);
			link(v+5) = y;
		}
		else
		{
			scaled shiftup = fontinfo[11+parambase[fam_fnt(3+cursize)]].int_-mem[x+2].int_;
			if (shiftup < fontinfo[9+parambase[fam_fnt(3+cursize)]].int_)
				shiftup = fontinfo[9+parambase[fam_fnt(3+cursize)]].int_;
			auto p = newkern(shiftup);
			link(p) = y;
			link(x) = p;
			p = newkern(fontinfo[13+parambase[fam_fnt(3+cursize)]].int_);
			link(p) = x;
			link(v+5) = p;
			mem[v+3].int_ = mem[v+3].int_+fontinfo[13+parambase[fam_fnt(3+cursize)]].int_+mem[x+3].int_+mem[x+2].int_+shiftup;
		}
		if (link(q+3) == 0)
			freenode(z, 7);
		else
		{
			scaled shiftdown = fontinfo[12+parambase[fam_fnt(3+cursize)]].int_-mem[z+3].int_;
			if (shiftdown < fontinfo[10+parambase[fam_fnt(3+cursize)]].int_)
				shiftdown = fontinfo[10+parambase[fam_fnt(3+cursize)]].int_;
			auto p = newkern(shiftdown);
			link(y) = p;
			link(p) = z;
			p = newkern(fontinfo[13+parambase[fam_fnt(3+cursize)]].int_);
			link(z) = p;
			mem[v+2].int_ = mem[v+2].int_+fontinfo[13+parambase[fam_fnt(3+cursize)]].int_+mem[z+3].int_+mem[z+2].int_+shiftdown;
		}
		mem[q+1].int_ = v;
	}
	return delta;
}
