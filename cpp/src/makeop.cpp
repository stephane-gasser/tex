#include "makeop.h"
#include "fetch.h"
#include "cleanbox.h"
#include "half.h"
#include "noeud.h"
#include "rebox.h"
#include "police.h"

static int big_op_spacing1(void) { return mathex(9); } //!< minimum clearance above a displayed op
static int big_op_spacing2(void) { return mathex(10); } //!< minimum clearance below a displayed op
static int big_op_spacing3(void) { return mathex(11); } //!< minimum baselineskip above displayed op
static int big_op_spacing4(void) { return mathex(12); } //!< minimum baselineskip below displayed op
static int big_op_spacing5(void) { return mathex(13); } //!< padding above and below displayed limits


scaled makeop(halfword q)
{
	if (subtype(q) == normal && curstyle < text_style)
		subtype(q) = limits;
	scaled delta;
	if (math_type(nucleus(q)) == math_char)
	{
		fetch(nucleus(q));
		if (curstyle < text_style && char_tag(curi) == list_tag)
		{
			auto c = rem_byte(curi);
			auto i = char_info(curf, c);
			if (char_exists(i))
			{
				curc = c;
				curi = i;
				character(nucleus(q)) = c;
			}
		}
		delta = char_italic(curf, curi);
		auto x = cleanbox(nucleus(q), curstyle);
		if (math_type(subscr(q)) && subtype(q) != limits)
		width(x) -= delta;
		shift_amount(x) = half(height(x)-depth(x))-axis_height(cursize);
		math_type(nucleus(q)) = sub_box;
		info(nucleus(q)) = x;
	}
	else
		delta = 0;
	if (subtype(q) == limits)
	{
		auto x = cleanbox(supscr(q), sup_style(curstyle));
		auto y = cleanbox(nucleus(q), curstyle);
		auto z = cleanbox(subscr(q), sub_style(curstyle));
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
		if (math_type(supscr(q)) == 0)
		{
			freenode(x, box_node_size);
			list_ptr(v) = y;
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
		if (math_type(subscr(q)) == 0)
			freenode(z, box_node_size);
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
