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

static halfword& broken_ptr(halfword p) { return link(p+1); }
static int holding_inserts(void) { return int_par(holding_inserts_code); }
static halfword& output_routine(void) { return equiv(output_routine_loc); }

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
		geqworddefine(int_base+output_penalty_code, penalty(bestpagebreak));
		penalty(bestpagebreak) = inf_penalty;
	}
	else
		geqworddefine(int_base+output_penalty_code, inf_penalty);
	if (bot_mark)
	{
		if (top_mark)
			deletetokenref(top_mark);
		top_mark = bot_mark;
		info(top_mark)++;
		deletetokenref(first_mark);
		first_mark = 0;
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
		helpline[1] = "You shouldn't use \\box255 except in \\output routines.";
		helpline[0] = "Proceed, and I'll discard its present contents.";
		boxerror(255);
	}
	insertpenalties = 0;
	savesplittopskip = split_top_skip();
	if (holding_inserts() <= 0)
	{
		r = link(page_ins_head);
		while (r != page_ins_head)
		{
			if (best_ins_ptr(r))
			{
				n = subtype(r);
				ensurevbox(n);
				if (box(n) == 0)
					box(n) = newnullbox();
				p = box(n)+list_offset;
				while (link(p))
					p = link(p);
				last_ins_ptr(r) = p;
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
			if (holding_inserts() <= 0)
			{
			r = link(page_ins_head);
			while (subtype(r) != subtype(p))
				r = link(r);
			if (best_ins_ptr(r) == 0)
				wait = true;
			else
			{
				wait = false;
				s = last_ins_ptr(r);
				link(s) = ins_ptr(p);
				if (best_ins_ptr(r) == p)
				{
					if (type(r) == split_up) //1
					if (broken_ins(r) == p && broken_ptr(r))
					{
						while (link(s) != broken_ptr(r))
							s = link(s);
						link(s) = 0;
						split_top_skip() = split_top_ptr(p);
						ins_ptr(p) = prunepagetop(broken_ptr(r));
						if (ins_ptr(p))
						{
							tempptr = vpack(ins_ptr(p), 0, additional);
							height(p) = height(tempptr)+depth(tempptr);
							freenode(tempptr, box_node_size);
							wait = true;
						}
					}
					best_ins_ptr(r) = 0;
					n = subtype(r);
					tempptr = list_ptr(box(n));
					freenode(box(n), box_node_size);
					box(n) = vpack(tempptr, 0, additional);
				}
				else
				{
					while (link(s))
						s = link(s);
					last_ins_ptr(r) = s;
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
				deleteglueref(split_top_ptr(p));
				freenode(p, ins_node_size);
			}
			p = prevp;
			}
		}
		else if (type(p) == mark_node) //4
		{
			if (first_mark == 0)
			{
				first_mark = mark_ptr(p);
				info(first_mark)++;
			}
			if (bot_mark)
				deletetokenref(bot_mark);
			bot_mark = mark_ptr(p);
			info(bot_mark)++;
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
				contrib_tail = pagetail;
		link(pagetail) = link(contrib_head);
		link(contrib_head) = p;
		link(prevp) = 0;
	}
	savevbadness = vbadness();
	vbadness() = inf_bad;
	savevfuzz = vfuzz();
	vfuzz() = max_dimen;
	box(255) = vpackage(link(page_head), bestsize, exactly, pagemaxdepth);
	vbadness() = savevbadness;
	vfuzz() = savevfuzz;
	if (lastglue != empty_flag)
		deleteglueref(lastglue);
	pagecontents = 0;
	pagetail = page_head;
	link(page_head) = 0;
	lastglue = empty_flag;
	lastpenalty = 0;
	lastkern = 0;
	page_depth = 0;
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
		freenode(r, page_ins_node_size);
		r = q;
	}
	link(page_ins_head) = page_ins_head;
	if (top_mark && first_mark == 0)
	{
		first_mark = top_mark;
		info(top_mark)++;
	}
	if (output_routine())
		if (deadcycles >= max_dead_cycles())
		{
			printnl("! ");
			print("Output loop---");
			printint(deadcycles);
			print(" consecutive dead cycles");
			helpptr = 3;
			helpline[2] = "I've concluded that your \\output is awry; it never does a";
			helpline[1] = "\\shipout, so I'm shipping \\box255 out myself. Next time";
			helpline[0] = "increase \\maxdeadcycles if you want me to be more patient!";
			error();
		}
		else
		{
			outputactive = true;
			deadcycles++;
			pushnest();
			mode = -vmode;
			prev_depth = ignore_depth;
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
				contrib_tail = pagetail;
		else
			link(pagetail) = link(contrib_head);
		link(contrib_head) = link(page_head);
		link(page_head) = 0;
		pagetail = page_head;
	}
	shipout(box(255));
	box(255) = 0;
}
