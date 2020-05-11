#include "makeop.h"
#include "fetch.h"
#include "cleanbox.h"
#include "half.h"
#include "newnullbox.h"
#include "rebox.h"
#include "freenode.h"
#include "newkern.h"

scaled makeop(halfword q)
{
	if (subtype(q) == 0 && curstyle < 2)
		subtype(q) = 1;
	scaled delta;
	if (link(q+1) == 1)
	{
		fetch(q+1);
		if (curstyle < 2 && char_tag(curi) == list_tag)
		{
			auto c = rem_byte(curi);
			auto i = char_info(curf, c);
			if (i.b0 > 0)
			{
				curc = c;
				curi = i;
				subtype(q+1) = c;
			}
		}
		delta = char_italic(curf, curi);
		auto x = cleanbox(q+1, curstyle);
		if (link(q+3) && subtype(q) != 1)
		width(x) -= delta;
		shift_amount(x) = half(height(x)-depth(x))-axis_height(cursize);
		link(q+1) = 2;
		info(q+1) = x;
	}
	else
		delta = 0;
	if (subtype(q) == 1)
	{
		auto x = cleanbox(q+2, 2*(curstyle/4)+4+curstyle%2);
		auto y = cleanbox(q+1, curstyle);
		auto z = cleanbox(q+3, 2*(curstyle/4)+5);
		auto v = newnullbox();
		type(v) = vlist_node;
		width(v) = std::max(std::max(width(x), width(y)), width(z));
		x = rebox(x, width(v));
		y = rebox(y, width(v));
		z = rebox(z, width(v));
		shift_amount(x) = half(delta);
		shift_amount(z) = -shift_amount(x);
		height(v) = height(y);
		depth(v) = depth(y);
		if (link(q+2) == 0)
		{
			freenode(x, 7);
			link(v+5) = y;
		}
		else
		{
			scaled shiftup = big_op_spacing3()-depth(x);
			if (shiftup < big_op_spacing1())
				shiftup = big_op_spacing1();
			auto p = newkern(shiftup);
			link(p) = y;
			link(x) = p;
			p = newkern(big_op_spacing5());
			link(p) = x;
			list_ptr(v) = p;
			height(v) += mathex(big_op_spacing5())+height(x)+depth(x)+shiftup;
		}
		if (link(q+3) == 0)
			freenode(z, 7);
		else
		{
			scaled shiftdown = big_op_spacing4()-height(z);
			if (shiftdown < big_op_spacing2())
				shiftdown = big_op_spacing2();
			auto p = newkern(shiftdown);
			link(y) = p;
			link(p) = z;
			p = newkern(big_op_spacing5());
			link(z) = p;
			depth(v) += big_op_spacing5()+height(z)+depth(z)+shiftdown;
		}
		new_hlist(q) = v;
	}
	return delta;
}
