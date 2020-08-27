#include "mlisttohlist.h"
#include "xovern.h"
#include "makefraction.h"
#include "boite.h"
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
#include "makeord.h"
#include "makescripts.h"
#include "noeud.h"
#include "makeleftright.h"
#include "police.h"

constexpr char math_spacing[] = "0234000122*4000133**3**344*0400400*000000234000111*1111112341011";

static int bin_op_penalty(void) { return int_par(bin_op_penalty_code); }
static int rel_penalty(void) { return int_par(rel_penalty_code); }

void mlisttohlist(void)
{
	halfword x, y;
	scaled delta;
	smallnumber s, t, savestyle;
	auto mlist = curmlist;
	auto penalties = mlistpenalties;
	auto style = curstyle;
	LinkedNode *q;
	q->num = mlist;
	LinkedNode *r = nullptr;
	smallnumber rtype = op_noad;
	scaled maxh = 0;
	scaled maxd = 0;
	cursize = curstyle < script_style  ? 0 : 16*((curstyle-text_style)/2);
	curmu = xovern(math_quad(cursize), 18);
	quarterword curc;
	Font ft;
	LinkedNode *p;
	BoxNode *z;
	while (q)
	{
		delta = 0;
		switch (q->type)
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
						q->type = ord_noad;
						continue;
				}
				break;
			case rel_noad:
			case close_noad:
			case punct_noad:
			case right_noad:
				if (rtype == bin_noad)
					r->type = ord_noad;
				if (q->type == right_noad)
				{
					r = q;
					rtype = r->type;
					q = q->link;
					continue;
				}
				break;
			case left_noad: 
				r = q;
				rtype = r->type;
				q = q->link;
				continue;
			case fraction_noad:
			{
				makefraction(q->num);
				LinkedNode* h;
				h->num = new_hlist(q->num);
				z = hpack(h, 0, additional);
				if (z->height > maxh)
					maxh = z->height;
				if (z->depth > maxd)
					maxd = z->depth;
				delete z;
				r = q;
				rtype = r->type;
				q = q->link;
				continue;
			}
			case op_noad:
			{
				delta = makeop(q->num);
				if (subtype(q->num) == 1)
				{
					LinkedNode *h;
					h->num = new_hlist(q->num);
					z = hpack(h, 0, additional);
					if (z->height > maxh)
						maxh = z->height;
					if (z->depth > maxd)
						maxd = z->depth;
					delete z;
					r = q;
					rtype = r->type;
					q = q->link;
					continue;
				}
				break;
			}
			case ord_noad: 
				makeord(q->num);
				break;
			case open_noad:
			case inner_noad: 
				break;
			case radical_noad: 
				makeradical(q->num);
				break;
			case over_noad: 
				makeover(q->num);
				break;
			case under_noad: 
				makeunder(q->num);
				break;
			case accent_noad: 
				makemathaccent(q->num);
				break;
			case vcenter_noad: 
				makevcenter(q->num);
				break;
			case style_node:
				curstyle = dynamic_cast<StyleNode*>(q)->subtype;
				if (curstyle < script_style)
					cursize = text_size;
				else
					cursize = 16*((curstyle-2)/2);
				curmu = xovern(math_quad(cursize), 18);
				q = q->link;
				continue;
			case choice_node:
			{
				auto Q = dynamic_cast<ChoiceNode*>(q);
				switch (curstyle/2)
				{
					case 0:
						p = Q->display_mlist;
						Q->display_mlist = nullptr;
						break;
					case 1:
						p = Q->text_mlist;
						Q->text_mlist = nullptr;
						break;
					case 2:
						p = Q->script_mlist;
						Q->script_mlist = nullptr;
						break;
					case 3:
						p = Q->script_script_mlist;
						Q->script_script_mlist = nullptr;
				}
				flushnodelist(Q->display_mlist);
				flushnodelist(Q->text_mlist);
				flushnodelist(Q->script_mlist);
				flushnodelist(Q->script_script_mlist);
				// delete q ? q = new StyleNode ?
				auto st = new StyleNode(curstyle);
				q = st;
				if (p)
				{
					auto z = q->link;
					q->link = p;
					while (p->link)
						p = p->link;
					p->link = z;
				}
				q = q->link;
				continue;
			}
			case ins_node:
			case mark_node:
			case adjust_node:
			case whatsit_node:
			case penalty_node:
			case disc_node: 
				q = q->link;
				continue;
			case rule_node:
				if (height(q->num) > maxh)
					maxh = height(q->num);
				if (depth(q->num) > maxd)
					maxd = depth(q->num);
				q = q->link;
				continue;
			case glue_node:
			{
				auto Q = dynamic_cast<GlueNode*>(q);
				if (Q->subtype == mu_glue)
				{
					auto x = Q->glue_ptr;
					y = mathglue(x->num, curmu);
					deleteglueref(x);
					Q->glue_ptr->num = y;
					Q->subtype = 0;
				}
				else 
					if (cursize && Q->subtype == cond_math_glue)
					{
						p = q->link;
						if (p)
							if (p->type == glue_node || p->type == kern_node)
							{
								q->link = p->link;
								p->link = nullptr;
								flushnodelist(p);
							}
					}
				q = q->link;
				continue;
			}
			case kern_node:
				mathkern(dynamic_cast<KernNode*>(q), curmu);
				q = q->link;
				continue;
			default: 
				confusion("mlist1");
		}
		auto Q = dynamic_cast<Noad*>(q);
		switch (Q->nucleus.math_type)
		{
			case math_char:
			case math_text_char:
				std::tie(ft, curc) = fetch(Q->nucleus);
				if (char_exists(ft.char_info(curc)))
				{
					delta = ft.char_italic(curc);
					p = newcharacter(fam_fnt(Q->nucleus.fam+cursize), curc);
					if (Q->nucleus.math_type == math_text_char && ft.space())
						delta = 0;
					if (Q->subscr.math_type == 0 && delta)
					{
						p->link = new KernNode(delta);
						delta = 0;
					}
				}
				else
					p = nullptr;
				break;
			case 0: 
				p = nullptr;
				break;
			case sub_box: 
				p = Q->nucleus.info;
				break;
			case sub_mlist:
				curmlist = Q->nucleus.info->num;
				savestyle = curstyle;
				mlistpenalties = false;
				mlisttohlist();
				curstyle = savestyle;
				if (curstyle < script_style)
					cursize = text_size;
				else
					cursize = 16*((curstyle-text_style)/2);
				curmu = xovern(math_quad(cursize), 18);
				p = hpack(temp_head->link, 0, additional);
				break;
			default: 
				confusion("mlist2");
		}
		new_hlist(q->num) = p->num;
		if (math_type(subscr(q->num)) || math_type(supscr(q->num)))
			makescripts(q->num, delta);
		LinkedNode *h;
		h->num = new_hlist(q->num);
		z = hpack(h, 0, additional);
		if (z->height > maxh)
			maxh = z->height;
		if (z->depth > maxd)
			maxd = z->depth;
		delete z;
		r = q;
		rtype = r->type;
		q = q->link;
	}
	if (rtype == bin_noad)
		r->type = ord_noad;
	p = dynamic_cast<CharNode*>(temp_head);
	p->link = nullptr;
	q->num = mlist;
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
		switch (q->type)
		{
			case op_noad:
			case open_noad:
			case close_noad:
			case punct_noad:
			case inner_noad: 
				t = q->type;
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
				t = makeleftright(q->num, style, maxd, maxh);
				break;
			case style_node:
				curstyle = dynamic_cast<StyleNode*>(q)->subtype;
				s = style_node_size;
				if (curstyle < script_style)
					cursize = text_size;
				else
					cursize = 16*((curstyle-2)/2);
				curmu = xovern(math_quad(cursize), 18);
				r = q;
				q = q->link;
				delete r;
				continue;
			case whatsit_node:
			case penalty_node:
			case rule_node:
			case disc_node:
			case adjust_node:
			case ins_node:
			case mark_node:
			case glue_node:
			case kern_node:
				p->link = q;
				p = q;
				q = q->link;
				p->link = nullptr;
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
				auto g = new GlueSpec(y);
				g->glue_ref_count = 0;
				auto z = new GlueNode(g);
				z->subtype = x+1;
				p->link = z;
				p = z;
			}
		}
		if (new_hlist(q->num))
		{
			p->link->num = new_hlist(q->num);
			do
				p = p->link;
			while (p->link);
		}
		if (penalties && q->link && pen < inf_penalty)
		{
			rtype = q->link->type;
			if (rtype != penalty_node && rtype != rel_noad)
			{
				auto z = new PenaltyNode(pen);
				p->link = z;
				p = z;
			}
		}
		rtype = t;
	}
}
