#include "mlisttohlist.h"
#include "xovern.h"
#include "makefraction.h"
#include "hpack.h"
#include "freenode.h"
#include "makeop.h"
#include "makeradical.h"
#include "makeover.h"
#include "makeunder.h"
#include "makemathaccent.h"
#include "makevcenter.h"
#include "flushnodelist.h"
#include "mathglue.h"
#include "deleteglueref.h"
#include "mathkern.h"
#include "confusion.h"
#include "fetch.h"
#include "newcharacter.h"
#include "hpack.h"
#include "makeord.h"
#include "makescripts.h"
#include "freenode.h"
#include "newkern.h"
#include "newglue.h"
#include "newpenalty.h"
#include "makeleftright.h"

void mlisttohlist(void)
{
	halfword p, x, y, z;
	int pen;
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
	if (curstyle < 4)
		cursize = 0;
	else
		cursize = 16*((curstyle-2)/2);
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
				z = hpack(new_hlist(q), 0, 1);
				if (height(z) > maxh)
					maxh = height(z);
				if (depth(z) > maxd)
					maxd = depth(z);
				freenode(z, 7);
				r = q;
				rtype = type(r);
				q = link(q);
				continue;
			case op_noad:
				delta = makeop(q);
				if (subtype(q) == 1)
				{
					z = hpack(new_hlist(q), 0, 1);
					if (height(z) > maxh)
						maxh = height(z);
					if (depth(z) > maxd)
						maxd = depth(z);
					freenode(z, 7);
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
				if (curstyle < 4)
					cursize = 0;
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
						p = display_mlist(q);
						display_mlist(q) = 0;
						break;
					case 1:
						p = text_mlist(q);
						text_mlist(q) = 0;
						break;
					case 2:
						p = script_mlist(q);
						script_mlist(q) = 0;
						break;
					case 3:
						p = script_script_mlist(q);
						script_script_mlist(q) = 0;
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
				confusion(888); //mlist1
		}
		switch (link(q+1))
		{
			case 1:
			case 4:
				fetch(q+1);
				if (curi.b0 > 0)
				{
					delta = char_italic(curf, curi);
					p = newcharacter(curf, curc);
					if (link(q+1) == 4 && param(space_code, curf))
						delta = 0;
					if (link(q+3) == 0 && delta)
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
			case 2: 
				p = info(q+1);
				break;
			case 3:
				curmlist = info(q+1);
				savestyle = curstyle;
				mlistpenalties = false;
				mlisttohlist;
				curstyle = savestyle;
				if (curstyle < 4)
					cursize = 0;
				else
					cursize = 16*((curstyle-2)/2);
				curmu = xovern(math_quad(cursize), 18);
				p = hpack(link(temp_head), 0, 1);
				break;
			default: 
				confusion(889); //mlist2
		}
		new_hlist(q) = p;
		if (link(q+3) || link(q+2))
			makescripts(q, delta);
		z = hpack(new_hlist(q), 0, 1);
		if (height(z) > maxh)
			maxh = height(z);
		if (depth(z) > maxd)
			maxd = depth(z);
		freenode(z, 7);
		r = q;
		rtype = type(r);
		q = link(q);
	}
	if (rtype == 18)
		type(r) = 16;
	p = temp_head;
	link(p) = 0;
	q = mlist;
	rtype = 0;
	curstyle = style;
	if (curstyle < 4)
		cursize = 0;
	else
		cursize = 16*((curstyle-2)/2);
	curmu = xovern(math_quad(cursize), 18);
	while (q)
	{
		t = 16;
		s = 4;
		pen = 10000;
		switch (type(q))
		{
			case 17:
			case 20:
			case 21:
			case 22:
			case 23: 
				t = type(q);
				break;
			case 18:
				t = 18;
				pen = int_par(bin_op_penalty_code);
				break;
			case 19:
				t = 19;
				pen = int_par(rel_penalty_code);
				break;
			case 16:
			case 29:
			case 27:
			case 26:
				break;
			case 24: 
				s = 5;
				break;
			case 28:
				s = 5;
				break;
			case 25:
				t = 23;
				s = 6;
				break;
			case 30:
			case 31: 
				t = makeleftright(q, style, maxd, maxh);
				break;
			case 14:
				curstyle = type(q);
				s = 3;
				if (curstyle < 4)
					cursize = 0;
				else
					cursize = 16*((curstyle-2)/2);
				curmu = xovern(math_quad(cursize), 18);
				r = q;
				q = link(q);
				freenode(r, s);
				continue;
				break;
			case 8:
			case 12:
			case 2:
			case 7:
			case 5:
			case 3:
			case 4:
			case 10:
			case 11:
				link(p) = q;
				p = q;
				q = link(q);
				link(p) = 0;
				continue;
			default: 
				confusion(890); //mlist3
		}
		if (rtype > 0)
		{
			switch (strpool[rtype*8+t+magicoffset])
			{
				case 48: 
					x = 0;
					break;
				case 49: 
					if (curstyle < 4)
						x = 15;
					else
						x = 0;
					break;
				case 50: 
					x = 15;
					break;
				case 51: 
					if (curstyle < 4)
						x = 16;
					else
						x = 0;
					break;
				case 52: 
					if (curstyle < 4)
						x = 17;
					else
						x = 0;
					break;
				default: 
					confusion(892); //mlist4
			}
			if (x)
			{
				y = mathglue(glue_par(x), curmu);
				z = newglue(y);
				link(y) = 0;
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
		if (penalties && link(q) && pen < 10000)
		{
			rtype = type(link(q));
			if (rtype != 12 && rtype != 19)
			{
				z = newpenalty(pen);
				link(p) = z;
				p = z;
			}
		}
		rtype = t;
	}
}
