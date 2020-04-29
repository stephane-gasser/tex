#include "builddiscretionary.h"
#include "unsave.h"
#include "printnl.h"
#include "print.h"
#include "begindiagnostic.h"
#include "error.h"
#include "showbox.h"
#include "enddiagnostic.h"
#include "flushnodelist.h"
#include "popnest.h"
#include "printesc.h"
#include "flushnodelist.h"
#include "newsavelevel.h"
#include "scanleftbrace.h"
#include "pushnest.h"

void builddiscretionary(void)
{
	unsave();
	auto q = curlist.headfield;
	auto p = link(q);
	int n = 0;
	while (p)
	{
		if (p < himemmin && type(p) > 2 && type(p) != kern_node && type(p) != ligature_node)
		{
			if (interaction == 3)
				printnl(262); //! 
			print(1106); //Improper discretionary list
			helpptr = 1;
			helpline[0] = 1107; //Discretionary lists must contain only boxes and kerns.
			error();
			begindiagnostic();
			printnl(1108); //The following discretionary sublist has been deleted:
			showbox(p);
			enddiagnostic(true);
			flushnodelist(p);
			link(q) = 0;
			break;
		}
		q = p;
		p = link(q);
		n++;
	}
	p = link(curlist.headfield);
	popnest();
	switch (savestack[saveptr-1].int_)
	{
		case 0: 
			info(curlist.tailfield+1) = p;
			break;
		case 1: 
			link(curlist.tailfield+1) = p;
			break;
		case 2:
			if (n > 0 && abs(curlist.modefield) == 203)
			{
				if (interaction == 3)
					printnl(262); //! 
				print(1100); //Illegal math 
				printesc(349); //discretionary
				helpptr = 2;
				helpline[1] = 1101; //Sorry: The third part of a discretionary break must be
				helpline[0] = 1102; //empty, in math formulas. I had to delete your third part.
				flushnodelist(p);
				n = 0;
				error();
			}
			else
				link(curlist.tailfield) = p;
			if (n <= 255)
				subtype(curlist.tailfield) = n;
			else
			{
				if (interaction == 3)
					printnl(262); //! 
				print(1103); //Discretionary list is too long
				helpptr = 2;
				helpline[1] = 1104; //Wow---I never thought anybody would tweak me here.
				helpline[0] = 1105; //You can't seriously need such a huge discretionary list?
				error();
			}
			if (n > 0)
				curlist.tailfield = q;
			saveptr--;
			return;
	}
	savestack[saveptr-1].int_++;
	newsavelevel(10);
	scanleftbrace();
	pushnest();
	curlist.modefield = -102;
	curlist.auxfield.hh.lh = 1000;
}
