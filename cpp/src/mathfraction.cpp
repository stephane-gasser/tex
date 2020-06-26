#include "mathfraction.h"
#include "scandelimiter.h"
#include "scandimen.h"
#include "impression.h"
#include "error.h"
#include "getnode.h"
#include "texte.h"

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
			scan_normal_dimen();
		print_err("Ambiguous; you need another { and }");
		helpptr = 3;
		helpline[2] = "I'm ignoring this fraction specification, since I don't";
		helpline[1] = "know whether a construction like `x \\over y \\over z'";
		helpline[0] = "means `{x \\over y} \\over z' or `x \\over {y \\over z}'.";
		error();
	}
	else
	{
		incompleat_noad = getnode(fraction_noad_size);
		type(incompleat_noad) = fraction_noad;
		subtype(incompleat_noad) = normal;
		link(numerator(incompleat_noad)) = 3;
		info(numerator(incompleat_noad)) = link(head);
		mem[denominator(incompleat_noad)].hh = emptyfield;
		mem[left_delimiter(incompleat_noad)].qqqq = nulldelimiter;
		mem[right_delimiter(incompleat_noad)].qqqq = nulldelimiter;
		link(head) = 0;
		tail = head;
		if (c >= delimited_code)
		{
			scandelimiter(left_delimiter(incompleat_noad), false);
			scandelimiter(right_delimiter(incompleat_noad), false);
		}
		switch (c%delimited_code)
		{
			case above_code:
				scan_normal_dimen();
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
