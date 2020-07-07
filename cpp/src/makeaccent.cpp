#include "makeaccent.h"
#include "lecture.h"
#include "newcharacter.h"
#include "doassignments.h"
#include "backinput.h"
#include "hpack.h"
#include "newkern.h"
#include <cmath>

//! slant to the right, per unit distance upward
static int& slant(internalfontnumber f) { return param(slant_code, f); }

void makeaccent(void)
{
	float s, t;
	halfword r;
	scaled a, h, x, w, delta;
	fourquarters i;
	curval = scancharnum();
	internalfontnumber f = cur_font();
	auto p = newcharacter(f, curval);
	if (p)
	{
		x = x_height(f);
		s = slant(f)/float(unity);
		a = char_width(f, char_info(f, character(p)));
		doassignments();
		halfword q = 0;
		f = cur_font();
		if (curcmd == letter || curcmd == other_char || curcmd == char_given)
			q = newcharacter(f, curchr);
		else 
			if (curcmd == char_num)
			{
				curval = scancharnum();
				q = newcharacter(f, curval);
			}
			else
				backinput();
		if (q)
		{
			t = slant(f)/float(unity);
			i = char_info(f, character(q));
			w = char_width(f, i);
			h = char_height(f, i);
			if (h != x)
			{
				p = hpack(p, 0, additional);
				shift_amount(p) = x-h;
			}
			delta = round((w-a)/2.0+h*t-x*s);
			r = newkern(delta);
			subtype(r) = acc_kern;
			link(tail) = r;
			link(r) = p;
			tail = newkern(-a-delta);
			subtype(tail) = acc_kern;
			link(p) = tail;
			p = q;
		}
		tail_append(p);
		space_factor = 1000;
	}
}
