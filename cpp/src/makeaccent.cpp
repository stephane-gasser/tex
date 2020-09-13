#include "makeaccent.h"
#include "lecture.h"
#include "noeud.h"
#include "doassignments.h"
#include "backinput.h"
#include "boite.h"
#include "police.h"
#include <cmath>

void makeaccent(Token t)
{
	if (auto p = newcharacter(curFontNum(), scancharnum()); p)
	{
		auto x = cur_font().x_height();
		auto s = cur_font().slant()/float(unity);
		auto a = p->width();
		doassignments();
		switch (t.cmd)
		{
			case char_num:
				t.chr = scancharnum(); [[fallthrough]];
			case letter:
			case other_char:
			case char_given:
			{
				auto q = newcharacter(curFontNum(), t.chr);
				auto t = cur_font().slant()/float(unity);
				auto w = q->width();
				auto h = q->height();
				auto delta = round((w-a)/2.0+h*t-x*s);
				tail_append(new KernNode(delta, acc_kern));
				if (h != x)
				{
					auto P = hpack(p, 0, additional);
					P->shift_amount = x-h;
					tail_append(P);
				}
				else
					tail_append(p);
				tail_append(new KernNode(-a-delta, acc_kern));
				tail_append(q);
				break;
			}
			default:
				backinput(t);
				tail_append(p);
		}
		space_factor = 1000;
	}
}
