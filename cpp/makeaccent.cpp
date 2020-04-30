#include "makeaccent.h"
#include "scancharnum.h"
#include "newcharacter.h"
#include "doassignments.h"
#include "backinput.h"
#include "hpack.h"
#include "newkern.h"
#include <cmath>

void makeaccent(void)
{
	float s, t;
	halfword r;
	scaled a, h, x, w, delta;
	fourquarters i;
	scancharnum();
	internalfontnumber f = cur_font();
	auto p = newcharacter(f, curval);
	if (p)
	{
		x = fontinfo[5+parambase[f]].int_;
		s = fontinfo[1+parambase[f]].int_/65536.0;
		a = fontinfo[widthbase[f]+fontinfo[charbase[f]+subtype(p)].qqqq.b0].int_;
		doassignments();
		halfword q = 0;
		f = cur_font();
		if (curcmd == 11 || curcmd == 12 || curcmd == 68)
			q = newcharacter(f, curchr);
		else 
			if (curcmd == 16)
			{
				scancharnum();
				q = newcharacter(f, curval);
			}
			else
				backinput();
		if (q)
		{
			t = fontinfo[1+parambase[f]].int_/65536.0;
			i = fontinfo[charbase[f]+subtype(q)].qqqq;
			w = fontinfo[widthbase[f]+i.b0].int_;
			h = fontinfo[heightbase[f]+i.b1/16].int_;
			if (h != x)
			{
				p = hpack(p, 0, 1);
				mem[p+4].int_ = x-h;
			}
			delta = round((w-a)/2.0+h*t-x*s);
			r = newkern(delta);
			subtype(r) = 2;
			link(curlist.tailfield) = r;
			link(r) = p;
			curlist.tailfield = newkern(-a-delta);
			subtype(curlist.tailfield) = 2;
			link(p) = curlist.tailfield;
			p = q;
		}
		link(curlist.tailfield) = p;
		curlist.tailfield = p;
		curlist.auxfield.hh.lh = 1000;
	}
}
