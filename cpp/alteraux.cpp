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
	if (curchr != abs(curlist.modefield))
		reportillegalcase();
	else
	{
		halfword c = curchr;
		scanoptionalequals();
		if (c == 1)
		{
			scandimen(false, false, false);
			curlist.auxfield.int_ = curval;
		}
		else
		{
			scanint();
			if (curval <= 0 || curval > 32767)
			{
				if (interaction == 3)
					printnl(262); //! 
				print(1212); //Bad space factor
				helpptr = 1;
				helpline[0] = 1213; //I allow only values in the range 1..32767 here.
				interror(curval);
			}
			else
			curlist.auxfield.hh.lh = curval;
		}
	}
}
