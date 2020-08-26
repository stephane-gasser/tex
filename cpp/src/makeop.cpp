#include "makeop.h"
#include "fetch.h"
#include "boite.h"
#include "half.h"
#include "noeud.h"
#include "police.h"

static int big_op_spacing1(void) { return mathex(9); } //!< minimum clearance above a displayed op
static int big_op_spacing2(void) { return mathex(10); } //!< minimum clearance below a displayed op
static int big_op_spacing3(void) { return mathex(11); } //!< minimum baselineskip above displayed op
static int big_op_spacing4(void) { return mathex(12); } //!< minimum baselineskip below displayed op
static int big_op_spacing5(void) { return mathex(13); } //!< padding above and below displayed limits


scaled makeop(halfword q)
{
	Noad *Q;
	Q->num = q;
	if (Q->subtype == normal && curstyle < text_style)
		Q->subtype = limits;
	scaled delta;
	if (Q->nucleus.math_type == math_char)
	{
		auto [ft, curc] = fetch(nucleus(q));
		if (curstyle < text_style && char_tag(ft.char_info(curc)) == list_tag)
		{
			auto c = rem_byte(ft.char_info(curc));
			if (char_exists(ft.char_info(c)))
			{
				curc = c;
				Q->nucleus.character = c;
			}
		}
		delta = ft.char_italic(curc);
		auto x = cleanbox(nucleus(q), curstyle);
		if (Q->subscr.math_type && Q->subtype != limits)
		x->width -= delta;
		x->shift_amount = half(x->height-x->depth)-axis_height(cursize);
		Q->nucleus.math_type = sub_box;
		Q->nucleus.info = x;
	}
	else
		delta = 0;
	if (Q->subtype == limits)
	{
		auto x = cleanbox(supscr(q), sup_style(curstyle));
		auto y = cleanbox(nucleus(q), curstyle);
		auto z = cleanbox(subscr(q), sub_style(curstyle));
		auto v = new BoxNode;
		v->type = vlist_node;
		v->width = std::max(std::max(x->width, y->width), z->width);
		x = rebox(x, v->width);
		y = rebox(y, v->width);
		z = rebox(z, v->width);
		x->shift_amount = half(delta);
		z->shift_amount = -x->shift_amount;
		v->height = y->height;
		v->depth = y->depth;
		if (Q->supscr.math_type == 0)
		{
			delete x;
			v->list_ptr = y;
		}
		else
		{
			scaled shiftup = big_op_spacing3()-x->depth;
			if (shiftup < big_op_spacing1())
				shiftup = big_op_spacing1();
			auto p = new KernNode(shiftup);
			p->link = y;
			x->link = p;
			p = new KernNode(big_op_spacing5());
			p->link = x;
			v->list_ptr = p;
			v->height += mathex(big_op_spacing5())+x->height+x->depth+shiftup;
		}
		if (Q->subscr.math_type == 0)
			delete z;
		else
		{
			scaled shiftdown = big_op_spacing4()-z->height;
			if (shiftdown < big_op_spacing2())
				shiftdown = big_op_spacing2();
			auto p = new KernNode(shiftdown);
			y->link = p;
			p->link = z;
			p = new KernNode(big_op_spacing5());
			z->link = p;
			v->depth += big_op_spacing5()+z->height+z->depth+shiftdown;
		}
		new_hlist(q) = v->num;
	}
	return delta;
}
