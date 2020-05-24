#include "charwarning.h"
#include "print.h"
#include "begindiagnostic.h"
#include "printnl.h"
#include "slowprint.h"
#include "printchar.h"
#include "enddiagnostic.h"

void charwarning(internalfontnumber f, eightbits c)
{
	if (int_par(tracing_lost_chars_code) > 0)
	{
		begindiagnostic();
		printnl("Missing character: There is no ");
		print(std::string(1, char(c)));
		print(" in font ");
		slowprint(fontname[f]);
		printchar('!');
		enddiagnostic(false);
	}
}
