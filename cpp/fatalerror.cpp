#include "fatalerror.h"
#include "normalizeselector.h"
#include "printnl.h"
#include "print.h"
#include "error.h"
#include "jumpout.h"

void fatalerror(strnumber s)
{
	normalizeselector();
	if (interaction == 3)
		printnl(262); //! 
	print(287); //Emergency stop
	helpptr = 1;
	helpline[0] = s;
	if (interaction == 3)
		interaction = 2;
	if (logopened)
		error();
	history = 3;
	jumpout();
}
