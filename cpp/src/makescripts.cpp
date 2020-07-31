#include "makescripts.h"
#include "hpack.h"
#include "cleanbox.h"
#include "noeud.h"
#include "vpackage.h"
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
		auto z = hpack(p->num, 0, additional);
		smallnumber t = curstyle < script_style ? script_size : script_script_size;
		shiftup = height(z)-sup_drop(t);
		shiftdown = depth(z)+sub_drop(t);
		freenode(z, box_node_size);
	}
	scaled clr;
	halfword x;
	if (math_type(supscr(q)) == 0)
	{
		x = cleanbox(subscr(q), sub_style(curstyle));
		width(x) += script_space();
		if (shiftdown < sub1(cursize))
			shiftdown = sub1(cursize);
		clr = height(x)-(math_x_height(cursize)*4)/5;
		if (shiftdown < clr)
			shiftdown = clr;
		shift_amount(x) = shiftdown;
	}
	else
	{
		x = cleanbox(supscr(q), sup_style(curstyle));
		width(x) += script_space();
		if (curstyle%2)
			clr = sup3(cursize);
		else 
			if (curstyle < 2)
				clr = sup1(cursize);
			else
				clr = sup2(cursize);
		if (shiftup < clr)
			shiftup = clr;
		clr = depth(x)+abs(math_x_height(cursize))/4;
		if (shiftup < clr)
			shiftup = clr;
		if (math_type(subscr(q)) == 0)
			shift_amount(x) = -shiftup;
		else
		{
			auto y = cleanbox(subscr(q), sub_style(curstyle));
			width(y) += script_space();
			if (shiftdown < sub2(cursize))
				shiftdown = sub2(cursize);
			clr = 4*default_rule_thickness()-(shiftup-depth(x)-(height(y)-shiftdown));
			if (clr > 0)
			{
				shiftdown += clr;
				clr = (abs(math_x_height(cursize)*4)/5)-(shiftup-depth(x));
				if (clr > 0)
				{
					shiftup += clr;
					shiftdown -= clr;
				}
			}
			shift_amount(x) = delta;
			p = new KernNode(shiftup-depth(x)-(height(y)-shiftdown));
			link(x) = p->num;
			p->link->num = y;
			x = vpack(x, 0, additional);
			shift_amount(x) = shiftdown;
		}
	}
	if (new_hlist(q) == 0)
		new_hlist(q) = x;
	else
	{
		p->num = new_hlist(q);
		while (p->link)
			p = p->link;
		p->link->num = x;
	}
}
