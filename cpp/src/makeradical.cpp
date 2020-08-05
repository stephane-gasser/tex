#include "makeradical.h"
#include "boite.h"
#include "vardelimiter.h"
#include "half.h"
#include "overbar.h"
#include "hpack.h"
#include "police.h"

void makeradical(halfword q)
{
	auto x = cleanbox(nucleus(q), cramped_style(curstyle));
	scaled clr;
	if (curstyle < text_style)
		clr = default_rule_thickness()+abs(math_x_height(cursize))/4;
	else
	{
		clr = default_rule_thickness();
		clr += abs(clr)/4;
	}
	auto y = vardelimiter(left_delimiter(q), cursize, x->height+x->depth+clr+default_rule_thickness());
	scaled delta = y->depth-(x->height+x->depth+clr);
	if (delta > 0)
		clr += half(delta);
	y->shift_amount = -(x->height+clr);
	y->link->num = overbar(x->num, clr, y->height);
	info(nucleus(q)) = hpack(y, 0, additional)->num;
	link(nucleus(q)) = sub_box;
}
