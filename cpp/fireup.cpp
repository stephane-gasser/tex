#include "fireup.h"
#include "geqworddefine.h"
#include "deletetokenref.h"
#include "printnl.h"
#include "print.h"
#include "printesc.h"
#include "ensurevbox.h"
#include "boxerror.h"
#include "newnullbox.h"
#include "prunepagetop.h"
#include "vpackage.h"
#include "freenode.h"
#include "deleteglueref.h"
#include "printint.h"
#include "error.h"
#include "pushnest.h"
#include "begintokenlist.h"
#include "newsavelevel.h"
#include "normalparagraph.h"
#include "scanleftbrace.h"
#include "shipout.h"

void fireup(halfword c)
{
	halfword p, q, r, s, prevp;
	unsigned char n;
	bool wait;
	int savevbadness;
	scaled savevfuzz;
	halfword savesplittopskip;
	if (type(bestpagebreak) == penalty_node) //12
	{
		geqworddefine(5302, mem[bestpagebreak+1].int_);
		mem[bestpagebreak+1].int_ = 10000;
	}
	else
		geqworddefine(5302, 10000);
	if (curmark[2])
	{
		if (curmark[0])
			deletetokenref(curmark[0]);
		curmark[0] = curmark[2];
		info(curmark[0])++;
		deletetokenref(curmark[1]);
		curmark[1] = 0;
	}
	if (c == bestpagebreak)
		bestpagebreak = 0;
	if (eqtb[3933].hh.rh)
	{
		if (interaction == 3)
			printnl(262); //! 
		print(338); //
		printesc(409); //box
		print(1002); //255 is not void
		helpptr = 2;
		helpline[1] = 1003; //You shouldn't use \box255 except in \output routines.
		helpline[0] = 991; //Proceed, and I'll discard its present contents.
		boxerror(255);
	}
	insertpenalties = 0;
	savesplittopskip = eqtb[2892].hh.rh;
	if (eqtb[5316].int_ <= 0)
	{
		r = link(30000);
		while (r != 30000)
		{
			if (info(r+2))
			{
				n = subtype(r);
				ensurevbox(n);
				if (box(n) == 0)
					box(n) = newnullbox();
				p = box(n)+5;
				while (link(p))
					p = link(p);
				link(r+2) = p;
			}
			r = link(r);
		}
	}
	q = 29996;
	link(q) = 0;
	prevp = 29998;
	p = link(prevp);
	while (p != bestpagebreak)
	{
		if (type(p) == ins_node) //3
		{
			if (eqtb[5316].int_ <= 0)
			{
			r = link(30000);
			while (subtype(r) != subtype(p))
				r = link(r);
			if (info(r+2) == 0)
				wait = true;
			else
			{
				wait = false;
				s = link(r+2);
				link(s) = info(p+4);
				if (info(r+2) == p)
				{
					if (type(r) == vlist_node) //1
					if (info(r+1) == p && link(r+1))
					{
						while (link(s) != link(r+1))
							s = link(s);
						link(s) = 0;
						eqtb[2892].hh.rh = link(p+4);
						info(p+4) = prunepagetop(link(r+1));
						if (info(p+4))
						{
							tempptr = vpackage(info(p+4), 0, 1, 1073741823);
							mem[p+3].int_ = mem[tempptr+3].int_+mem[tempptr+2].int_;
							freenode(tempptr, 7);
							wait = true;
						}
					}
					info(r+2) = 0;
					n = subtype(r);
					tempptr = info(eqtb[3678+n].hh.rh+5);
					freenode(eqtb[3678+n].hh.rh, 7);
					eqtb[3678+n].hh.rh = vpackage(tempptr, 0, 1, 1073741823);
				}
				else
				{
					while (link(s))
						s = link(s);
					link(r+2) = s;
				}
			}
			link(prevp) = link(p);
			link(p) = 0;
			if (wait)
			{
				link(q) = p;
				q = p;
				insertpenalties++;
			}
			else
			{
				deleteglueref(link(p+4));
				freenode(p, 5);
			}
			p = prevp;
			}
		}
		else if (type(p) == mark_node) //4
		{
			if (curmark[1] == 0)
			{
				curmark[1] = mem[p+1].int_;
				info(curmark[1])++;
			}
			if (curmark[2])
				deletetokenref(curmark[2]);
			curmark[2] = mem[p+1].int_;
			info(curmark[2])++;
		}
		prevp = p;
		p = link(prevp);
	}
	eqtb[2892].hh.rh = savesplittopskip;
	if (p)
	{
		if (link(29999) == 0)
			if (nestptr == 0)
				curlist.tailfield = pagetail;
			else
				nest[0].tailfield = pagetail;
		link(pagetail) = link(29999);
		link(29999) = p;
		link(prevp) = 0;
	}
	savevbadness = eqtb[5290].int_;
	eqtb[5290].int_ = 10000;
	savevfuzz = eqtb[5839].int_;
	eqtb[5839].int_ = 1073741823;
	eqtb[3933].hh.rh = vpackage(mem[29998].hh.rh, bestsize, 0, pagemaxdepth);
	eqtb[5290].int_ = savevbadness;
	eqtb[5839].int_ = savevfuzz;
	if (lastglue != 65535)
		deleteglueref(lastglue);
	pagecontents = 0;
	pagetail = 29998;
	link(29998) = 0;
	lastglue = 65535;
	lastpenalty = 0;
	lastkern = 0;
	pagesofar[7] = 0;
	pagemaxdepth = 0;
	if (q != 29996)
	{
		link(29998) = link(29996);
		pagetail = q;
	}
	r = link(30000);
	while (r != 30000)
	{
		q = link(r);
		freenode(r, 4);
		r = q;
	}
	link(30000) = 30000;
	if (curmark[0] && curmark[1] == 0)
	{
		curmark[1] = curmark[0];
		info(curmark[0])++;
	}
	if (eqtb[3413].hh.rh)
		if (deadcycles >= eqtb[5303].int_)
		{
			if (interaction == 3)
				printnl(262); //! 
			print(1004); //Output loop---
			printint(deadcycles);
			print(1005); // consecutive dead cycles
			helpptr = 3;
			helpline[2] = 1006; //I've concluded that your \output is awry; it never does a
			helpline[1] = 1007; //\shipout, so I'm shipping \box255 out myself. Next time
			helpline[0] = 1008; //increase \maxdeadcycles if you want me to be more patient!
			error();
		}
		else
		{
			outputactive = true;
			deadcycles++;
			pushnest();
			curlist.modefield = -1;
			curlist.auxfield.int_ = -65536000;
			curlist.mlfield = -line;
			begintokenlist(eqtb[3413].hh.rh, 6);
			newsavelevel(8);
			normalparagraph();
			scanleftbrace();
			return;
		}
	if (link(29998) != 0)
	{
		if (link(29999) == 0)
			if (nestptr == 0)
				curlist.tailfield = pagetail;
			else
				nest[0].tailfield = pagetail;
		else
			link(pagetail) = link(29999);
		link(29999) = link(29998);
		link(29998) = 0;
		pagetail = 29998;
	}
	shipout(eqtb[3933].hh.rh);
	eqtb[3933].hh.rh = 0;
}
