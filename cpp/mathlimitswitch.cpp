#include "mathlimitswitch.h"
#include "print.h"
#include "printnl.h"
#include "error.h"

void mathlimitswitch(void)
{
	if (curlist.headfield != curlist.tailfield && type(curlist.tailfield) == 17)
		{
			subtype(curlist.tailfield) = curchr;
			return;
		}
	if (interaction == 3)
		printnl(262); //! 
	print(1129); //Limit controls must follow a math operator
	helpptr = 1;
	helpline[0] = 1130; //I'm ignoring this misplaced \limits or \nolimits command.
	error();
}
