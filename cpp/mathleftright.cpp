#include "mathleftright.h"
#include "scandelimiter.h"
#include "printnl.h"
#include "print.h"
#include "printesc.h"
#include "error.h"
#include "offsave.h"
#include "newnoad.h"
#include "pushmath.h"
#include "unsave.h"
#include "finmlist.h"

void mathleftright(void)
{
	smallnumber t = curchr;
	if (t == 31 && curgroup != 16)
	{
		if (curgroup == 15)
		{
			scandelimiter(29988, false);
			if (interaction == 3)
				printnl(262); //! 
			print(776); //Extra 
			printesc(876); //right
			helpptr = 1;
			helpline[0] = 1156; //I'm ignoring a \right that had no matching \left.
			error();
		}
		else
			offsave();
	}
	else
	{
		auto p = newnoad();
		type(p) = t;
		scandelimiter(p+1, false);
		if (t == 30)
		{
			pushmath(16);
			link(curlist.headfield) = p;
			curlist.tailfield = p;
		}
		else
		{
			p = finmlist(p);
			unsave();
			link(curlist.tailfield) = newnoad();
			curlist.tailfield = link(curlist.tailfield);
			type(curlist.tailfield) = 23;
			link(curlist.tailfield+1) = 3;
			info(curlist.tailfield+1) = p;
		}
	}
}
