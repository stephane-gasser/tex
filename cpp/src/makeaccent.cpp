#include "makeaccent.h"
#include "lecture.h"
#include "noeud.h"
#include "doassignments.h"
#include "backinput.h"
#include "hpack.h"
#include "police.h"
#include <cmath>

void makeaccent(Token t)
{
	auto f = curFontNum();
	auto p = newcharacter(f, scancharnum());
	if (p)
	{
		auto x = cur_font().x_height();
		auto s = cur_font().slant()/float(unity);
		auto a = cur_font().char_width(character(p));
		doassignments();
		halfword q = 0;
		f = curFontNum();
		if (t.cmd == letter || t.cmd == other_char || t.cmd == char_given)
			q = newcharacter(f, t.chr);
		else 
			if (t.cmd == char_num)
				q = newcharacter(f, scancharnum());
			else
				backinput(t);
		if (q)
		{
			auto t = cur_font().slant()/float(unity);
			auto w = cur_font().char_width(character(q));
			auto h = cur_font().char_height(character(q));
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
