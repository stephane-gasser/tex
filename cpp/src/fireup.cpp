#include "fireup.h"
#include "geqworddefine.h"
#include "impression.h"
#include "ensurevbox.h"
#include "noeud.h"
#include "prunepagetop.h"
#include "vpackage.h"
#include "deleteglueref.h"
#include "erreur.h"
#include "pushnest.h"
#include "normalparagraph.h"
#include "lecture.h"
#include "shipout.h"
#include "texte.h"

static halfword& broken_ptr(halfword p) { return link(p+1); }
static int holding_inserts(void) { return int_par(holding_inserts_code); }
static halfword& output_routine(void) { return equiv(output_routine_loc); }

void fireup(halfword c)
{
	halfword s;
	unsigned char n;
	bool wait;
	int savevbadness;
	scaled savevfuzz;
	if (type(bestpagebreak) == penalty_node) //12
	{
		PenaltyNode *Bestpagebreak;
		Bestpagebreak->num = bestpagebreak;
		geqworddefine(int_base+output_penalty_code, Bestpagebreak->penalty);
		Bestpagebreak->penalty = inf_penalty;
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
		boxerror(255, esc("box")+"255 is not void", "You shouldn't use \\box255 except in \\output routines.\nProceed, and I'll discard its present contents.");
	insertpenalties = 0;
	auto savesplittopskip = split_top_skip;
	if (holding_inserts() <= 0)
	{
		auto r = page_ins_head->link;
		while (r != page_ins_head)
		{
			if (best_ins_ptr(r->num))
			{
				n = subtype(r->num);
				ensurevbox(n);
				if (box(n) == 0)
				{
					auto B = new BoxNode;
					box(n) = B->num;
				}
				auto p = box(n)+list_offset;
				while (link(p))
					p = link(p);
				last_ins_ptr(r->num) = p;
			}
			r = r->link;
		}
	}
	auto q = hold_head;
	q->link = nullptr;
	auto prevp = page_head;
	auto p = prevp->link;
	while (p->num != bestpagebreak)
	{
		if (p->type == ins_node) //3
		{
			if (holding_inserts() <= 0)
			{
				auto r = page_ins_head->link;
				while (subtype(r->num) != subtype(p->num))
					r = r->link;
				if (best_ins_ptr(r->num) == 0)
					wait = true;
				else
				{
					wait = false;
					s = last_ins_ptr(r->num);
					link(s) = ins_ptr(p->num);
					if (best_ins_ptr(r->num) == p->num)
					{
						if (r->type == split_up) //1
						if (broken_ins(r->num) == p->num && broken_ptr(r->num))
						{
							while (link(s) != broken_ptr(r->num))
								s = link(s);
							link(s) = 0;
							split_top_skip->num = split_top_ptr(p->num);
							ins_ptr(p->num) = prunepagetop(broken_ptr(r->num))->num;
							if (ins_ptr(p->num))
							{
								tempptr = vpack(ins_ptr(p->num), 0, additional);
								height(p->num) = height(tempptr)+depth(tempptr);
								freenode(tempptr, box_node_size);
								wait = true;
							}
						}
						best_ins_ptr(r->num) = 0;
						n = subtype(r->num);
						tempptr = list_ptr(box(n));
						freenode(box(n), box_node_size);
						box(n) = vpack(tempptr, 0, additional);
					}
					else
					{
						while (link(s))
							s = link(s);
						last_ins_ptr(r->num) = s;
					}
				}
				prevp->link = p->link;
				p->link = nullptr;
				if (wait)
				{
					q->link = p;
					q = p;
					insertpenalties++;
				}
				else
				{
					deleteglueref(split_top_ptr(p->num));
					freenode(p->num, ins_node_size);
				}
				p = prevp;
			}
		}
		else if (p->type == mark_node) //4
		{
			if (first_mark == 0)
			{
				first_mark = mark_ptr(p->num);
				info(first_mark)++;
			}
			if (bot_mark)
				deletetokenref(bot_mark);
			bot_mark = mark_ptr(p->num);
			info(bot_mark)++;
		}
		prevp = p;
		p = prevp->link;
	}
	split_top_skip = savesplittopskip;
	if (p)
	{
		if (contrib_head->link == nullptr)
			if (nestptr == 0)
				tail->num = pagetail;
			else
				contrib_tail = pagetail;
		link(pagetail) = contrib_head->link->num;
		contrib_head->link = p;
		prevp->link = nullptr;
	}
	savevbadness = vbadness();
	vbadness() = inf_bad;
	savevfuzz = vfuzz();
	vfuzz() = max_dimen;
	box(255) = vpackage(page_head->link->num, bestsize, exactly, pagemaxdepth);
	vbadness() = savevbadness;
	vfuzz() = savevfuzz;
	if (lastglue)
		delete lastglue;
	pagecontents = 0;
	pagetail = page_head->num;
	page_head->link = nullptr;
	lastglue = nullptr;
	lastpenalty = 0;
	lastkern = 0;
	page_depth = 0;
	pagemaxdepth = 0;
	if (q != hold_head)
	{
		page_head->link = hold_head->link;
		pagetail = q->num;
	}
	auto r = page_ins_head->link;
	while (r != page_ins_head)
	{
		q = r->link;
		freenode(r->num, page_ins_node_size);
		r = q;
	}
	page_ins_head->link = page_ins_head;
	if (top_mark && first_mark == 0)
	{
		first_mark = top_mark;
		info(top_mark)++;
	}
	if (output_routine())
		if (deadcycles >= max_dead_cycles())
			error("Output loop---"+std::to_string(deadcycles)+" consecutive dead cycles", "I've concluded that your \\output is awry; it never does a\n\\shipout, so I'm shipping \\box255 out myself. Next time\nincrease \\maxdeadcycles if you want me to be more patient!");
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
			auto t = scanleftbrace();
			return;
		}
	if (page_head->link)
	{
		if (contrib_head->link == nullptr)
			if (nestptr == 0)
				tail->num = pagetail;
			else
				contrib_tail = pagetail;
		else
			link(pagetail) = contrib_head->link->num;
		contrib_head->link = page_head->link;
		page_head->link = nullptr;
		pagetail = page_head->num;
	}
	shipout(box(255));
	box(255) = 0;
}
