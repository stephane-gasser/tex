#include "mathlimitswitch.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

void mathlimitswitch(halfword chr)
{
	if (head != tail && type(tail) == op_noad)
		subtype(tail) = chr;
	else
		error("Limit controls must follow a math operator", "I'm ignoring this misplaced \\limits or \\nolimits command.", curalign);
}
