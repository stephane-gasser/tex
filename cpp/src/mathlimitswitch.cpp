#include "mathlimitswitch.h"
#include "impression.h"
#include "error.h"
#include "texte.h"

void mathlimitswitch(void)
{
	if (head != tail && type(tail) == op_noad)
		{
			subtype(tail) = curchr;
			return;
		}
	print_err("Limit controls must follow a math operator");
	helpptr = 1;
	helpline[0] = "I'm ignoring this misplaced \\limits or \\nolimits command.";
	error();
}
