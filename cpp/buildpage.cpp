#include "buildpage.h"
#include "freezepagespecs.h"
#include "deleteglueref.h"
#include "newskipparam.h"
#include "flushnodelist.h"
#include "getnode.h"
#include "ensurevbox.h"
#include "xovern.h"
#include "printnl.h"
#include "print.h"
#include "printesc.h"
#include "printint.h"
#include "error.h"
#include "xovern.h"
#include "vertbreak.h"
#include "confusion.h"
#include "badness.h"
#include "fireup.h"
#include "newspec.h"
#include "texte.h"

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
				if (pagecontents < 2)
				{
					if (pagecontents == 0)
						freezepagespecs(2);
					else
						pagecontents = 2;
					q = newskipparam(9);
					if (width(tempptr) > height(p))
						width(tempptr) -= height(p);
					else
						width(tempptr) = 0;
					link(q) = p;
					link(contrib_head) = q;
					continue;
				}
				pagesofar[1] += pagesofar[7]+height(p);
				pagesofar[7] = depth(p);
				break;
			case whatsit_node: //8
				break;
			case glue_node: //10
				if (pagecontents < 2)
				{
					link(contrib_head) = link(p);
					link(p) = 0;
					flushnodelist(p);
					continue;
				}
				if (type(pagetail) < 9)
					pi = 0;
				break;
			case kern_node: //11
				if (pagecontents < 2)
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
				if (pagecontents < 2)
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
					freezepagespecs(1);
				n = subtype(p);
				r = page_ins_head;
				while (n >= subtype(link(r)))
					r = link(r);
				if (subtype(r) != n)
				{
					q = getnode(4);
					link(q) = link(r);
					link(r) = q;
					r = q;
					subtype(r) = n;
					type(r) = hlist_node;
					ensurevbox(n);
					if (box(n) == 0)
						height(r) = 0;
					else
						height(r) = height(box(n))+depth(box(n));
					info(r+2) = 0;
					q = skip(2900);
					if (count(n) == 1000)
						h = height(r);
					else
						h = xovern(height(r), 1000)*count(n);
					pagesofar[0] -= h+width(q);
					pagesofar[2+type(q)] += depth(q);
					pagesofar[6] += height(q);
					if (subtype(q) && height(q))
					{
						printnl("! ");
						print("Infinite glue shrinkage inserted from ");
						printesc("skip");
						printint(n);
						helpptr = 3;
						helpline[2] = txt("The correction glue for page breaking with insertions");
						helpline[1] = txt("must have finite shrinkability. But you may proceed,");
						helpline[0] = txt("since the offensive shrinkability has been made finite.");
						error();
					}
				}
				if (type(r) == vlist_node)
					insertpenalties += width(p);
				else
				{
					link(r+2) = p;
					delta = pagesofar[0]-pagesofar[1]-pagesofar[7]+pagesofar[6];
					if (count(n) == 1000)
						h = height(p);
					else
						h = xovern(height(p), 1000)*count(n);
					if ((h <= 0 || h <= delta) && height(p)+height(r) <= dimen(n))
					{
						pagesofar[0] -= h;
						height(r) += height(p);
					}
					else
					{
						if (count(n) <= 0)
							w = max_dimen;
						else
						{
							w = pagesofar[0]-pagesofar[1]-pagesofar[7];
							if (count(n) != 1000)
								w = xovern(w, count(n))*1000;
						}
						if (w > dimen(n)-height(r))
							w = dimen(n)-height(r);
						q = vertbreak(info(p+4), w, depth(p));
						height(r) += bestheightplusdepth;
						if (count(n) != 1000)
							bestheightplusdepth = xovern(bestheightplusdepth, 1000)*count(n);
						pagesofar[0] -= bestheightplusdepth;
						type(r) = 1;
						link(r+1) = q;
						info(r+1) = p;
						if (q == 0)
							insertpenalties -= 10000;
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
				if (pagesofar[1] < pagesofar[0])
					if (pagesofar[3] || pagesofar[4] || pagesofar[5])
						b = 0;
					else
						b =	badness(pagesofar[0]-pagesofar[1], pagesofar[2]);
				else 
					if (pagesofar[1]-pagesofar[0] > pagesofar[6])
						b = max_dimen;
				else
						b = badness(pagesofar[1]-pagesofar[0], pagesofar[6]);
				if (b < max_dimen)
					if (pi <= -10000)
						c = pi;
					else 
						if (b < 10000)
							c = b+pi+insertpenalties;
						else
							c = 100000;
				else
					c = b;
				if (insertpenalties >= 10000)
					c = max_dimen;
				if (c <= leastpagecost)
				{
					bestpagebreak = p;
					bestsize = pagesofar[0];
					leastpagecost = c;
					r = link(page_ins_head);
					while (r != page_ins_head)
					{
						info(r+2) = link(r+2);
						r = link(r);
					}
				}
				if (c == max_dimen || pi <= -10000)
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
			pagesofar[1] += pagesofar[7]+width(q);
			pagesofar[7] = 0;
		}
		if (type(p) == glue_node)
		{
			q = info(p+1);
			pagesofar[2+type(q)] += depth(q);
			pagesofar[6] += height(q);
			if (subtype(q) && height(q))
			{
				printnl("! ");
				print("Infinite glue shrinkage found on current page");
				helpptr = 4;
				helpline[3] = txt("The page about to be output contains some infinitely");
				helpline[2] = txt("shrinkable glue, e.g., `\\vss' or `\\vskip 0pt minus 1fil'.");
				helpline[1] = txt("Such glue doesn't belong there; but you can safely proceed,");
				helpline[0] = txt("since the offensive shrinkability has been made finite.");
				error();
				r = newspec(q);
				subtype(r) = 0;
				deleteglueref(q);
				info(p+1) = r;
				q = r;
			}
			pagesofar[1] += pagesofar[7]+width(q);
			pagesofar[7] = 0;
		}
		if (pagesofar[7] > pagemaxdepth)
		{
			pagesofar[1] += pagesofar[7]-pagemaxdepth;
			pagesofar[7] = pagemaxdepth;
		}
		link(pagetail) = p;
		pagetail = p;
		link(contrib_head) = link(p);
		link(p) = 0;
	} while (link(contrib_head));
	if (nestptr == 0)
		tail = contrib_head;
	else
		nest[0].tailfield = contrib_head;
}
