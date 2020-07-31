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
	auto p = newcharacter(curFontNum(), scancharnum());
	if (p)
	{
		auto x = cur_font().x_height();
		auto s = cur_font().slant()/float(unity);
		auto a = cur_font().char_width(p->character);
		doassignments();
		CharNode *q = nullptr;
		if (t.cmd == letter || t.cmd == other_char || t.cmd == char_given)
			q = newcharacter(curFontNum(), t.chr);
		else 
			if (t.cmd == char_num)
				q = newcharacter(curFontNum(), scancharnum());
			else
				backinput(t);
		if (q)
		{
			auto t = cur_font().slant()/float(unity);
			auto w = cur_font().char_width(q->character);
			auto h = cur_font().char_height(q->character);
			if (h != x)
			{
				p->num = hpack(p->num, 0, additional);
				shift_amount(p->num) = x-h;
			}
			auto delta = round((w-a)/2.0+h*t-x*s);
			auto r = new KernNode(delta, acc_kern);
			tail->link = r;
			r->link = p;
			tail = new KernNode(-a-delta, acc_kern);
			p->link = tail;
			p = q;
		}
		tail_append(p);
		space_factor = 1000;
	}
}
