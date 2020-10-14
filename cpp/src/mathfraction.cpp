#include "mathfraction.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "noeud.h"
#include "etat.h"
#include "getnext.h"

void mathfraction(halfword c, Token t) // c: above_code/over_code/atop_code (+delimiter_code)
{
	if (incompleat_noad)
	{
		if (c >= delimited_code)
		{
			Delimiter dummy;
			dummy.scan(scannerstatus, false, t);
			dummy.scan(scannerstatus, false, t);
		}
		if (c%delimited_code == above_code)
			(void)scan_normal_dimen(scannerstatus);
		error("Ambiguous; you need another { and }", "I'm ignoring this fraction specification, since I don't\nknow whether a construction like `x \\over y \\over z'\nmeans `{x \\over y} \\over z' or `x \\over {y \\over z}'.");
	}
	else
	{
		incompleat_noad = new FractionNoad(c, t);
		head->link = nullptr;
		tail = head;
	}
}
