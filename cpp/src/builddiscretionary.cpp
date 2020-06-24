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
#include "texte.h"

void builddiscretionary(void)
{
	unsave();
	auto q = head;
	auto p = link(q);
	int n = 0;
	while (p)
	{
		if (p < himemmin && type(p) > 2 && type(p) != kern_node && type(p) != ligature_node)
		{
			printnl("! "); 
			print("Improper discretionary list"); 
			helpptr = 1;
			helpline[0] = "Discretionary lists must contain only boxes and kerns.";
			error();
			begindiagnostic();
			printnl("The following discretionary sublist has been deleted:");
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
	p = link(head);
	popnest();
	switch (savestack[saveptr-1].int_)
	{
		case 0: 
			info(tail+1) = p;
			break;
		case 1: 
			link(tail+1) = p;
			break;
		case 2:
			if (n > 0 && abs(mode) == mmode)
			{
				printnl("! "); 
				print("Illegal math ");
				printesc("discretionary");
				helpptr = 2;
				helpline[1] = "Sorry: The third part of a discretionary break must be";
				helpline[0] = "empty, in math formulas. I had to delete your third part.";
				flushnodelist(p);
				n = 0;
				error();
			}
			else
				link(tail) = p;
			if (n <= 255)
				subtype(tail) = n;
			else
			{
				printnl("! ");
				print("Discretionary list is too long");
				helpptr = 2;
				helpline[1] = "Wow---I never thought anybody would tweak me here.";
				helpline[0] = "You can't seriously need such a huge discretionary list?";
				error();
			}
			if (n > 0)
				tail = q;
			saveptr--;
			return;
	}
	savestack[saveptr-1].int_++;
	newsavelevel(10);
	scanleftbrace();
	pushnest();
	mode = -hmode;
	space_factor = 1000;
}
