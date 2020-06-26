#include "noalignerror.h"
#include "impression.h"
#include "error.h"
#include "texte.h"

void noalignerror(void)
{
	print_err("Misplaced "+esc("noalign"));
	helpptr = 2;
	helpline[1] = "I expect to see \\noalign only after the \\cr of";
	helpline[0] = "an alignment. Proceed, and I'll ignore this case.";
	error();
}
