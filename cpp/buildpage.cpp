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
		if (lastglue != 65535)
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
			lastglue = 65535;
			if (type(p) == penalty_node) //12
				lastpenalty = mem[p+1].int_;
			else 
				if (mem[p].hh.b0 == kern_node) //11
					lastkern = mem[p+1].int_;
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
					if (mem[tempptr+1].int_ > mem[p+3].int_)
						mem[tempptr+1].int_ -= mem[p+3].int_;
					else
						mem[tempptr+1].int_ = 0;
					link(q) = p;
					link(contrib_head) = q;
					continue;
				}
				pagesofar[1] += pagesofar[7]+mem[p+3].int_;
				pagesofar[7] = mem[p+2].int_;
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
				pi = mem[p+1].int_;
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
					type(r) = 0;
					ensurevbox(n);
					if (box(n) == 0)
						mem[r+3].int_ = 0;
					else
						mem[r+3].int_ = mem[box(n)+3].int_+mem[box(n)+2].int_;
					info(r+2) = 0;
					q = skip(2900);
					if (count(n) == 1000)
						h = mem[r+3].int_;
					else
						h = xovern(mem[r+3].int_, 1000)*count(n);
					pagesofar[0] -= h+mem[q+1].int_;
					pagesofar[2+type(q)] += mem[q+2].int_;
					pagesofar[6] += mem[q+3].int_;
					if (subtype(q) && mem[q+3].int_)
					{
						if (interaction == 3)
							printnl(262); //! 
						print(997); //Infinite glue shrinkage inserted from 
						printesc(395); //skip
						printint(n);
						helpptr = 3;
						helpline[2] = 998; //The correction glue for page breaking with insertions
						helpline[1] = 999; //must have finite shrinkability. But you may proceed,
						helpline[0] = 921; //since the offensive shrinkability has been made finite.
						error();
					}
				}
				if (type(r) == 1)
					insertpenalties += mem[p+1].int_;
				else
				{
					link(r+2) = p;
					delta = pagesofar[0]-pagesofar[1]-pagesofar[7]+pagesofar[6];
					if (count(n) == 1000)
						h = mem[p+3].int_;
					else
						h = xovern(mem[p+3].int_, 1000)*count(n);
					if ((h <= 0 || h <= delta) && mem[p+3].int_+mem[r+3].int_ <= dimen(n))
					{
						pagesofar[0] -= h;
						mem[r+3].int_ += mem[p+3].int_;
					}
					else
					{
						if (count(n) <= 0)
							w = 1073741823;
						else
						{
							w = pagesofar[0]-pagesofar[1]-pagesofar[7];
							if (count(n) != 1000)
								w = xovern(w, count(n))*1000;
						}
						if (w > dimen(n)-mem[r+3].int_)
							w = dimen(n)-mem[r+3].int_;
						q = vertbreak(info(p+4), w, mem[p+2].int_);
						mem[r+3].int_ += bestheightplusdepth;
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
								insertpenalties += mem[q+1].int_;
					}
				}
				break;
			default: 
				confusion(992); //page
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
						b = 1073741823;
				else
						b = badness(pagesofar[1]-pagesofar[0], pagesofar[6]);
				if (b < 1073741823)
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
					c = 1073741823;
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
				if (c == 1073741823 || pi <= -10000)
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
			pagesofar[1] += pagesofar[7]+mem[q+1].int_;
			pagesofar[7] = 0;
		}
		if (type(p) == glue_node)
		{
			q = info(p+1);
			pagesofar[2+type(q)] += mem[q+2].int_;
			pagesofar[6] += mem[q+3].int_;
			if (subtype(q) && mem[q+3].int_)
			{
				if (interaction == 3)
					printnl(262); //! 
				print(993); //Infinite glue shrinkage found on current page
				helpptr = 4;
				helpline[3] = 994; //The page about to be output contains some infinitely
				helpline[2] = 962; //shrinkable glue, e.g., `\vss' or `\vskip 0pt minus 1fil'.
				helpline[1] = 963; //Such glue doesn't belong there; but you can safely proceed,
				helpline[0] = 921; //since the offensive shrinkability has been made finite.
				error();
				r = newspec(q);
				subtype(r) = 0;
				deleteglueref(q);
				info(p+1) = r;
				q = r;
			}
			pagesofar[1] += pagesofar[7]+mem[q+1].int_;
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
		curlist.tailfield = contrib_head;
	else
		nest[0].tailfield = contrib_head;
}
