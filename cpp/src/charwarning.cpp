#include "charwarning.h"
#include "impression.h"
#include "begindiagnostic.h"
#include "enddiagnostic.h"

static int tracing_lost_chars(void) { return int_par(tracing_lost_chars_code); }

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
