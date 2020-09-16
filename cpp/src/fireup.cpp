#include "fireup.h"
#include "equivalent.h"
#include "impression.h"
#include "boite.h"
#include "sauvegarde.h"
#include "prunepagetop.h"
#include "deleteglueref.h"
#include "erreur.h"
#include "pushnest.h"
#include "normalparagraph.h"
#include "lecture.h"
#include "shipout.h"
#include "buildpage.h"
#include "fichier.h"

void fireup(LinkedNode *c)
{
	unsigned char n;
	bool wait;
	int savevbadness;
	scaled savevfuzz;
	if (bestpagebreak->type == penalty_node) //12
	{
		auto Bestpagebreak = dynamic_cast<PenaltyNode*>(bestpagebreak);
		geqworddefine(&eqtb_int[output_penalty_code], Bestpagebreak->penalty);
		Bestpagebreak->penalty = inf_penalty;
	}
	else
		geqworddefine(&eqtb_int[output_penalty_code], inf_penalty);
	if (bot_mark)
	{
		if (top_mark)
			deletetokenref(top_mark);
		top_mark = bot_mark;
		top_mark->token_ref_count++;
		deletetokenref(first_mark);
		first_mark = nullptr;
	}
	if (c == bestpagebreak)
		bestpagebreak = nullptr;
	if (box(255))
		boxerror(255, esc("box")+"255 is not void", "You shouldn't use \\box255 except in \\output routines.\nProceed, and I'll discard its present contents.");
	insertpenalties = 0;
	auto savesplittopskip = split_top_skip();
	if (holding_inserts() <= 0)
	{
		auto r = dynamic_cast<PageInsNode*>(page_ins_head->link);
		while (r != page_ins_head)
		{
			if (r->best_ins_ptr)
			{
				n = r->subtype;
				ensurevbox(n);
				if (box(n) == nullptr)
					setBox(n,  new BoxNode);
				auto p = box(n)->list_ptr;
				while (p->link)
					next(p);
				r->last_ins_ptr = p;
			}
			next(r);
		}
	}
	hold_head->link = nullptr;
	auto q = hold_head;
	auto prevp = page_head;
	auto p = page_head->link;
	for (; p != bestpagebreak; prevp = p, next(p))
	{
		if (p->type == ins_node) //3
		{
			auto P = dynamic_cast<InsNode*>(p);
			if (holding_inserts() <= 0)
			{
				auto r = dynamic_cast<PageInsNode*>(page_ins_head->link);
				while (r->subtype != P->subtype)
					next(r);
				if (r->best_ins_ptr == nullptr)
					wait = true;
				else
				{
					wait = false;
					r->last_ins_ptr->link = P->ins_ptr;
					if (r->best_ins_ptr == p)
					{
						if (r->type == split_up && r->broken_ins == p && r->broken_ptr)
						{
							LinkedNode *s;
							followUntilBeforeTarget(r->last_ins_ptr, s, r->broken_ptr);
							s->link = nullptr;
							setSplitTopSkip(P->split_top_ptr);
							P->ins_ptr = prunepagetop(r->broken_ptr);
							if (P->ins_ptr)
							{
								auto ins = P->ins_ptr;
								auto pck = vpack(ins, 0, additional);
								P->height = pck->height+pck->depth;
								delete pck;
								wait = true;
							}
						}
						r->best_ins_ptr = nullptr;
						n = r->subtype;
						auto liste = box(n)->list_ptr;
						delete box(n);
						setBox(n, vpack(liste, 0, additional));
					}
					else
					{
						LinkedNode *s;
						followUntilEnd(r->last_ins_ptr, s);
						r->last_ins_ptr = s;
					}
				}
				prevp->link = p->link;
				p->link = nullptr;
				if (wait)
				{
					appendAtEnd(q, p);
					insertpenalties++;
				}
				else
				{
					deleteglueref(P->split_top_ptr);
					delete p;
				}
				p = prevp;
			}
		}
		else if (p->type == mark_node) //4
		{
			auto m = dynamic_cast<MarkNode*>(p)->mark_ptr;
			if (first_mark == nullptr)
			{
				first_mark = m;
				first_mark->token_ref_count++;
			}
			if (bot_mark)
				deletetokenref(bot_mark);
			bot_mark = m;
			bot_mark->token_ref_count++;
		}
	}
	setSplitTopSkip(savesplittopskip);
	if (p)
	{
		if (contrib_head->link == nullptr)
			if (nest.size() == 1)
				tail = pagetail;
			else
				contrib_tail = pagetail;
		pagetail->link = contrib_head->link;
		contrib_head->link = p;
		prevp->link = nullptr;
	}
	savevbadness = vbadness();
	vbadness() = inf_bad;
	savevfuzz = vfuzz();
	vfuzz() = max_dimen;
	setBox(255, vpackage(page_head->link, bestsize, exactly, pagemaxdepth));
	vbadness() = savevbadness;
	vfuzz() = savevfuzz;
	if (lastglue)
		delete lastglue;
	pagecontents = 0;
	pagetail = page_head;
	page_head->link = nullptr;
	lastglue = nullptr;
	lastpenalty = 0;
	lastkern = 0;
	page_depth = 0;
	pagemaxdepth = 0;
	if (q != hold_head)
	{
		page_head->link = hold_head->link;
		pagetail = q;
	}
	auto r = page_ins_head->link;
	while (r != page_ins_head)
	{
		q = r->link;
		delete r;
		r = q;
	}
	next(page_ins_head);
	if (top_mark && first_mark == nullptr)
	{
		first_mark = top_mark;
		top_mark->token_ref_count++;
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
			newsavelevel(output_group);
			normalparagraph();
			auto t = scanleftbrace();
			return;
		}
	if (page_head->link)
	{
		if (contrib_head->link == nullptr)
			if (nest.size() == 1)
				tail = pagetail;
			else
				contrib_tail = pagetail;
		else
			pagetail->link = contrib_head->link;
		contrib_head->link = page_head->link;
		page_head->link = nullptr;
		pagetail = page_head;
	}
	shipout(box(255));
	setBox(255, nullptr);
}
