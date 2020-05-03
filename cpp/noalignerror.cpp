#include "noalignerror.h"
#include "printnl.h"
#include "print.h"
#include "error.h"
#include "printesc.h"

void noalignerror(void)
{
	printnl(262); //! 
	print(1113); //Misplaced 
	printesc(527); //noalign
	helpptr = 2;
	helpline[1] = 1121; //I expect to see \noalign only after the \cr of
	helpline[0] = 1122; //an alignment. Proceed, and I'll ignore this case.
	error();
}
