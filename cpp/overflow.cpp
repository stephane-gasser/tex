#include "overflow.h"
#include "normalizeselector.h"
#include "printchar.h"
#include "printnl.h"
#include "print.h"
#include "print.h"
#include "printint.h"
#include "error.h"
#include "jumpout.h"

void overflow(strnumber s, int n)
{
	normalizeselector();
	printnl(262); //! 
	print(288); //TeX capacity exceeded, sorry [
	print(s);
	printchar('=');
	printint(n);
	printchar(']');
	helpptr = 2;
	helpline[1] = 289; //If you really absolutely need more capacity,
	helpline[0] = 290; //you can ask a wizard to enlarge me.
	if (interaction == error_stop_mode)
		interaction = scroll_mode;
	if (logopened)
		error();
	history = fatal_error_stop;
	jumpout();
}
