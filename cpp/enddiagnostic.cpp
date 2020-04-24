#include "enddiagnostic.h"
#include "println.h"
#include "printnl.h"

void enddiagnostic(bool blankline)
{
	printnl(338); //
	if (blankline)
		println();
	selector = oldsetting;
}
