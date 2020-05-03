#include "mathlimitswitch.h"
#include "print.h"
#include "printnl.h"
#include "error.h"

void mathlimitswitch(void)
{
	if (head != tail && type(tail) == 17)
		{
			subtype(tail) = curchr;
			return;
		}
	printnl(262); //! 
	print(1129); //Limit controls must follow a math operator
	helpptr = 1;
	helpline[0] = 1130; //I'm ignoring this misplaced \limits or \nolimits command.
	error();
}
