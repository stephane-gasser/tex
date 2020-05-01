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
	if (curlist.auxfield.int_)
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
		curlist.auxfield.int_ = getnode(6);
		type(curlist.auxfield.int_) = 25;
		subtype(curlist.auxfield.int_) = 0;
		link(curlist.auxfield.int_+2) = 3;
		info(curlist.auxfield.int_+2) = link(curlist.headfield);
		mem[curlist.auxfield.int_+3].hh = emptyfield;
		mem[curlist.auxfield.int_+4].qqqq = nulldelimiter;
		mem[curlist.auxfield.int_+5].qqqq = nulldelimiter;
		link(curlist.headfield) = 0;
		curlist.tailfield = curlist.headfield;
		if (c >= 3)
		{
			scandelimiter(curlist.auxfield.int_+4, false);
			scandelimiter(curlist.auxfield.int_+5, false);
		}
		switch (c%3)
		{
			case 0:
				scandimen(false, false, false);
				mem[curlist.auxfield.int_+1].int_ = curval;
				break;
			case 1: 
				mem[curlist.auxfield.int_+1].int_ = 1073741824;
				break;
			case 2: 
				mem[curlist.auxfield.int_+1].int_ = 0;
				break;
		}
	}
}
