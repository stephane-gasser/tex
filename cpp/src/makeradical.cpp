#include "makeradical.h"
#include "cleanbox.h"
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
	auto y = vardelimiter(left_delimiter(q), cursize, height(x)+depth(x)+clr+default_rule_thickness());
	scaled delta = depth(y)-(height(x)+depth(x)+clr);
	if (delta > 0)
		clr += half(delta);
	shift_amount(y) = -(height(x)+clr);
	link(y) = overbar(x, clr, height(y));
	info(nucleus(q)) = hpack(y, 0, additional);
	link(nucleus(q)) = sub_box;
}
