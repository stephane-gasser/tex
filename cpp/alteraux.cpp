#include "alteraux.h"
#include "reportillegalcase.h"
#include "scanoptionalequals.h"
#include "scandimen.h"
#include "scanint.h"
#include "printnl.h"
#include "print.h"
#include "interror.h"
#include "texte.h"

void alteraux(void)
{
	if (curchr != abs(mode))
		reportillegalcase();
	else
	{
		halfword c = curchr;
		scanoptionalequals();
		if (c == 1)
		{
			scandimen(false, false, false);
			prev_depth = curval;
		}
		else
		{
			scanint();
			if (curval <= 0 || curval > 0x7F'FF)
			{
				printnl("! ");
				print("Bad space factor");
				helpptr = 1;
				helpline[0] = txt("I allow only values in the range 1..0x7F'FF here.");
				interror(curval);
			}
			else
			space_factor = curval;
		}
	}
}
