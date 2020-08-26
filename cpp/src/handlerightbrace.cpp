#include "handlerightbrace.h"
#include "unsave.h"
#include "impression.h"
#include "erreur.h"
#include "extrarightbrace.h"
#include "package.h"
#include "endgraf.h"
#include "boite.h"
#include "popnest.h"
#include "deleteglueref.h"
#include "buildpage.h"
#include "lecture.h"
#include "buildpage.h"
#include "builddiscretionary.h"
#include "backinput.h"
#include "alignpeek.h"
#include "noeud.h"
#include "buildchoices.h"
#include "finmlist.h"
#include "texte.h"

static int floating_penalty(void) { return int_par(floating_penalty_code); }

void handlerightbrace(Token t, halfword &loop)
{
	BoxNode *p;
	GlueSpec *q;
	scaled d;
	int f;
	switch (curgroup)
	{
		case simple_group: 
			unsave();
			break;
		case bottom_level:
			error("Too many }'s", "You've closed more groups than you opened.\nSuch booboos are generally harmless, so keep going.");
			break;
		case semi_simple_group:
		case math_shift_group:
		case math_left_group: 
			extrarightbrace();
			break;
		case hbox_group: 
			package(0, t);
			break;
		case adjusted_hbox_group:
			adjusttail = adjust_head;
			package(0, t);
			break;
		case vbox_group:
			endgraf();
			package(0, t);
			break;
		case vtop_group:
			endgraf();
			package(vtop_code, t);
			break;
		case insert_group:
			endgraf();
			q = split_top_skip;
			q->glue_ref_count++;
			d = split_max_depth();
			f = floating_penalty();
			unsave();
			saveptr--;
			p = vpack(head->link, 0, additional);
			popnest();
			if (saved(0) < 255)
			{
				auto ins = new InsNode;
				ins->subtype = saved(0);
				ins->height = p->height+p->depth;
				ins->ins_ptr = p->list_ptr;
				ins->split_top_ptr = q;
				ins->depth = d;
				ins->float_cost = f;
				tail_append(ins);
			}
			else
			{
				auto a = new AdjustNode;
				a->adjust_ptr = dynamic_cast<TokenNode*>(p->list_ptr);
				tail_append(a);
				deleteglueref(q);
			}
			delete p;
			if (nestptr == 0)
				buildpage();
			break;
		case output_group:
			if (loc || (token_type != output_text && token_type != backed_up))
			{
				error("Unbalanced output routine", "Your sneaky output routine has problematic {'s and/or }'s.\nI can't handle that very well; good luck.");
				do
					t = gettoken();
				while (loc);
			}
			endtokenlist();
			endgraf();
			unsave();
			outputactive = false;
			insertpenalties = 0;
			if (box[255])
				boxerror(255, "Output routine didn't use all of "+esc("box255"), "Your \\output commands should empty \\box255,\ne.g., by saying `\\shipout\\box255'.\nProceed; I'll discard its present contents.");
			if (tail != head)
			{
				pagetail->link = head->link;
				pagetail = tail;
			}
			if (page_head->link)
			{
				if (contrib_head->link == nullptr)
					contrib_tail = pagetail;
				pagetail->link = contrib_head->link;
				contrib_head->link = page_head->link;
				page_head->link = nullptr;
				pagetail = page_head;
			}
			popnest();
			buildpage();
			break;
		case disc_group: 
			builddiscretionary;
			break;
		case align_group:
			backinput(t);
			t.tok = cs_token_flag+frozen_cr;
			inserror(t, "Missing "+esc("cr")+" inserted", "I'm guessing that you meant to end an alignment here.");
			break;
		case no_align_group:
			endgraf();
			unsave();
			alignpeek(loop);
			break;
		case vcenter_group:
		{
			endgraf();
			unsave();
			saveptr -= 2;
			p = vpack(head->link, saved(1), saved(0));
			popnest();
			auto n = new Noad;
			n->type = vcenter_noad;
			n->nucleus.math_type = sub_box;
			n->nucleus.info = p;
			tail_append(n);
			break;
		}
		case math_choice_group:
			buildchoices(t);
			break;
		case math_group:
			unsave();
			saveptr--;
			math_type(saved(0)) = sub_mlist;
			p->num = finmlist(0);
			info(saved(0)) = p->num;
			if (p && p->link == nullptr)
				if (p->type == ord_noad)
				{
					auto P = dynamic_cast<Noad*>(p);
					if (P->subscr.math_type == 0 && P->supscr.math_type == 0)
					{
						mem[saved(0)] = mem[nucleus(p->num)];
						delete p;
					}
				}
				else 
					if (p->type == accent_noad)
						if (saved(0) == nucleus(tail->num))
							if (tail->type == ord_noad)
							{
								auto q = head;
								while (q->link != tail)
									q = q->link;
								q->link = p;
								delete tail;
								tail = p;
							}
			break;
		default: 
			confusion("rightbrace");
	}
}
