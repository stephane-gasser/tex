#include "makeaccent.h"
#include "lecture.h"
#include "noeud.h"
#include "doassignments.h"
#include "boite.h"
#include "police.h"
#include "etat.h"
#include "getnext.h"
#include <cmath>

void makeaccent(char status)
{
	if (auto accent = newcharacter(curFontNum(), scanner.getUChar(status)); accent)
	{
		auto t = doassignments(status);
		switch (t.cmd)
		{
			case char_num:
				t.chr = scanner.getUChar(status); [[fallthrough]];
			case letter:
			case other_char:
			case char_given:
			{
				auto x = cur_font().x_height();
				auto s = cur_font().slant()/float(unity);
				auto a = accent->width();
				auto lettre = newcharacter(curFontNum(), t.chr);
				auto t = cur_font().slant()/float(unity);
				auto w = lettre->width();
				auto h = lettre->height();
				auto delta = round((w-a)/2.0+h*t-x*s);
				tail_append(new KernNode(delta, acc_kern));
				if (h != x)
				{
					auto accentBox = hpack(accent, 0, additional);
					accentBox->shift_amount = x-h;
					tail_append(accentBox);
				}
				else
					tail_append(accent);
				tail_append(new KernNode(-a-delta, acc_kern));
				tail_append(lettre);
				break;
			}
			default:
				tail_append(accent);
				backinput(t);
		}
		space_factor = 1000;
	}
}
