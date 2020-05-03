#include "scanfourbitint.h"
#include "scanint.h"
#include "printnl.h"
#include "print.h"
#include "interror.h"

void scanfourbitint(void)
{
	scanint();
	if (curval < 0 || curval > 15)
	{
		printnl(262); //!=
		print(692); //Bad number
		helpptr = 2;
		helpline[1] = 693; //Since I expected to read a number between 0 and 15,
		helpline[0] = 689; //I changed this one to zero.
		interror(curval);
		curval = 0;
	}
}
