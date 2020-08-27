#include "makefraction.h"
#include "boite.h"
#include "half.h"
#include "noeud.h"
#include "fractionrule.h"
#include "vardelimiter.h"
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
	FractionNoad *Q;
	Q->num = q;
	if (Q->thickness == default_code)
		Q->thickness = default_rule_thickness();
	auto x = cleanbox(q+2, num_style(curstyle));
	auto z = cleanbox(q+3, denom_style(curstyle));
	if (x->width < z->width)
		x = rebox(x, z->width);
	else
		z = rebox(z, x->width);
	scaled shiftup, shiftdown;
	if (curstyle < 2)
	{
		shiftup = num1(cursize);
		shiftdown = denom1(cursize);
	}
	else
	{
		shiftdown = denom2(cursize);
		if (Q->thickness)
			shiftup = num2(cursize);
		else
			shiftup = num3(cursize);
	}
	scaled clr, delta;
	if (Q->thickness == 0)
	{
		if (curstyle < 2)
			clr = 7*default_rule_thickness();
		else
			clr = 3*default_rule_thickness();
		delta = half(clr-((shiftup-x->depth)-(z->height-shiftdown)));
		if (delta > 0)
		{
			shiftup += delta;
			shiftdown += delta;
		}
	}
	else
	{
		if (curstyle < 2)
			clr = 3*Q->thickness;
		else
			clr = Q->thickness;
		delta = half(Q->thickness);
		scaled delta1 = clr-(shiftup-x->depth-(axis_height(cursize)+delta));
		scaled delta2 = clr-(axis_height(cursize)-delta-(z->height-shiftdown));
		if (delta1 > 0)
			shiftup += delta1;
		if (delta2 > 0)
			shiftdown += delta2;
	}
	auto v = new BoxNode;
	v->type = vlist_node;
	v->height = shiftup+x->height;
	v->depth = z->depth+shiftdown;
	v->width = x->width;
	KernNode *p;
	if (Q->thickness == 0)
	{
		p = new KernNode((shiftup-x->depth)-(z->height-shiftdown));
		p->link = z;
	}
	else
	{
		auto y = fractionrule(Q->thickness);
		p = new KernNode((axis_height(cursize)-delta)-(z->height-shiftdown));
		y->link = p;
		p->link = z;
		p = new KernNode((shiftup-x->depth)-(axis_height(cursize)+delta));
		p->link = y;
	}
	x->link = p;
	v->list_ptr = x;
	if (curstyle < 2)
		delta = delim1(cursize);
	else
		delta = delim2(cursize);
	x = vardelimiter(Q->left_delimiter, cursize, delta);
	x->link = v;
	z = vardelimiter(Q->right_delimiter, cursize, delta);
	v->link = z;
	new_hlist(q) = hpack(x, 0, additional)->num;
}
