#include "omiterror.h"
#include "printnl.h"
#include "print.h"
#include "error.h"
#include "printesc.h"
#include "texte.h"

void omiterror(void)
{
	printnl("! ");
	print("Misplaced ");
	printesc("omit");
	helpptr = 2;
	helpline[1] = txt("I expect to see \\omit only after tab marks or the \\cr of");
	helpline[0] = txt("an alignment. Proceed, and I'll ignore this case.");
	error();
}
