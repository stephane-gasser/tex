#include "handlerightbrace.h"
#include "unsave.h"
#include "printnl.h"
#include "print.h"
#include "error.h"
#include "extrarightbrace.h"
#include "package.h"
#include "endgraf.h"
#include "vpackage.h"
#include "popnest.h"
#include "getnode.h"
#include "deleteglueref.h"
#include "freenode.h"
#include "buildpage.h"
#include "gettoken.h"
#include "endtokenlist.h"
#include "printesc.h"
#include "printint.h"
#include "boxerror.h"
#include "buildpage.h"
#include "builddiscretionary.h"
#include "backinput.h"
#include "inserror.h"
#include "alignpeek.h"
#include "newnoad.h"
#include "buildchoices.h"
#include "finmlist.h"
#include "confusion.h"
#include "texte.h"

static int floating_penalty(void) { return int_par(floating_penalty_code); }

void handlerightbrace(void)
{
	halfword p, q;
	scaled d;
	int f;
	switch (curgroup)
	{
		case simple_group: 
			unsave();
			break;
		case bottom_level:
			printnl("! ");
			print("Too many }'s");
			helpptr = 2;
			helpline[1] = "You've closed more groups than you opened.";
			helpline[0] = "Such booboos are generally harmless, so keep going.";
			error();
			break;
		case semi_simple_group:
		case math_shift_group:
		case math_left_group: 
			extrarightbrace();
			break;
		case hbox_group: 
			package(0);
			break;
		case adjusted_hbox_group:
			adjusttail = adjust_head;
			package(0);
			break;
		case vbox_group:
			endgraf();
			package(0);
			break;
		case vtop_group:
			endgraf();
			package(4);
			break;
		case insert_group:
			endgraf();
			q = split_top_skip();
			link(q)++;
			d = split_max_depth();
			f = floating_penalty();
			unsave();
			saveptr--;
			p = vpack(link(head), 0, additional);
			popnest();
			if (saved(0) < 255)
			{
				tail_append(getnode(ins_node_size));
				type(tail) = ins_node; //3
				subtype(tail) = saved(0);
				height(tail) = height(p)+depth(p);
				ins_ptr(tail) = list_ptr(p);
				split_top_ptr(tail) = q;
				depth(tail) = d;
				float_cost(tail) = f;
			}
			else
			{
				tail_append(getnode(small_node_size));
				type(tail) = adjust_node; //5
				type(tail) = 0;
				adjust_ptr(tail) = list_ptr(p);
				deleteglueref(q);
			}
			freenode(p, box_node_size);
			if (nestptr == 0)
				buildpage();
			break;
		case output_group:
			if (loc || (token_type != output_text && token_type != backed_up))
			{
				printnl("! ");
				print("Unbalanced output routine");
				helpptr = 2;
				helpline[1] = "Your sneaky output routine has problematic {'s and/or }'s.";
				helpline[0] = "I can't handle that very well; good luck.";
				error();
				do
					gettoken();
				while (loc);
			}
			endtokenlist();
			endgraf();
			unsave();
			outputactive = false;
			insertpenalties = 0;
			if (box(255))
			{
				printnl("! ");
				print("Output routine didn't use all of ");
				printesc("box");
				printint(255); 
				helpptr = 3;
				helpline[2] = "Your \\output commands should empty \\box255,";
				helpline[1] = "e.g., by saying `\\shipout\\box255'.";
				helpline[0] = "Proceed; I'll discard its present contents.";
				boxerror(255);
			}
			if (tail != head)
			{
				link(pagetail) = link(head);
				pagetail = tail;
			}
			if (link(page_head))
			{
				if (link(contrib_head) == 0)
					contrib_tail = pagetail;
				link(pagetail) = link(contrib_head);
				link(contrib_head) = link(page_head);
				link(page_head) = 0;
				pagetail = page_head;
			}
			popnest();
			buildpage();
			break;
		case disc_group: 
			builddiscretionary;
			break;
		case align_group:
			backinput();
			curtok = cs_token_flag+frozen_cr;
			printnl("! ");
			print("Missing ");
			printesc("cr");
			print(" inserted");
			helpptr = 1;
			helpline[0] = "I'm guessing that you meant to end an alignment here.";
			inserror();
			break;
		case no_align_group:
			endgraf();
			unsave();
			alignpeek();
			break;
		case vcenter_group:
			endgraf();
			unsave();
			saveptr -= 2;
			p = vpack(link(head), saved(1), saved(0));
			popnest();
			tail_append(newnoad());
			type(tail) = vcenter_noad;
			math_type(nucleus(tail)) = sub_box;
			info(nucleus(tail)) = p;
			break;
		case math_choice_group: 
			buildchoices();
			break;
		case math_group:
			unsave();
			saveptr--;
			math_type(saved(0)) = sub_mlist;
			p = finmlist(0);
			info(saved(0)) = p;
			if (p && link(p) == 0)
				if (type(p) == ord_noad)
				{
					if (math_type(subscr(p)) == 0 && math_type(supscr(p)) == 0)
					{
						mem[saved(0)] = mem[nucleus(p)];
						freenode(p, noad_size);
					}
				}
				else 
					if (type(p) == accent_noad)
						if (saved(0) == nucleus(tail))
							if (type(tail) == ord_noad)
							{
								q = head;
								while (link(q) != tail)
									q = link(q);
								link(q) = p;
								freenode(tail, noad_size);
								tail = p;
							}
			break;
		default: 
			confusion("rightbrace");
	}
}
