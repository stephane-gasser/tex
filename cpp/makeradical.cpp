#include "makeradical.h"
#include "cleanbox.h"
#include "vardelimiter.h"
#include "half.h"
#include "overbar.h"
#include "hpack.h"

void makeradical(halfword q)
{
	auto x = cleanbox(q+1, 2 *(curstyle/2)+1);
	scaled clr;
	if (curstyle < 2)
		clr = default_rule_thickness()+abs(math_x_height(cursize))/4;
	else
	{
		clr = default_rule_thickness();
		clr += abs(clr)/4;
	}
	auto y = vardelimiter(q+4, cursize, height(x)+depth(x)+clr+default_rule_thickness());
	scaled delta = depth(y)-(height(x)+depth(x)+clr);
	if (delta > 0)
		clr += half(delta);
	shift_amount(y) = -(height(x)+clr);
	link(y) = overbar(x, clr, height(y));
	info(nucleus(q)) = hpack(y, 0, 1);
	link(nucleus(q)) = sub_box;
}
