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
	if (p >= himemmin)
	{
		shiftup = 0;
		shiftdown = 0;
	}
	else
	{
		auto z = hpack(p, 0, 1);
		smallnumber t;
		if (curstyle < 4)
			t = 16;
		else
			t = 32;
		shiftup = height(z)-sup_drop(t);
		shiftdown = depth(z)+sub_drop(t);
		freenode(z, 7);
	}
	scaled clr;
	halfword x;
	if (link(q+2) == 0)
	{
		x = cleanbox(q+3, 2*(curstyle/4)+5);
		width(x) += dimen_par(script_space_code);
		if (shiftdown < sub1(cursize))
			shiftdown = sub1(cursize);
		clr = height(x)-(math_x_height(cursize)*4)/5;
		if (shiftdown < clr)
			shiftdown = clr;
		shift_amount(x) = shiftdown;
	}
	else
	{
		x = cleanbox(q+2, 2*(curstyle/4)+4+(curstyle%2));
		width(x) += dimen_par(script_space_code);
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
		if (link(q+3) == 0)
			shift_amount(x) = -shiftup;
		else
		{
			auto y = cleanbox(q+3, 2*(curstyle/4)+5);
			width(y) += dimen_par(script_space_code);
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
			x = vpackage(x, 0, 1, max_dimen);
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
