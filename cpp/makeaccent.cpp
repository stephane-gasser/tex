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
		x = param(x_height_code, f);
		s = param(slant_code, f)/float(unity);
		a = char_width(f, char_info(f, character(p)));
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
			t = param(slant_code, f)/float(unity);
			i = char_info(f, character(q));
			w = char_width(f, i);
			h = char_height(f, i);
			if (h != x)
			{
				p = hpack(p, 0, 1);
				shift_amount(p) = x-h;
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
