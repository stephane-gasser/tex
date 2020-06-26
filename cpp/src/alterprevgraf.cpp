#include "alterprevgraf.h"
#include "scanoptionalequals.h"
#include "scanint.h"
#include "impression.h"
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
		print_err(" Bad "+esc("prevgraf"));
		helpptr = 1;
		helpline[0] = "I allow only nonnegative values here.";
		interror(curval);
	}
	else
	{
		nest[p].pgfield = curval;
		curlist = nest[nestptr];
	}
}
