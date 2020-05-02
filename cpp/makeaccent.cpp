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
		s = fontinfo[1+parambase[f]].int_/float(0x1'00'00);
		a = fontinfo[widthbase[f]+fontinfo[charbase[f]+subtype(p)].qqqq.b0].int_;
		doassignments();
		halfword q = 0;
		f = cur_font();
		if (curcmd == letter || curcmd == other_char || curcmd == char_given)
			q = newcharacter(f, curchr);
		else 
			if (curcmd == char_num)
			{
				scancharnum();
				q = newcharacter(f, curval);
			}
			else
				backinput();
		if (q)
		{
			t = fontinfo[1+parambase[f]].int_/float(0x1'00'00);
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
			link(tail) = r;
			link(r) = p;
			tail = newkern(-a-delta);
			subtype(tail) = 2;
			link(p) = tail;
			p = q;
		}
		tail_append(p);
		space_factor = 1000;
	}
}
