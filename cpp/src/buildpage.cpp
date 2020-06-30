#include "buildpage.h"
#include "freezepagespecs.h"
#include "deleteglueref.h"
#include "newskipparam.h"
#include "flushnodelist.h"
#include "getnode.h"
#include "ensurevbox.h"
#include "xovern.h"
#include "impression.h"
#include "error.h"
#include "xovern.h"
#include "vertbreak.h"
#include "confusion.h"
#include "badness.h"
#include "fireup.h"
#include "newspec.h"
#include "texte.h"

//! Append contributions to the current page.
void buildpage(void)
{
	halfword p, q, r;
	int b, c, pi;
	unsigned char n;
	scaled delta, h, w;
	if (link(contrib_head) == 0 || outputactive)
		return;
	do
	{
		p = link(contrib_head);
		if (lastglue != empty_flag)
			deleteglueref(lastglue);
		lastpenalty = 0;
		lastkern = 0;
		if (type(p) == glue_node) //10
		{
			lastglue = info(p+1);
			link(lastglue)++;
		}
		else
		{
			lastglue = empty_flag;
			if (type(p) == penalty_node) //12
				lastpenalty = penalty(p);
			else 
				if (type(p) == kern_node) //11
					lastkern = width(p);
		}
		switch (type(p))
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
					q = newskipparam(9);
					if (width(tempptr) > height(p))
						width(tempptr) -= height(p);
					else
						width(tempptr) = 0;
					link(q) = p;
					link(contrib_head) = q;
					continue;
				}
				page_total += page_depth+height(p);
				page_depth = depth(p);
				break;
			case whatsit_node: //8
				break;
			case glue_node: //10
				if (pagecontents < box_there)
				{
					link(contrib_head) = link(p);
					link(p) = 0;
					flushnodelist(p);
					continue;
				}
				if (precedes_break(pagetail))
					pi = 0;
				break;
			case kern_node: //11
				if (pagecontents < box_there)
				{
					link(contrib_head) = link(p);
					link(p) = 0;
					flushnodelist(p);
					continue;
				}
				if (link(p) == 0)
					return;
				if (type(link(p)) == glue_node) //10
					pi = 0;
				break;
			case penalty_node: //12
				if (pagecontents < box_there)
				{
					link(contrib_head) = link(p);
					link(p) = 0;
					flushnodelist(p);
					continue;
				}
				pi = penalty(p);
				break;
			case mark_node: //4
				break;
			case ins_node: //3
				if (pagecontents == 0)
					freezepagespecs(inserts_only);
				n = subtype(p);
				r = page_ins_head;
				while (n >= subtype(link(r)))
					r = link(r);
				if (subtype(r) != n)
				{
					q = getnode(page_ins_node_size);
					link(q) = link(r);
					link(r) = q;
					r = q;
					subtype(r) = n;
					type(r) = inserting;
					ensurevbox(n);
					if (box(n) == 0)
						height(r) = 0;
					else
						height(r) = height(box(n))+depth(box(n));
					best_ins_ptr(r) = 0;
					q = skip(n);
					if (count(n) == 1000)
						h = height(r);
					else
						h = xovern(height(r), 1000)*count(n);
					page_goal -= h+width(q);
					pagesofar[2+type(q)] += depth(q);
					page_shrink += height(q);
					if (subtype(q) && height(q))
					{
						print_err("Infinite glue shrinkage inserted from "+esc("skip")+std::to_string(n));
						helpptr = 3;
						helpline[2] = "The correction glue for page breaking with insertions";
						helpline[1] = "must have finite shrinkability. But you may proceed,";
						helpline[0] = "since the offensive shrinkability has been made finite.";
						error();
					}
				}
				if (type(r) == vlist_node)
					insertpenalties += width(p);
				else
				{
					last_ins_ptr(r) = p;
					delta = page_goal-page_total-page_depth+page_shrink;
					if (count(n) == 1000)
						h = height(p);
					else
						h = xovern(height(p), 1000)*count(n);
					if ((h <= 0 || h <= delta) && height(p)+height(r) <= dimen(n))
					{
						page_goal -= h;
						height(r) += height(p);
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
						if (w > dimen(n)-height(r))
							w = dimen(n)-height(r);
						q = vertbreak(info(p+4), w, depth(p));
						height(r) += bestheightplusdepth;
						if (count(n) != 1000)
							bestheightplusdepth = xovern(bestheightplusdepth, 1000)*count(n);
						page_goal -= bestheightplusdepth;
						type(r) = 1;
						link(r+1) = q;
						info(r+1) = p;
						if (q == 0)
							insertpenalties += eject_penalty;
						else 
							if (type(q) == 12)
								insertpenalties += width(q);
					}
				}
				break;
			default: 
				confusion("page");
		}
		if ((type(p) == glue_node && type(pagetail) < 9) || (type(p) ==  kern_node && type(link(p)) == glue_node) || type(p) == penalty_node)
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
					bestpagebreak = p;
					bestsize = page_goal;
					leastpagecost = c;
					r = link(page_ins_head);
					while (r != page_ins_head)
					{
						info(r+2) = link(r+2);
						r = link(r);
					}
				}
				if (c == awful_bad || pi <= eject_penalty)
				{
					fireup(p);
					if (outputactive)
						return;
					continue;
				}
			}
		if (type(p) == kern_node)
		{
			q = p;
			page_total += page_depth+width(q);
			page_depth = 0;
		}
		if (type(p) == glue_node)
		{
			q = info(p+1);
			pagesofar[2+type(q)] += depth(q);
			page_shrink += height(q);
			if (subtype(q) && height(q))
			{
				print_err("Infinite glue shrinkage found on current page");
				helpptr = 4;
				helpline[3] = "The page about to be output contains some infinitely";
				helpline[2] = "shrinkable glue, e.g., `\\vss' or `\\vskip 0pt minus 1fil'.";
				helpline[1] = "Such glue doesn't belong there; but you can safely proceed,";
				helpline[0] = "since the offensive shrinkability has been made finite.";
				error();
				r = newspec(q);
				subtype(r) = 0;
				deleteglueref(q);
				info(p+1) = r;
				q = r;
			}
			page_total += page_depth+width(q);
			page_depth = 0;
		}
		if (page_depth > pagemaxdepth)
		{
			page_total += page_depth-pagemaxdepth;
			page_depth = pagemaxdepth;
		}
		link(pagetail) = p;
		pagetail = p;
		link(contrib_head) = link(p);
		link(p) = 0;
	} while (link(contrib_head));
	if (nestptr == 0)
		tail = contrib_head;
	else
		contrib_tail = contrib_head;
}
