#include "charwarning.h"
#include "impression.h"
#include "police.h"

static int tracing_lost_chars(void) { return int_par(tracing_lost_chars_code); }

void charwarning(internalfontnumber f, eightbits c)
{
	if (tracing_lost_chars() > 0)
		diagnostic("\rMissing character: There is no "+std::string(1, c)+" in font "+fonts[f].name+"!");
}
