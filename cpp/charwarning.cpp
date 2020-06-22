#include "charwarning.h"
#include "printchar.h"
#include "print.h"
#include "begindiagnostic.h"
#include "printnl.h"
#include "slowprint.h"
#include "printchar.h"
#include "enddiagnostic.h"

void charwarning(internalfontnumber f, eightbits c)
{
	if (tracing_lost_chars() > 0)
	{
		begindiagnostic();
		printnl("Missing character: There is no ");
		printchar(c);
		print(" in font ");
		slowprint(fontname[f]);
		printchar('!');
		enddiagnostic(false);
	}
}
