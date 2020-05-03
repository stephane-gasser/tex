#include "alteraux.h"
#include "reportillegalcase.h"
#include "scanoptionalequals.h"
#include "scandimen.h"
#include "scanint.h"
#include "printnl.h"
#include "print.h"
#include "interror.h"

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
				printnl(262); //! 
				print(1212); //Bad space factor
				helpptr = 1;
				helpline[0] = 1213; //I allow only values in the range 1..0x7F'FF here.
				interror(curval);
			}
			else
			space_factor = curval;
		}
	}
}
