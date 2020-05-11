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

void handlerightbrace(void)
{
	halfword p, q;
	scaled d;
	int f;
	switch (curgroup)
	{
		case 1: 
			unsave();
			break;
		case 0:
			printnl(262); //! 
			print(1043); //Too many }'s
			helpptr = 2;
			helpline[1] = 1044; //You've closed more groups than you opened.
			helpline[0] = 1045; //Such booboos are generally harmless, so keep going.
			error();
			break;
		case 14:
		case 15:
		case 16: 
			extrarightbrace();
			break;
		case 2: 
			package(0);
			break;
		case 3:
			adjusttail = adjust_head;
			package(0);
			break;
		case 4:
			endgraf();
			package(0);
			break;
		case 5:
			endgraf();
			package(4);
			break;
		case 11:
			endgraf();
			q = split_top_skip();
			link(q)++;
			d = dimen_par(split_max_depth_code);
			f = int_par(floating_penalty_code);
			unsave();
			saveptr--;
			p = vpackage(link(head), 0, 1, max_dimen);
			popnest();
			if (saved(0) < 255)
			{
				tail_append(getnode(5));
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
				tail_append(getnode(2));
				type(tail) = adjust_node; //5
				type(tail) = 0;
				adjust_ptr(tail) = list_ptr(p);
				deleteglueref(q);
			}
			freenode(p, 7);
			if (nestptr == 0)
				buildpage();
			break;
		case 8:
			if ((curinput.locfield || curinput.indexfield != 6) && curinput.indexfield != 3)
			{
				printnl(262); //! 
				print(1009); //Unbalanced output routine
				helpptr = 2;
				helpline[1] = 1010; //Your sneaky output routine has problematic {'s and/or }'s.
				helpline[0] = 1011; //I can't handle that very well; good luck.
				error();
				do
					gettoken();
				while (curinput.locfield);
			}
			endtokenlist();
			endgraf();
			unsave();
			outputactive = false;
			insertpenalties = 0;
			if (box(255))
			{
				printnl(262); //! 
				print(1012); //Output routine didn't use all of 
				printesc(409); //box
				printint(255); 
				{
				helpptr = 3;
				helpline[2] = 1013; //Your \output commands should empty \box255,
				helpline[1] = 1014; //e.g., by saying `\shipout\box255'.
				helpline[0] = 1015; //Proceed; I'll discard its present contents.
				}
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
					nest[0].tailfield = pagetail;
				link(pagetail) = link(contrib_head);
				link(contrib_head) = link(page_head);
				link(page_head) = 0;
				pagetail = page_head;
			}
			popnest();
			buildpage();
			break;
		case 10: 
			builddiscretionary;
			break;
		case 6:
			backinput();
			curtok = cs_token_flag+frozen_cr;
			printnl(262); //! 
			print(625); //Missing 
			printesc(898); //cr
			print(626); // inserted
			helpptr = 1;
			helpline[0] = 1124; //I'm guessing that you meant to end an alignment here.
			inserror();
			break;
		case 7:
			endgraf();
			unsave();
			alignpeek();
			break;
		case 12:
			endgraf();
			unsave();
			saveptr -= 2;
			p = vpackage(link(head), saved(1), saved(0), max_dimen);
			popnest();
			tail_append(newnoad());
			type(tail) = 29;
			link(tail+1) = 2;
			info(tail+1) = p;
			break;
		case 13: 
			buildchoices();
			break;
		case 9:
			unsave();
			saveptr--;
			link(saved(0)) = 3;
			p = finmlist(0);
			info(saved(0)) = p;
			if (p && link(p) == 0)
				if (type(p) == ord_noad)
				{
					if (math_type(subscr(p)) == 0 && math_type(supscr(p)) == 0)
					{
						mem[saved(0)] = mem[nucleus(p)];
						freenode(p, 4);
					}
				}
				else 
					if (type(p) == accent_noad)
						if (saved(0) == tail+1)
							if (type(tail) == ord_noad)
							{
								q = head;
								while (link(q) != tail)
									q = link(q);
								link(q) = p;
								freenode(tail, 4);
								tail = p;
							}
			break;
		default: 
			confusion(1046); //rightbrace
	}
}
