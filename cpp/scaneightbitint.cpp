#include "scaneightbitint.h"
#include "scanint.h"
#include "printnl.h"
#include "print.h"
#include "interror.h"


void scaneightbitint(void)
{
	scanint();
	if (curval < 0 || curval > 255)
	{
		printnl(262); //! 
		print(687); //Bad register code
		helpptr = 2;
		helpline[1] = 688; //A register number must be between 0 and 255.
		helpline[0] = 689; //I changed this one to zero.
		interror(curval);
		curval = 0;
	}
}
