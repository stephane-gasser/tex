#include "makeaccent.h"
#include "lecture.h"
#include "noeud.h"
#include "doassignments.h"
#include "backinput.h"
#include "hpack.h"
#include "police.h"
#include <cmath>

//! slant to the right, per unit distance upward
static int& slant(internalfontnumber f) { return param(slant_code, f); }

void makeaccent(Token t)
{
	auto f = cur_font();
	auto p = newcharacter(f, scancharnum());
	if (p)
	{
		auto x = x_height(f);
		auto s = slant(f)/float(unity);
		auto a = char_width(f, char_info(f, character(p)));
		doassignments();
		halfword q = 0;
		f = cur_font();
		if (t.cmd == letter || t.cmd == other_char || t.cmd == char_given)
			q = newcharacter(f, t.chr);
		else 
			if (t.cmd == char_num)
				q = newcharacter(f, scancharnum());
			else
				backinput(t);
		if (q)
		{
			auto t = slant(f)/float(unity);
			auto i = char_info(f, character(q));
			auto w = char_width(f, i);
			auto h = char_height(f, i);
			if (h != x)
			{
				p = hpack(p, 0, additional);
				shift_amount(p) = x-h;
			}
			auto delta = round((w-a)/2.0+h*t-x*s);
			auto r = newkern(delta);
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
