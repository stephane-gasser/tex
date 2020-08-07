#include "fireup.h"
#include "geqworddefine.h"
#include "impression.h"
#include "boite.h"
#include "noeud.h"
#include "prunepagetop.h"
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
		top_mark->token_ref_count++;
		deletetokenref(first_mark);
		first_mark = nullptr;
	}
	if (c == bestpagebreak)
		bestpagebreak = 0;
	if (box[255])
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
				if (box[n] == nullptr)
					box[n] = new BoxNode;
				auto p = box[n]->list_ptr;
				while (p->link)
					p = p->link;
				last_ins_ptr(r->num) = p->num;
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
			auto P = dynamic_cast<InsNode*>(p);
			if (holding_inserts() <= 0)
			{
				auto r = dynamic_cast<PageInsNode*>(page_ins_head->link);
				while (r->subtype != P->subtype)
					r = dynamic_cast<PageInsNode*>(r->link);
				if (r->best_ins_ptr == nullptr)
					wait = true;
				else
				{
					wait = false;
					s = r->last_ins_ptr->num;
					link(s) = P->ins_ptr->num;
					if (r->best_ins_ptr == p)
					{
						if (r->type == split_up) //1
						if (r->broken_ins == p && r->broken_ptr)
						{
							while (link(s) != r->broken_ptr->num)
								s = link(s);
							link(s) = 0;
							split_top_skip = P->split_top_ptr;
							P->ins_ptr = prunepagetop(r->broken_ptr);
							if (P->ins_ptr)
							{
								auto ins = P->ins_ptr;
								auto tempptr = vpack(ins, 0, additional);
								P->height = tempptr->height+tempptr->depth;
								delete tempptr;
								wait = true;
							}
						}
						r->best_ins_ptr = nullptr;
						n = r->subtype;
						auto tempptr = box[n]->list_ptr;
						delete box[n];
						box[n] = vpack(tempptr, 0, additional);
					}
					else
					{
						while (link(s))
							s = link(s);
						r->last_ins_ptr->num = s;
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
		prevp = p;
		p = prevp->link;
	}
	split_top_skip = savesplittopskip;
	if (p)
	{
		if (contrib_head->link == nullptr)
			if (nestptr == 0)
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
	box[255] = vpackage(page_head->link, bestsize, exactly, pagemaxdepth);
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
	page_ins_head->link = page_ins_head;
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
			newsavelevel(8);
			normalparagraph();
			auto t = scanleftbrace();
			return;
		}
	if (page_head->link)
	{
		if (contrib_head->link == nullptr)
			if (nestptr == 0)
				tail = pagetail;
			else
				contrib_tail = pagetail;
		else
			pagetail->link = contrib_head->link;
		contrib_head->link = page_head->link;
		page_head->link = nullptr;
		pagetail = page_head;
	}
	shipout(box[255]);
	box[255] = nullptr;
}
