#include "cserror.h"
#include "printnl.h"
#include "print.h"
#include "printesc.h"
#include "error.h"

void cserror(void)
{
	if (interaction == 3)
		printnl(262);//! 
	print(776); //Extra 
	printesc(505); //endcsname
	helpptr = 1;
	helpline[0] = 1125; //I'm ignoring this, since I wasn't doing a \csname.
	error();
}
