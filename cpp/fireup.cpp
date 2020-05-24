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
#include "texte.h"

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
		geqworddefine(5302, penalty(bestpagebreak));
		penalty(bestpagebreak) = 10000;
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
	if (box(255))
	{
		printnl("! ");
		print(""); 
		printesc("box");
		print("255 is not void");
		helpptr = 2;
		helpline[1] = txt("You shouldn't use \\box255 except in \\output routines.");
		helpline[0] = txt("Proceed, and I'll discard its present contents.");
		boxerror(255);
	}
	insertpenalties = 0;
	savesplittopskip = split_top_skip();
	if (int_par(holding_inserts_code) <= 0)
	{
		r = link(page_ins_head);
		while (r != page_ins_head)
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
	q = hold_head;
	link(q) = 0;
	prevp = page_head;
	p = link(prevp);
	while (p != bestpagebreak)
	{
		if (type(p) == ins_node) //3
		{
			if (int_par(holding_inserts_code) <= 0)
			{
			r = link(page_ins_head);
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
						split_top_skip() = link(p+4);
						info(p+4) = prunepagetop(link(r+1));
						if (info(p+4))
						{
							tempptr = vpackage(info(p+4), 0, 1, max_dimen);
							height(p) = height(tempptr)+depth(tempptr);
							freenode(tempptr, 7);
							wait = true;
						}
					}
					info(r+2) = 0;
					n = subtype(r);
					tempptr = info(box(n)+5);
					freenode(box(n), 7);
					box(n) = vpackage(tempptr, 0, 1, max_dimen);
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
				curmark[1] = mark_ptr(p);
				info(curmark[1])++;
			}
			if (curmark[2])
				deletetokenref(curmark[2]);
			curmark[2] = mark_ptr(p);
			info(curmark[2])++;
		}
		prevp = p;
		p = link(prevp);
	}
	split_top_skip() = savesplittopskip;
	if (p)
	{
		if (link(contrib_head) == 0)
			if (nestptr == 0)
				tail = pagetail;
			else
				nest[0].tailfield = pagetail;
		link(pagetail) = link(contrib_head);
		link(contrib_head) = p;
		link(prevp) = 0;
	}
	savevbadness = int_par(vbadness_code);
	int_par(vbadness_code) = 10000;
	savevfuzz = dimen_par(vfuzz_code);
	dimen_par(vfuzz_code) = max_dimen;
	box(255) = vpackage(link(page_head), bestsize, 0, pagemaxdepth);
	int_par(vbadness_code) = savevbadness;
	dimen_par(vfuzz_code) = savevfuzz;
	if (lastglue != empty_flag)
		deleteglueref(lastglue);
	pagecontents = 0;
	pagetail = page_head;
	link(page_head) = 0;
	lastglue = empty_flag;
	lastpenalty = 0;
	lastkern = 0;
	pagesofar[7] = 0;
	pagemaxdepth = 0;
	if (q != hold_head)
	{
		link(page_head) = link(hold_head);
		pagetail = q;
	}
	r = link(page_ins_head);
	while (r != page_ins_head)
	{
		q = link(r);
		freenode(r, 4);
		r = q;
	}
	link(page_ins_head) = page_ins_head;
	if (curmark[0] && curmark[1] == 0)
	{
		curmark[1] = curmark[0];
		info(curmark[0])++;
	}
	if (output_routine())
		if (deadcycles >= int_par(max_dead_cycles_code))
		{
			printnl("! ");
			print("Output loop---");
			printint(deadcycles);
			print(" consecutive dead cycles");
			helpptr = 3;
			helpline[2] = txt("I've concluded that your \\output is awry; it never does a");
			helpline[1] = txt("\\shipout, so I'm shipping \\box255 out myself. Next time");
			helpline[0] = txt("increase \\maxdeadcycles if you want me to be more patient!");
			error();
		}
		else
		{
			outputactive = true;
			deadcycles++;
			pushnest();
			mode = -vmode;
			prev_depth = -0x1'00'00*1000;
			mode_line = -line;
			begintokenlist(output_routine(), 6);
			newsavelevel(8);
			normalparagraph();
			scanleftbrace();
			return;
		}
	if (link(page_head))
	{
		if (link(contrib_head) == 0)
			if (nestptr == 0)
				tail = pagetail;
			else
				nest[0].tailfield = pagetail;
		else
			link(pagetail) = link(contrib_head);
		link(contrib_head) = link(page_head);
		link(page_head) = 0;
		pagetail = page_head;
	}
	shipout(box(255));
	box(255) = 0;
}
