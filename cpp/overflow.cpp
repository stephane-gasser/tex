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
	if (interaction == 3)
		printnl(262); //! 
	print(288); //TeX capacity exceeded, sorry [
	print(s);
	printchar('=');
	printint(n);
	printchar(']');
	helpptr = 2;
	helpline[1] = 289; //If you really absolutely need more capacity,
	helpline[0] = 290; //you can ask a wizard to enlarge me.
	if (interaction == 3)
		interaction = 2;
	if (logopened)
		error();
	history = 3;
	jumpout();
}
