#include "makescripts.h"
#include "boite.h"
#include "noeud.h"
#include "police.h"

static int script_space(void) { return dimen_par(script_space_code); }

static int sup1(smallnumber c) { return mathsy(13, c); } //!< superscript shift-up in uncramped display style 
static int sup2(smallnumber c) { return mathsy(14, c); } //!< superscript shift-up in uncramped non-display
static int sup3(smallnumber c) { return mathsy(15, c); } //!< superscript shift-up in cramped styles
static int sub1(smallnumber c) { return mathsy(16, c); } //!< subscript shift-down if superscript is absent
static int sub2(smallnumber c) { return mathsy(17, c); } //!< subscript shift-down if superscript is present
static int sup_drop(smallnumber c) { return mathsy(18, c); } //!< superscript baseline below top of large box
static int sub_drop(smallnumber c) { return mathsy(19, c); } //!< subscript baseline below bottom of large box

void makescripts(halfword q, scaled delta)
{
	LinkedNode *p;
	p->num = new_hlist(q);
	scaled shiftup, shiftdown;
	if (p->is_char_node())
	{
		shiftup = 0;
		shiftdown = 0;
	}
	else
	{
		auto z = hpack(p, 0, additional);
		smallnumber t = curstyle < script_style ? script_size : script_script_size;
		shiftup = z->height-sup_drop(t);
		shiftdown = z->depth+sub_drop(t);
		delete z;
	}
	scaled clr;
	BoxNode *x;
	if (math_type(supscr(q)) == 0)
	{
		x = cleanbox(subscr(q), sub_style(curstyle));
		x->width += script_space();
		if (shiftdown < sub1(cursize))
			shiftdown = sub1(cursize);
		clr = x->height-(math_x_height(cursize)*4)/5;
		if (shiftdown < clr)
			shiftdown = clr;
		x->shift_amount = shiftdown;
	}
	else
	{
		x = cleanbox(supscr(q), sup_style(curstyle));
		x->width += script_space();
		if (curstyle%2)
			clr = sup3(cursize);
		else 
			if (curstyle < 2)
				clr = sup1(cursize);
			else
				clr = sup2(cursize);
		if (shiftup < clr)
			shiftup = clr;
		clr = x->depth+abs(math_x_height(cursize))/4;
		if (shiftup < clr)
			shiftup = clr;
		if (math_type(subscr(q)) == 0)
			x->shift_amount = -shiftup;
		else
		{
			auto y = cleanbox(subscr(q), sub_style(curstyle));
			y->width += script_space();
			if (shiftdown < sub2(cursize))
				shiftdown = sub2(cursize);
			clr = 4*default_rule_thickness()-(shiftup-x->depth-(y->height-shiftdown));
			if (clr > 0)
			{
				shiftdown += clr;
				clr = (abs(math_x_height(cursize)*4)/5)-(shiftup-x->depth);
				if (clr > 0)
				{
					shiftup += clr;
					shiftdown -= clr;
				}
			}
			x->shift_amount = delta;
			p = new KernNode(shiftup-x->depth-(y->height-shiftdown));
			x->link = p;
			p->link = y;
			x = vpack(x, 0, additional);
			x->shift_amount = shiftdown;
		}
	}
	if (new_hlist(q) == 0)
		new_hlist(q) = x->num;
	else
	{
		p->num = new_hlist(q);
		while (p->link)
			p = p->link;
		p->link = x;
	}
}
