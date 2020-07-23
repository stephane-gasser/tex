#include "mlisttohlist.h"
#include "xovern.h"
#include "makefraction.h"
#include "hpack.h"
#include "makeop.h"
#include "makeradical.h"
#include "makeover.h"
#include "makeunder.h"
#include "makemathaccent.h"
#include "makevcenter.h"
#include "mathglue.h"
#include "deleteglueref.h"
#include "mathkern.h"
#include "erreur.h"
#include "fetch.h"
#include "hpack.h"
#include "makeord.h"
#include "makescripts.h"
#include "noeud.h"
#include "makeleftright.h"
#include "police.h"

constexpr char math_spacing[] = "0234000122*4000133**3**344*0400400*000000234000111*1111112341011";

static void choose_mlist(halfword &p, halfword q, halfword& (*f)(halfword))
{
	p = f(q);
	f(q) = 0;
}

static int bin_op_penalty(void) { return int_par(bin_op_penalty_code); }
static int rel_penalty(void) { return int_par(rel_penalty_code); }

void mlisttohlist(void)
{
	halfword p, x, y, z;
	scaled delta;
	smallnumber s, t, savestyle;
	auto mlist = curmlist;
	auto penalties = mlistpenalties;
	auto style = curstyle;
	auto q = mlist;
	halfword r = 0;
	smallnumber rtype = 17;
	scaled maxh = 0;
	scaled maxd = 0;
	cursize = curstyle < 4 ? 0 : 16*((curstyle-2)/2);
	curmu = xovern(math_quad(cursize), 18);
	while (q)
	{
		delta = 0;
		switch (type(q))
		{
			case bin_noad: 
				switch (rtype)
				{
					case bin_noad:
					case op_noad:
					case rel_noad:
					case open_noad:
					case punct_noad:
					case left_noad:
						type(q) = ord_noad;
						continue;
				}
				break;
			case rel_noad:
			case close_noad:
			case punct_noad:
			case right_noad:
				if (rtype == bin_noad)
					type(r) = ord_noad;
				if (type(q) == right_noad)
				{
					r = q;
					rtype = type(r);
					q = link(q);
					continue;
				}
				break;
			case left_noad: 
				r = q;
				rtype = type(r);
				q = link(q);
				continue;
			case fraction_noad:
				makefraction(q);
				z = hpack(new_hlist(q), 0, additional);
				if (height(z) > maxh)
					maxh = height(z);
				if (depth(z) > maxd)
					maxd = depth(z);
				freenode(z, box_node_size);
				r = q;
				rtype = type(r);
				q = link(q);
				continue;
			case op_noad:
				delta = makeop(q);
				if (subtype(q) == 1)
				{
					z = hpack(new_hlist(q), 0, additional);
					if (height(z) > maxh)
						maxh = height(z);
					if (depth(z) > maxd)
						maxd = depth(z);
					freenode(z, box_node_size);
					r = q;
					rtype = type(r);
					q = link(q);
					continue;
				}
				break;
			case ord_noad: 
				makeord(q);
				break;
			case open_noad:
			case inner_noad: 
				break;
			case radical_noad: 
				makeradical(q);
				break;
			case over_noad: 
				makeover(q);
				break;
			case under_noad: 
				makeunder(q);
				break;
			case accent_noad: 
				makemathaccent(q);
				break;
			case vcenter_noad: 
				makevcenter(q);
				break;
			case style_node:
				curstyle = subtype(q);
				if (curstyle < script_style)
					cursize = text_size;
				else
					cursize = 16*((curstyle-2)/2);
				curmu = xovern(math_quad(cursize), 18);
				q = link(q);
				continue;
				break;
			case choice_node:
				switch (curstyle/2)
				{
					case 0:
						choose_mlist(p, q, display_mlist); 
						break;
					case 1:
						choose_mlist(p, q, text_mlist);
						break;
					case 2:
						choose_mlist(p, q, script_mlist);
						break;
					case 3:
						choose_mlist(p, q, script_script_mlist);
				}
				flushnodelist(display_mlist(q));
				flushnodelist(text_mlist(q));
				flushnodelist(script_mlist(q));
				flushnodelist(script_script_mlist(q));
				type(q) = style_node;
				subtype(q) = curstyle;
				width(q) = 0;
				depth(q) = 0;
				if (p)
				{
					z = link(q);
					link(q) = p;
					while (link(p))
						p = link(p);
					link(p) = z;
				}
				q = link(q);
				continue;
			case ins_node:
			case mark_node:
			case adjust_node:
			case whatsit_node:
			case penalty_node:
			case disc_node: 
				q = link(q);
				continue;
			case rule_node:
				if (height(q) > maxh)
					maxh = height(q);
				if (depth(q) > maxd)
					maxd = depth(q);
				q = link(q);
				continue;
			case glue_node:

				if (subtype(q) == mu_glue)
				{
					x = glue_ptr(q);
					y = mathglue(x, curmu);
					deleteglueref(x);
					glue_ptr(q) = y;
					subtype(q) = 0;
				}
				else 
					if (cursize && subtype(q) == cond_math_glue)
					{
						p = link(q);
						if (p)
							if (type(p) == glue_node || type(p) == kern_node)
							{
								link(q) = link(p);
								link(p) = 0;
								flushnodelist(p);
							}
					}
				q = link(q);
				continue;
			case kern_node:
				mathkern(q, curmu);
				q = link(q);
				continue;
			default: 
				confusion("mlist1");
		}
		switch (math_type(nucleus(q)))
		{
			case math_char:
			case math_text_char:
				fetch(nucleus(q));
				if (char_exists(curi))
				{
					delta = char_italic(curf, curi);
					p = newcharacter(curf, curc);
					if (math_type(nucleus(q)) == math_text_char && space(curf))
						delta = 0;
					if (math_type(subscr(q)) == 0 && delta)
					{
						link(p) = newkern(delta);
						delta = 0;
					}
				}
				else
					p = 0;
				break;
			case 0: 
				p = 0;
				break;
			case sub_box: 
				p = info(nucleus(q));
				break;
			case sub_mlist:
				curmlist = info(nucleus(q));
				savestyle = curstyle;
				mlistpenalties = false;
				mlisttohlist();
				curstyle = savestyle;
				if (curstyle < script_style)
					cursize = text_size;
				else
					cursize = 16*((curstyle-text_style)/2);
				curmu = xovern(math_quad(cursize), 18);
				p = hpack(link(temp_head), 0, additional);
				break;
			default: 
				confusion("mlist2");
		}
		new_hlist(q) = p;
		if (math_type(subscr(q)) || math_type(supscr(q)))
			makescripts(q, delta);
		z = hpack(new_hlist(q), 0, additional);
		if (height(z) > maxh)
			maxh = height(z);
		if (depth(z) > maxd)
			maxd = depth(z);
		freenode(z, box_node_size);
		r = q;
		rtype = type(r);
		q = link(q);
	}
	if (rtype == bin_noad)
		type(r) = ord_noad;
	p = temp_head;
	link(p) = 0;
	q = mlist;
	rtype = 0;
	curstyle = style;
	if (curstyle < script_style)
		cursize = text_size;
	else
		cursize = 16*((curstyle-text_style)/2);
	curmu = xovern(math_quad(cursize), 18);
	while (q)
	{
		t = ord_noad;
		s = noad_size;
		int pen = inf_penalty;
		switch (type(q))
		{
			case op_noad:
			case open_noad:
			case close_noad:
			case punct_noad:
			case inner_noad: 
				t = type(q);
				break;
			case bin_noad:
				t = bin_noad;
				pen = bin_op_penalty();
				break;
			case rel_noad:
				t = rel_noad;
				pen = rel_penalty();
				break;
			case ord_noad:
			case vcenter_noad:
			case over_noad:
			case under_noad:
				break;
			case radical_noad: 
				s = radical_noad_size;
				break;
			case accent_noad:
				s = accent_noad_size;
				break;
			case fraction_noad:
				t = inner_noad;
				s = fraction_noad_size;
				break;
			case left_noad:
			case right_noad: 
				t = makeleftright(q, style, maxd, maxh);
				break;
			case style_node:
				curstyle = type(q);
				s = style_node_size;
				if (curstyle < script_style)
					cursize = text_size;
				else
					cursize = 16*((curstyle-2)/2);
				curmu = xovern(math_quad(cursize), 18);
				r = q;
				q = link(q);
				freenode(r, s);
				continue;
				break;
			case whatsit_node:
			case penalty_node:
			case rule_node:
			case disc_node:
			case adjust_node:
			case ins_node:
			case mark_node:
			case glue_node:
			case kern_node:
				link(p) = q;
				p = q;
				q = link(q);
				link(p) = 0;
				continue;
			default: 
				confusion("mlist3");
		}
		if (rtype > 0)
		{
			switch (math_spacing[(rtype-ord_noad)*8+t-ord_noad])
			{
				case '0': 
					x = 0;
					break;
				case '1': 
					x = curstyle < script_style ? thin_mu_skip_code : 0;
					break;
				case '2': 
					x = thin_mu_skip_code;
					break;
				case '3': 
					x = curstyle < script_style ? med_mu_skip_code : 0;
					break;
				case '4': 
					x = curstyle < script_style ? thick_mu_skip_code: 0;
					break;
				default: 
					confusion("mlist4");
			}
			if (x)
			{
				y = mathglue(glue_par(x), curmu);
				z = newglue(y);
				glue_ref_count(y) = 0;
				link(p) = z;
				p = z;
				subtype(z) = x+1;
			}
		}
		if (new_hlist(q))
		{
			link(p) = new_hlist(q);
			do
				p = link(p);
			while (link(p));
		}
		if (penalties && link(q) && pen < inf_penalty)
		{
			rtype = type(link(q));
			if (rtype != penalty_node && rtype != rel_noad)
			{
				z = newpenalty(pen);
				link(p) = z;
				p = z;
			}
		}
		rtype = t;
	}
}
