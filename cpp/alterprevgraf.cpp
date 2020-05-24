#include "alterprevgraf.h"
#include "scanoptionalequals.h"
#include "scanint.h"
#include "printnl.h"
#include "print.h"
#include "printesc.h"
#include "interror.h"
#include "texte.h"

void alterprevgraf(void)
{
	nest[nestptr] = curlist;
	auto p = nestptr;
	while (abs(nest[p].modefield) != 1)
		p--;
	scanoptionalequals();
	scanint();
	if (curval < 0)
	{
		printnl("! ");
		print(" Bad ");
		printesc("prevgraf");
		helpptr = 1;
		helpline[0] = txt("I allow only nonnegative values here.");
		interror(curval);
	}
	else
	{
		nest[p].pgfield = curval;
		curlist = nest[nestptr];
	}
}
