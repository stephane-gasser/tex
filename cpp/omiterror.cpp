#include "omiterror.h"
#include "printnl.h"
#include "print.h"
#include "error.h"
#include "printesc.h"

void omiterror(void)
{
	if (interaction == 3)
		printnl(262); //! 
	print(1113); //Misplaced 
	printesc(530); //omit
	helpptr = 2;
	helpline[1] = 1123; //I expect to see \omit only after tab marks or the \cr of
	helpline[0] = 1122; //an alignment. Proceed, and I'll ignore this case.
	error();
}
