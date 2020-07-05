#include "alteraux.h"
#include "reportillegalcase.h"
#include "scanoptionalequals.h"
#include "scandimen.h"
#include "scanint.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

static void erreurAlteraux(void)
{
	print_err("Bad space factor");
	helpptr = 1;
	helpline[0] = "I allow only values in the range 1..32767 here.";
	interror(curval);
}

void alteraux(void)
{
	if (curchr != abs(mode))
		reportillegalcase();
	else
	{
		halfword c = curchr;
		scanoptionalequals();
		if (c == vmode)
		{
			scan_normal_dimen();
			prev_depth = curval;
		}
		else
		{
			scanint();
			if (curval <= 0 || curval > 32767)
				erreurAlteraux();
			else
				space_factor = curval;
		}
	}
}
