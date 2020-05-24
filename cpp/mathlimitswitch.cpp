#include "mathlimitswitch.h"
#include "print.h"
#include "printnl.h"
#include "error.h"
#include "texte.h"

void mathlimitswitch(void)
{
	if (head != tail && type(tail) == 17)
		{
			subtype(tail) = curchr;
			return;
		}
	printnl("! ");
	print("Limit controls must follow a math operator");
	helpptr = 1;
	helpline[0] = "I'm ignoring this misplaced \\limits or \\nolimits command.";
	error();
}
