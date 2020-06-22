#include "makescripts.h"
#include "hpack.h"
#include "cleanbox.h"
#include "freenode.h"
#include "newkern.h"
#include "vpackage.h"

void makescripts(halfword q, scaled delta)
{
	halfword p = new_hlist(q);
	scaled shiftup, shiftdown;
	if (is_char_node(p))
	{
		shiftup = 0;
		shiftdown = 0;
	}
	else
	{
		auto z = hpack(p, 0, additional);
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
			p = newkern(shiftup-depth(x)-(height(y)-shiftdown));
			link(x) = p;
			link(p) = y;
			x = vpack(x, 0, additional);
			shift_amount(x) = shiftdown;
		}
	}
	if (new_hlist(q) == 0)
		new_hlist(q) = x;
	else
	{
		p = new_hlist(q);
		while (link(p))
			p = link(p);
		link(p) = x;
	}
}
