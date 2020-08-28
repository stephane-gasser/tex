#include "buildpage.h"
#include "freezepagespecs.h"
#include "deleteglueref.h"
#include "xovern.h"
#include "impression.h"
#include "erreur.h"
#include "xovern.h"
#include "vertbreak.h"
#include "badness.h"
#include "fireup.h"
#include "noeud.h"
#include "texte.h"
#include "boite.h"

//! Append contributions to the current page.
void buildpage(void)
{
	LinkedNode *p, *q, *r;
	int b, c, pi;
	unsigned char n;
	scaled delta, h, w;
	if (contrib_head->link == nullptr || outputactive)
		return;
	while (contrib_head->link)
	{
		p = contrib_head->link;
		if (lastglue)
		{
			delete lastglue;
			lastglue = nullptr;
		}
		lastpenalty = 0;
		lastkern = 0;
		if (p->type == glue_node) //10
		{
			lastglue = dynamic_cast<GlueNode*>(p)->glue_ptr;
			lastglue->glue_ref_count++;
		}
		else
		{
			lastglue = nullptr;
			if (p->type == penalty_node) //12
				lastpenalty = dynamic_cast<PenaltyNode*>(p)->penalty;
			else 
				if (p->type == kern_node) //11
					lastkern = dynamic_cast<KernNode*>(p)->width;
		}
		switch (p->type)
		{
			case hlist_node: //0
			case vlist_node: //1
			case rule_node:  //2
				if (pagecontents < box_there)
				{
					if (pagecontents == 0)
						freezepagespecs(box_there);
					else
						pagecontents = box_there;
					q = newskipparam(top_skip_code);
					auto g = dynamic_cast<GlueNode*>(q)->glue_ptr;
					if (g->width > height(p->num))
						g->width -= height(p->num);
					else
						g->width = 0;
					q->link = p;
					contrib_head->link = q;
					continue;
				}
				page_total += page_depth+height(p->num);
				page_depth = depth(p->num);
				break;
			case whatsit_node: //8
				break;
			case glue_node: //10
				if (pagecontents < box_there)
				{
					contrib_head->link = p->link;
					p->link = nullptr;
					flushnodelist(p);
					continue;
				}
				if (precedes_break(pagetail->num))
					pi = 0;
				break;
			case kern_node: //11
				if (pagecontents < box_there)
				{
					contrib_head->link = p->link;
					p->link = nullptr;
					flushnodelist(p);
					continue;
				}
				if (p->link == nullptr)
					return;
				if (p->link->type == glue_node) //10
					pi = 0;
				break;
			case penalty_node: //12
				if (pagecontents < box_there)
				{
					contrib_head->link = p->link;
					p->link = nullptr;
					flushnodelist(p);
					continue;
				}
				pi = dynamic_cast<PenaltyNode*>(p)->penalty;
				break;
			case mark_node: //4
				break;
			case ins_node: //3
			{
				auto P = dynamic_cast<InsNode*>(p);
				if (pagecontents == 0)
					freezepagespecs(inserts_only);
				n = P->subtype;
				r = page_ins_head;
				while (n >= dynamic_cast<InsNode*>(r->link)->subtype)
					next(r);
				if (dynamic_cast<PageInsNode*>(r)->subtype != n)
				{
					auto Q = new PageInsNode;
					Q->link = r->link;
					r->link = Q;
					r = Q; //r: PageInsNode
					Q->subtype = n;
					r->type = inserting;
					ensurevbox(n);
					if (box[n] == nullptr)
						Q->height = 0;
					else
						Q->height = box[n]->height+box[n]->depth;
					Q->best_ins_ptr = 0;
					auto q = skip[n];
					if (count(n) == 1000)
						h = Q->height;
					else
						h = xovern(Q->height, 1000)*count(n);
					page_goal -= h+q->width;
					pagesofar[2+q->stretch_order] += q->stretch;
					page_shrink += q->shrink;
					if (q->shrink_order && q->shrink)
						error("Infinite glue shrinkage inserted from "+esc("skip")+std::to_string(n), "The correction glue for page breaking with insertions\nmust have finite shrinkability. But you may proceed,\nsince the offensive shrinkability has been made finite.");
				}
				if (r->type == split_up)
					insertpenalties += P->float_cost;
				else
				{
					auto R = dynamic_cast<PageInsNode*>(r);
					R->last_ins_ptr = p;
					delta = page_goal-page_total-page_depth+page_shrink;
					if (count(n) == 1000)
						h = P->height;
					else
						h = xovern(P->height, 1000)*count(n);
					if ((h <= 0 || h <= delta) && P->height+R->height <= dimen(n))
					{
						page_goal -= h;
						R->height += P->height;
					}
					else
					{
						if (count(n) <= 0)
							w = max_dimen;
						else
						{
							w = page_goal-page_total-page_depth;
							if (count(n) != 1000)
								w = xovern(w, count(n))*1000;
						}
						if (w > dimen(n)-height(r->num))
							w = dimen(n)-height(r->num);
						q->num = vertbreak(info(p->num+4), w, depth(p->num));
						R->height += bestheightplusdepth;
						if (count(n) != 1000)
							bestheightplusdepth = xovern(bestheightplusdepth, 1000)*count(n);
						page_goal -= bestheightplusdepth;
						r->type = split_up;
						R->broken_ptr = q;
						R->broken_ins = p;
						if (q == nullptr)
							insertpenalties += eject_penalty;
						else 
							if (q->type == penalty_node)
								insertpenalties += dynamic_cast<PenaltyNode*>(q)->penalty;
					}
				}
				break;
			}
			default: 
				confusion("page");
		}
		if ((p->type == glue_node && precedes_break(pagetail->num)) || (p->type ==  kern_node && p->link->type == glue_node) || p->type == penalty_node)
			if (pi < 10000)
			{
				if (page_total < page_goal)
					if (pagesofar[3] || pagesofar[4] || pagesofar[5])
						b = 0;
					else
						b =	badness(page_goal-page_total, pagesofar[2]);
				else 
					if (page_total-page_goal > page_shrink)
						b = max_dimen;
				else
						b = badness(page_total-page_goal, page_shrink);
				if (b < max_dimen)
					if (pi <= eject_penalty)
						c = pi;
					else 
						if (b < inf_bad)
							c = b+pi+insertpenalties;
						else
							c = deplorable;
				else
					c = b;
				if (insertpenalties >= 10000)
					c = awful_bad;
				if (c <= leastpagecost)
				{
					bestpagebreak = p->num;
					bestsize = page_goal;
					leastpagecost = c;
					r = page_ins_head->link;
					while (r != page_ins_head)
					{
						best_ins_ptr(r->num) = last_ins_ptr(r->num);
						next(r);
					}
				}
				if (c == awful_bad || pi <= eject_penalty)
				{
					fireup(p->num);
					if (outputactive)
						return;
					continue;
				}
			}
		if (p->type == kern_node)
		{
			q = p;
			page_total += page_depth+width(q->num);
			page_depth = 0;
		}
		if (p->type == glue_node)
		{
			auto q = dynamic_cast<GlueNode*>(p)->glue_ptr;
			pagesofar[2+q->stretch_order] += q->stretch;
			page_shrink += q->shrink;
			if (q->shrink_order && q->shrink)
			{
				error("Infinite glue shrinkage found on current page", "The page about to be output contains some infinitely\nshrinkable glue, e.g., `\\vss' or `\\vskip 0pt minus 1fil'.\nSuch glue doesn't belong there; but you can safely proceed,\nsince the offensive shrinkability has been made finite.");
				auto r = new GlueSpec(q);
				r->shrink_order = normal;
				deleteglueref(q);
				dynamic_cast<GlueNode*>(p)->glue_ptr = r;
				q = r;
			}
			page_total += page_depth+q->width;
			page_depth = 0;
		}
		if (page_depth > pagemaxdepth)
		{
			page_total += page_depth-pagemaxdepth;
			page_depth = pagemaxdepth;
		}
		pagetail->link = p;
		pagetail = p;
		contrib_head->link = p->link;
		p->link = nullptr;
	}
	if (nestptr == 0)
		tail = contrib_head;
	else
		contrib_tail = contrib_head;
}
