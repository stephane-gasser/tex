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
			if (interaction == 3)
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
			adjusttail = 29995;
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
			p = vpackage(link(curlist.headfield), 0, 1, 1073741823);
			popnest();
			if (savestack[saveptr+0].int_ < 255)
			{
				link(curlist.tailfield) = getnode(5);
				curlist.tailfield = link(curlist.tailfield);
				type(curlist.tailfield) = ins_node; //3
				subtype(curlist.tailfield) = savestack[saveptr+0].int_;
				mem[curlist.tailfield+3].int_ = mem[p+3].int_+mem[p+2].int_;
				info(curlist.tailfield+4) = link(p+5);
				link(curlist.tailfield+4) = q;
				mem[curlist.tailfield+2].int_ = d;
				mem[curlist.tailfield+1].int_ = f;
			}
			else
			{
				link(curlist.tailfield) = getnode(2);
				curlist.tailfield = link(curlist.tailfield);
				type(curlist.tailfield) = adjust_node; //5
				type(curlist.tailfield) = 0;
				mem[curlist.tailfield+1].int_ = link(p+5);
				deleteglueref(q);
			}
			freenode(p, 7);
			if (nestptr == 0)
				buildpage();
			break;
		case 8:
			if ((curinput.locfield || curinput.indexfield != 6) && curinput.indexfield != 3)
			{
				if (interaction == 3)
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
				if (interaction == 3)
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
			if (curlist.tailfield != curlist.headfield)
			{
				link(pagetail) = link(curlist.headfield);
				pagetail = curlist.tailfield;
			}
			if (link(29998))
			{
				if (link(29999) == 0)
					nest[0].tailfield = pagetail;
				link(pagetail) = link(29999);
				link(29999) = link(29998);
				link(29998) = 0;
				pagetail = 29998;
			}
			popnest();
			buildpage();
			break;
		case 10: 
			builddiscretionary;
			break;
		case 6:
			backinput();
			curtok = 6710;
			if (interaction == 3)
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
			p = vpackage(link(curlist.headfield), savestack[saveptr+1].int_, savestack[saveptr].int_, 1073741823);
			popnest();
			link(curlist.tailfield) = newnoad();
			curlist.tailfield = link(curlist.tailfield);
			type(curlist.tailfield) = 29;
			link(curlist.tailfield+1) = 2;
			info(curlist.tailfield+1) = p;
			break;
		case 13: 
			buildchoices();
			break;
		case 9:
			unsave();
			saveptr--;
			link(savestack[saveptr].int_) = 3;
			p = finmlist(0);
			info(savestack[saveptr].int_) = p;
			if (p)
				if (link(p) == 0)
					if (type(p) == 16)
					{
						if (link(p+3) == 0 && link(p+2) == 0)
						{
							mem[savestack[saveptr].int_].hh = mem[p+1].hh;
							freenode(p, 4);
						}
					}
					else 
						if (type(p) == 28)
							if (savestack[saveptr].int_ == curlist.tailfield+1)
								if (type(curlist.tailfield) == 16)
								{
									q = curlist.headfield;
									while (link(q) != curlist.tailfield)
										q = link(q);
									link(q) = p;
									freenode(curlist.tailfield, 4);
									curlist.tailfield = p;
								}
			break;
		default: 
			confusion(1046); //rightbrace
	}
}
