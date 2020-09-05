#include "mathfraction.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "noeud.h"

void mathfraction(halfword c, Token t)
{
	if (incompleat_noad)
	{
		if (c >= delimited_code)
		{
			Delimiter dummy;
			scandelimiter(dummy, false, t);
			scandelimiter(dummy, false, t);
		}
		if (c%delimited_code == 0)
			int _ = scan_normal_dimen();
		error("Ambiguous; you need another { and }", "I'm ignoring this fraction specification, since I don't\nknow whether a construction like `x \\over y \\over z'\nmeans `{x \\over y} \\over z' or `x \\over {y \\over z}'.");
	}
	else
	{
		incompleat_noad = new FractionNoad;
		incompleat_noad->numerator.math_type = sub_mlist;
		incompleat_noad->numerator.info = head->link;
		incompleat_noad->denominator.math_type = 0; // = twohalves{0, 0};
		incompleat_noad->left_delimiter = Delimiter{0, 0, 0, 0};
		incompleat_noad->right_delimiter = Delimiter{0, 0, 0, 0};
		head->link = nullptr;
		tail = head;
		if (c >= delimited_code)
		{
			scandelimiter(incompleat_noad->left_delimiter, false, t);
			scandelimiter(incompleat_noad->right_delimiter, false, t);
		}
		switch (c%delimited_code)
		{
			case above_code:
				incompleat_noad->thickness = scan_normal_dimen();
				break;
			case over_code: 
				incompleat_noad->thickness = default_code;
				break;
			case atop_code: 
				incompleat_noad->thickness = 0;
				break;
		}
	}
}
