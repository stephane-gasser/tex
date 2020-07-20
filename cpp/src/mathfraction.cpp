#include "mathfraction.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "noeud.h"
#include "texte.h"

void mathfraction(halfword c, Token t)
{
	if (incompleat_noad)
	{
		if (c >= delimited_code)
		{
			scandelimiter(garbage, false, t);
			scandelimiter(garbage, false, t);
		}
		if (c%delimited_code == 0)
			int _ = scan_normal_dimen();
		error("Ambiguous; you need another { and }", "I'm ignoring this fraction specification, since I don't\nknow whether a construction like `x \\over y \\over z'\nmeans `{x \\over y} \\over z' or `x \\over {y \\over z}'.");
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
			scandelimiter(left_delimiter(incompleat_noad), false, t);
			scandelimiter(right_delimiter(incompleat_noad), false, t);
		}
		switch (c%delimited_code)
		{
			case above_code:
				thickness(incompleat_noad) = scan_normal_dimen();
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
