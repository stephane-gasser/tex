#include "scantwentysevenbitint.h"
#include "scanint.h"
#include "printnl.h"
#include "print.h"
#include "interror.h"

void scantwentysevenbitint(void)
{
	scanint();
	if (curval < 0 || curval > 134217727)
	{
		if (interaction == 3)
			printnl(262); //! 
		print(696); //Bad delimiter code
		helpptr = 2;
		helpline[1] = 697; //A numeric delimiter code must be between 0 and 2^{27}-1.
		helpline[0] = 689; //I changed this one to zero.
		interror(curval);
		curval = 0;
	}
}
