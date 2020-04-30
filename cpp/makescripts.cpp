#include "makescripts.h"
#include "hpack.h"
#include "cleanbox.h"
#include "freenode.h"
#include "newkern.h"
#include "vpackage.h"

void makescripts(halfword q, scaled delta)
{
	halfword p = mem[q+1].int_;
	scaled shiftup, shiftdown;
	if (p >= himemmin)
	{
		shiftup = 0;
		shiftdown = 0;
	}
	else
	{
		auto z = hpack(p, 0, 1);
		smallnumber t;
		if (curstyle < 4)
			t = 16;
		else
			t = 32;
		shiftup = mem[z+3].int_-fontinfo[18+parambase[fam_fnt(2+t)]].int_;
		shiftdown = mem[z+2].int_+fontinfo[19+parambase[fam_fnt(2+t)]].int_;
		freenode(z, 7);
	}
	scaled clr;
	halfword x;
	if (link(q+2) == 0)
	{
		x = cleanbox(q+3, 2*(curstyle/4)+5);
		mem[x+1].int_ += eqtb[5842].int_;
		if (shiftdown < fontinfo[16+parambase[fam_fnt(2+cursize)]].int_)
			shiftdown = fontinfo[16+parambase[fam_fnt(2+cursize)]].int_;
		clr = mem[x+3].int_-(abs(fontinfo[5+parambase[fam_fnt(2+cursize)]].int_*4)/5);
		if (shiftdown < clr)
			shiftdown = clr;
		mem[x+4].int_ = shiftdown;
	}
	else
	{
		x = cleanbox(q+2, 2*(curstyle/4)+4+(curstyle%2));
		mem[x+1].int_ += eqtb[5842].int_;
		if (curstyle%2)
			clr = fontinfo[15+parambase[fam_fnt(2+cursize)]].int_;
		else 
			if (curstyle < 2)
				clr = fontinfo[13+parambase[fam_fnt(2+cursize)]].int_;
			else
				clr = fontinfo[14+parambase[fam_fnt(2+cursize)]].int_;
		if (shiftup < clr)
			shiftup = clr;
		clr = mem[x+2].int_+abs(fontinfo[5+parambase[fam_fnt(2+cursize)]].int_)/4;
		if (shiftup < clr)
			shiftup = clr;
		if (link(q+3) == 0)
			mem[x+4].int_ = -shiftup;
		else
		{
			auto y = cleanbox(q+3, 2*(curstyle/4)+5);
			mem[y+1].int_ = mem[y+1].int_+eqtb[5842].int_;
			if (shiftdown < fontinfo[17+parambase[fam_fnt(2+cursize)]].int_)
				shiftdown = fontinfo[17+parambase[fam_fnt(2+cursize)]].int_;
			clr = 4*fontinfo[8+parambase[fam_fnt(3+cursize)]].int_-(shiftup-mem[x+2].int_-(mem[y+3].int_-shiftdown));
			if (clr > 0)
			{
				shiftdown = shiftdown+clr;
				clr = (abs(fontinfo[5+parambase[fam_fnt(2+cursize)]].int_ * 4)/5)-(shiftup-mem[x+2].int_);
				if (clr > 0)
				{
					shiftup += clr;
					shiftdown -= clr;
				}
			}
			mem[x+4].int_ = delta;
			p = newkern(shiftup-mem[x+2].int_-(mem[y+3].int_-shiftdown));
			link(x) = p;
			link(p) = y;
			x = vpackage(x, 0, 1, 1073741823);
			mem[x+4].int_ = shiftdown;
		}
	}
	if (mem[q+1].int_ == 0)
		mem[q+1].int_ = x;
	else
	{
		p = mem[q+1].int_;
		while (link(p))
			p = link(p);
		link(p) = x;
	}
}
