#include "charwarning.h"
#include "impression.h"

static int tracing_lost_chars(void) { return int_par(tracing_lost_chars_code); }

void charwarning(internalfontnumber f, eightbits c)
{
	if (tracing_lost_chars() > 0)
	{
		begindiagnostic();
		printnl("Missing character: There is no "+std::string(1, c)+" in font ");
		slowprint(fontname[f]);
		print("!");
		print(enddiagnostic(false));
	}
}
