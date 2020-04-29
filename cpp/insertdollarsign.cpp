#include "insertdollarsign.h"
#include "backinput.h"
#include "printnl.h"
#include "print.h"
#include "inserror.h"

void insertdollarsign(void)
{
	backinput();
	curtok = 804;
	if (interaction == 3)
		printnl(262); //! 
	print(1016); //Missing $ inserted
	helpptr = 2;
	helpline[1] = 1017; //I've inserted a begin-math/end-math symbol since I think
	helpline[0] = 1018; //you left one out. Proceed, with fingers crossed.
	inserror();
}

