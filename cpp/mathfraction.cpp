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
		if (c >= delimited_code)
		{
			scandelimiter(garbage, false);
			scandelimiter(garbage, false);
		}
		if (c%delimited_code == 0)
			scandimen(false, false, false);
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
		type(incompleat_noad) = fraction_noad;
		subtype(incompleat_noad) = normal;
		link(numerator(incompleat_noad)) = 3;
		info(numerator(incompleat_noad)) = link(head);
		mem[denominator(incompleat_noad)].hh = emptyfield;
		mem[left_delimiter(incompleat_noad)].qqqq = nulldelimiter;
		mem[right_delimiter(incompleat_noad)].qqqq = nulldelimiter;
		link(head) = 0;
		tail = head;
		if (c >= 3)
		{
			scandelimiter(left_delimiter(incompleat_noad), false);
			scandelimiter(right_delimiter(incompleat_noad), false);
		}
		switch (c%3)
		{
			case above_code:
				scandimen(false, false, false);
				thickness(incompleat_noad) = curval;
				break;
			case over_code: 
				thickness(incompleat_noad) = default_code;
				break;
			case atop_code: 
				thickness(incompleat_noad) = 0;
				break;
		}
	}
}
