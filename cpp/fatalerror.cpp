#include "fatalerror.h"
#include "normalizeselector.h"
#include "printnl.h"
#include "print.h"
#include "error.h"
#include "jumpout.h"

void fatalerror(strnumber s)
{
	normalizeselector();
	printnl(262); //! 
	print(287); //Emergency stop
	helpptr = 1;
	helpline[0] = s;
	if (interaction == error_stop_mode)
		interaction = scroll_mode;
	if (logopened)
		error();
	history = fatal_error_stop;
	jumpout();
}
