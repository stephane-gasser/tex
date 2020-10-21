#include "handlerightbrace.h"
#include "sauvegarde.h"
#include "impression.h"
#include "erreur.h"
#include "endgraf.h"
#include "boite.h"
#include "etat.h"
#include "buildpage.h"
#include "lecture.h"
#include "builddiscretionary.h"
#include "noeud.h"
#include "buildchoices.h"
#include "formule.h"
#include "getnext.h"

void handlerightbrace(char status, Token t, AlignRecordNode* &loop)
{
	switch (curgroup)
	{
		case simple_group: 
			unsave();
			break;
		case bottom_level:
			error("Too many }'s", "You've closed more groups than you opened.\nSuch booboos are generally harmless, so keep going.");
			break;
		case semi_simple_group:
			error("Extra }, or forgotten "+esc("endgroup"), "I've deleted a group-closing symbol because it seems to be\nspurious, as in `$x}$'. But perhaps the } is legitimate and\nyou forgot something else, as in `\\hbox{$x}'. In such cases\nthe way to recover is to insert both the forgotten and the\ndeleted material, e.g., by typing `I$}'.");
			alignstate++;
			break;
		case math_shift_group:
			error("Extra }, or forgotten $", "I've deleted a group-closing symbol because it seems to be\nspurious, as in `$x}$'. But perhaps the } is legitimate and\nyou forgot something else, as in `\\hbox{$x}'. In such cases\nthe way to recover is to insert both the forgotten and the\ndeleted material, e.g., by typing `I$}'.");
			alignstate++;
			break;
		case math_left_group: 
			error("Extra }, or forgotten "+esc("right"), "I've deleted a group-closing symbol because it seems to be\nspurious, as in `$x}$'. But perhaps the } is legitimate and\nyou forgot something else, as in `\\hbox{$x}'. In such cases\nthe way to recover is to insert both the forgotten and the\ndeleted material, e.g., by typing `I$}'.");
			alignstate++;
			break;
		case adjusted_hbox_group:
			adjusttail = adjust_head;
			package(status, box_code, t);
			break;
		case vbox_group:
			endgraf(); [[fallthrough]];
		case hbox_group: 
			package(status, box_code, t);
			break;
		case vtop_group:
			endgraf();
			package(status, vtop_code, t);
			break;
		case insert_group:
		{
			endgraf();
			unsave();
			auto s0 = savestack.back()->int_;
			savestack.pop_back();
			auto p = vpack(head->link, 0, additional);
			popnest();
			if (s0 < 255)
			{
				split_top_skip()->glue_ref_count++;
				tail_append(new InsNode(s0, p->height+p->depth, split_max_depth(), split_top_skip(), floating_penalty(), p->list_ptr));
			}
			else
				tail_append(new AdjustNode(p->list_ptr));
			delete p;
			if (nest.size() == 1)
				buildpage(status);
			break;
		}
		case output_group:
			if (loc || (token_type != output_text && token_type != backed_up))
			{
				error("Unbalanced output routine", "Your sneaky output routine has problematic {'s and/or }'s.\nI can't handle that very well; good luck.");
				do
					t = scanner.get(status);
				while (loc);
			}
			endtokenlist();
			endgraf();
			unsave();
			outputactive = false;
			insertpenalties = 0;
			if (box(255))
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
			buildpage(status);
			break;
		case disc_group: 
			builddiscretionary();
			scanner.leftBrace(status);
			break;
		case align_group:
			backinput(t);
			inserror(cs_token_flag+frozen_cr, "Missing "+esc("cr")+" inserted", "I'm guessing that you meant to end an alignment here.");
			break;
		case no_align_group:
			endgraf();
			unsave();
			alignpeek(status, loop);
			break;
		case vcenter_group:
		{
			endgraf();
			unsave();
			auto s1 = savestack.back()->int_; //scaled
			savestack.pop_back();
			auto s0 = savestack.back()->int_; //smallnumber
			savestack.pop_back();
			auto p = vpack(head->link, s1, s0);
			popnest();
			auto n = new Noad(vcenter_noad);
			n->nucleus.math_type = sub_box;
			n->nucleus.info = p;
			tail_append(n);
			break;
		}
		case math_choice_group:
			buildchoices();
			scanner.leftBrace(status);
			break;
		case math_group:
		{
			unsave();
			auto &n = *dynamic_cast<NoadContent*>(savestack.back()->index); //NoadContent
			savestack.pop_back();
			n.math_type = sub_mlist;
			auto p = finmlist(nullptr);
			n.info = p;
			if (p && p->link == nullptr)
				switch (p->type)
				{
					case ord_noad:
						if (auto P = dynamic_cast<Noad*>(p); P->subscr.math_type == 0 && P->supscr.math_type == 0)
						{
							n = P->nucleus;
							delete p;
						}
						break;
					case accent_noad:
						if (tail->type == ord_noad && n == dynamic_cast<Noad*>(tail)->nucleus)
						{
							LinkedNode *q;
							followUntilBeforeTarget(head, q, tail); // head -> ... -> q -> tail
							q->link = p; // head -> ... -> q -> p
							delete tail;
							tail = p; // head -> ... -> q -> p=tail
						}
				}
			break;
		}
		default: 
			confusion("rightbrace");
	}
}
