#include "mathfraction.h"
#include "scandelimiter.h"
#include "scandimen.h"
#include "printnl.h"
#include "print.h"
#include "error.h"
#include "getnode.h"

void mathfraction(void)
{
	smallnumber c = curchr;
	if (incompleat_noad)
	{
		if (c >= 3)
		{
			scandelimiter(garbage, false);
			scandelimiter(garbage, false);
		}
		if (c%3 == 0)
			scandimen(false, false, false);
		if (interaction == 3)
			printnl(262); //! 
		print(1152); //Ambiguous; you need another { and }
		helpptr = 3;
		helpline[2] = 1153; //I'm ignoring this fraction specification, since I don't
		helpline[1] = 1154; //know whether a construction like `x \over y \over z'
		helpline[0] = 1155; //means `{x \over y} \over z' or `x \over {y \over z}'.
		error();
	}
	else
	{
		incompleat_noad = getnode(6);
		type(incompleat_noad) = 25;
		subtype(incompleat_noad) = 0;
		link(incompleat_noad+2) = 3;
		info(incompleat_noad+2) = link(head);
		mem[incompleat_noad+3].hh = emptyfield;
		mem[incompleat_noad+4].qqqq = nulldelimiter;
		mem[incompleat_noad+5].qqqq = nulldelimiter;
		link(head) = 0;
		tail = head;
		if (c >= 3)
		{
			scandelimiter(incompleat_noad+4, false);
			scandelimiter(incompleat_noad+5, false);
		}
		switch (c%3)
		{
			case 0:
				scandimen(false, false, false);
				mem[incompleat_noad+1].int_ = curval;
				break;
			case 1: 
				mem[incompleat_noad+1].int_ = 0x40'00'00'00;
				break;
			case 2: 
				mem[incompleat_noad+1].int_ = 0;
				break;
		}
	}
}
