#include "alterprevgraf.h"
#include "scanoptionalequals.h"
#include "scanint.h"
#include "printnl.h"
#include "print.h"
#include "printesc.h"
#include "interror.h"

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
		if (interaction == 3)
			printnl(262); //
		print(954); // Bad 
		printesc(532); //prevgraf
		helpptr = 1;
		helpline[0] = 1214; //I allow only nonnegative values here.
		interror(curval);
	}
	else
	{
		nest[p].pgfield = curval;
		curlist = nest[nestptr];
	}
}
