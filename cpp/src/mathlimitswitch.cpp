#include "mathlimitswitch.h"
#include "impression.h"
#include "erreur.h"
#include "etat.h"

void mathlimitswitch(Token t)
{
	if (head != tail && tail->type == op_noad)
		dynamic_cast<Noad*>(tail)->subtype = t.chr;
	else
		error("Limit controls must follow a math operator", "I'm ignoring this misplaced \\limits or \\nolimits command.");
}
