#include "enddiagnostic.h"
#include "println.h"
#include "printnl.h"

void enddiagnostic(bool blankline)
{
	printnl("");
	if (blankline)
		println();
	selector = oldsetting;
}
