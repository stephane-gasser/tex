#include "builddiscretionary.h"
#include "unsave.h"
#include "impression.h"
#include "erreur.h"
#include "flushnodelist.h"
#include "popnest.h"
#include "flushnodelist.h"
#include "newsavelevel.h"
#include "scanleftbrace.h"
#include "pushnest.h"
#include "texte.h"

static void erreurBuilddiscretionary1(void)
{
	print_err("Improper discretionary list"); 
	helpptr = 1;
	helpline[0] = "Discretionary lists must contain only boxes and kerns.";
	error();
}

static void erreurBuilddiscretionary2(void)
{
	print_err("Illegal math "+esc("discretionary"));
	helpptr = 2;
	helpline[1] = "Sorry: The third part of a discretionary break must be";
	helpline[0] = "empty, in math formulas. I had to delete your third part.";
	error();
}

static void erreurBuilddiscretionary3(void)
{
	
	print_err("Discretionary list is too long");
	helpptr = 2;
	helpline[1] = "Wow---I never thought anybody would tweak me here.";
	helpline[0] = "You can't seriously need such a huge discretionary list?";
	error();
}

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
			erreurBuilddiscretionary1();
			begindiagnostic();
			printnl("The following discretionary sublist has been deleted:"+showbox(p));
			print(enddiagnostic(true));
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
				erreurBuilddiscretionary2();
				flushnodelist(p);
				n = 0;
			}
			else
				link(tail) = p;
			if (n <= 255)
				subtype(tail) = n;
			else
				erreurBuilddiscretionary3();
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
