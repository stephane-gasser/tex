#include "omiterror.h"
#include "impression.h"
#include "error.h"
#include "texte.h"

void omiterror(void)
{
	print_err("Misplaced "+esc("omit"));
	helpptr = 2;
	helpline[1] = "I expect to see \\omit only after tab marks or the \\cr of";
	helpline[0] = "an alignment. Proceed, and I'll ignore this case.";
	error();
}
