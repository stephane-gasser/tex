#include "makefraction.h"
#include "cleanbox.h"
#include "rebox.h"
#include "half.h"
#include "noeud.h"
#include "fractionrule.h"
#include "vardelimiter.h"
#include "hpack.h"
#include "police.h"

static int num1(smallnumber c) { return mathsy(8, c); } //!< numerator shift-up in display styles
static int num2(smallnumber c) { return mathsy(9, c); } //!< numerator shift-up in non-display, non-\atop 
static int num3(smallnumber c) { return mathsy(10, c); } //!< numerator shift-up in non-display \atop
static int denom1(smallnumber c) { return mathsy(11, c); } //!< denominator shift-down in display styles
static int denom2(smallnumber c) { return mathsy(12, c); } //!< denominator shift-down in non-display styles
static int delim1(smallnumber c) { return mathsy(20, c); } //!< size of \atopwithdelims delimiters
static int delim2(smallnumber c) { return mathsy(21, c); } //!< size of \atopwithdelims delimiters in non-displays
static int denom_style(int c) { return 2*(c/2)+cramped+2-2*(c/6); }  //!< smaller, cramped
static int num_style(int c) { return c+2-2*(c/6); } //!< smaller unless already script-script

void makefraction(halfword q)
{
	if (thickness(q) == default_code)
		thickness(q) = default_rule_thickness();
	auto x = cleanbox(q+2, num_style(curstyle));
	auto z = cleanbox(q+3, denom_style(curstyle));
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
	LinkedNode *p;
	if (thickness(q) == 0)
	{
		p = new KernNode((shiftup-depth(x))-(height(z)-shiftdown));
		p->link->num = z;
	}
	else
	{
		auto y = fractionrule(thickness(q));
		p = new KernNode((axis_height(cursize)-delta)-(height(z)-shiftdown));
		link(y) = p->num;
		p->link->num = z;
		p = new KernNode((shiftup-depth(x))-(axis_height(cursize)+delta));
		p->link->num = y;
	}
	link(x) = p->num;
	list_ptr(v) = x;
	if (curstyle < 2)
		delta = delim1(cursize);
	else
		delta = delim2(cursize);
	x = vardelimiter(left_delimiter(q), cursize, delta);
	link(x) = v;
	z = vardelimiter(right_delimiter(q), cursize, delta);
	link(v) = z;
	thickness(q) = hpack(x, 0, additional);
}
