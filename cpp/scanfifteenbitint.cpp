#include "scanfifteenbitint.h"
#include "scanint.h"
#include "printnl.h"
#include "print.h"
#include "interror.h"

void scanfifteenbitint(void)
{
	scanint();
	if (curval < 0 || curval > 32767)
	{
		if (interaction == 3)
			printnl(262); //! 
		print(694); //Bad mathchar
		helpptr = 2;
		helpline[1] = 695; //A mathchar number must be between 0 and 32767.
		helpline[0] = 689; //I changed this one to zero.
		interror(curval);
		curval = 0;
	}
}
