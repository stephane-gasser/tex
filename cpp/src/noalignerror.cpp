#include "noalignerror.h"
#include "printnl.h"
#include "print.h"
#include "error.h"
#include "printesc.h"
#include "texte.h"

void noalignerror(void)
{
	printnl("! ");
	print("Misplaced ");
	printesc("noalign");
	helpptr = 2;
	helpline[1] = "I expect to see \\noalign only after the \\cr of";
	helpline[0] = "an alignment. Proceed, and I'll ignore this case.";
	error();
}
