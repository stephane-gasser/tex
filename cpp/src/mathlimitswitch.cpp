#include "mathlimitswitch.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

static void erreurMathlimitswitch(void)
{
	print_err("Limit controls must follow a math operator");
	helpptr = 1;
	helpline[0] = "I'm ignoring this misplaced \\limits or \\nolimits command.";
	error();
}

void mathlimitswitch(void)
{
	if (head != tail && type(tail) == op_noad)
		{
			subtype(tail) = curchr;
			return;
		}
	erreurMathlimitswitch();
}
