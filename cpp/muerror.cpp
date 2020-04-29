#include "muerror.h"
#include "error.h"
#include "printnl.h"
#include "print.h"

void muerror(void)
{
	if (interaction == 3)
		printnl(262); //! 
	print(662); //Incompatible glue units
	helpptr = 1;
	helpline[0] = 663; //I'm going to assume that 1mu=1pt when they're mixed.
	error();
}
