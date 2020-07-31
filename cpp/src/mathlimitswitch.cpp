#include "mathlimitswitch.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

void mathlimitswitch(Token t)
{
	if (head != tail && tail->type == op_noad)
		subtype(tail->num) = t.chr;
	else
		error("Limit controls must follow a math operator", "I'm ignoring this misplaced \\limits or \\nolimits command.");
}
