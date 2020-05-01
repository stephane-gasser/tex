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
		printnl(824); //Missing character: There is no 
		print(c);
		print(825); // in font 
		slowprint(fontname[f]);
		printchar('!');
		enddiagnostic(false);
	}
}
