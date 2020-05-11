#include "makefraction.h"
#include "cleanbox.h"
#include "rebox.h"
#include "half.h"
#include "newnullbox.h"
#include "fractionrule.h"
#include "newkern.h"
#include "vardelimiter.h"
#include "hpack.h"

void makefraction(halfword q)
{
	if (thickness(q) == default_code)
		thickness(q) = default_rule_thickness();
	auto x = cleanbox(q+2, curstyle+2-2*(curstyle/6));
	auto z = cleanbox(q+3, 2*(curstyle/2)+3-2*(curstyle/6));
	if (width(x) < width(z))
		x = rebox(x, width(z));
	else
		z = rebox(z, width(x));
	scaled shiftup, shiftdown;
	if (curstyle < 2)
	{
		shiftup = num1(cursize);
		shiftdown = denom1(cursize);
	}
	else
	{
		shiftdown = denom2(cursize);
		if (thickness(q))
			shiftup = num2(cursize);
		else
			shiftup = num3(cursize);
	}
	scaled clr, delta;
	if (thickness(q) == 0)
	{
		if (curstyle < 2)
			clr = 7*default_rule_thickness();
		else
			clr = 3*default_rule_thickness();
		delta = half(clr-((shiftup-depth(x))-(height(z)-shiftdown)));
		if (delta > 0)
		{
			shiftup += delta;
			shiftdown += delta;
		}
	}
	else
	{
		if (curstyle < 2)
			clr = 3*thickness(q);
		else
			clr = thickness(q);
		delta = half(thickness(q));
		scaled delta1 = clr-(shiftup-depth(x)-(axis_height(cursize)+delta));
		scaled delta2 = clr-(axis_height(cursize)-delta-(height(z)-shiftdown));
		if (delta1 > 0)
			shiftup += delta1;
		if (delta2 > 0)
			shiftdown += delta2;
	}
	auto v = newnullbox();
	type(v) = vlist_node;
	height(v) = shiftup+height(x);
	depth(v) = depth(z)+shiftdown;
	width(v) = width(x);
	halfword p;
	if (thickness(q) == 0)
	{
		p = newkern((shiftup-depth(x))-(height(z)-shiftdown));
		link(p) = z;
	}
	else
	{
		auto y = fractionrule(thickness(q));
		p = newkern((axis_height(cursize)-delta)-(height(z)-shiftdown));
		link(y) = p;
		link(p) = z;
		p = newkern((shiftup-depth(x))-(axis_height(cursize)+delta));
		link(p) = y;
	}
	link(x) = p;
	list_ptr(v) = x;
	if (curstyle < 2)
		delta = delim1(cursize);
	else
		delta = delim2(cursize);
	x = vardelimiter(left_delimiter(q), cursize, delta);
	link(x) = v;
	z = vardelimiter(right_delimiter(q), cursize, delta);
	link(v) = z;
	thickness(q) = hpack(x, 0, 1);
}
