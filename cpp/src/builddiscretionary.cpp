#include "builddiscretionary.h"
#include "unsave.h"
#include "impression.h"
#include "error.h"
#include "flushnodelist.h"
#include "popnest.h"
#include "flushnodelist.h"
#include "newsavelevel.h"
#include "scanleftbrace.h"
#include "pushnest.h"
#include "texte.h"

void builddiscretionary(void)
{
	unsave();
	// Prune the current list, if necessary, until it contains only |char_node|, |kern_node|, |hlist_node|, |vlist_node|, |rule_node|,
	//  and |ligature_node| items; set |n| to the length of the list, and set |q| to the list's tail
	auto q = head;
	auto p = link(q);
	int n = 0;
	while (p)
	{
		if (!is_char_node(p) && type(p) > rule_node && type(p) != kern_node && type(p) != ligature_node)
		{
			print_err("Improper discretionary list"); 
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
			pre_break(tail) = p;
			break;
		case 1: 
			post_break(tail) = p;
			break;
		case 2: //Attach list |p| to the current list, and record its length; then finish up and |return|
			if (n > 0 && abs(mode) == mmode)
			{
				print_err("Illegal math "+esc("discretionary"));
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
				print_err("Discretionary list is too long");
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
