#include "newinteraction.h"
#include "impression.h"

void newinteraction(void)
{
	println();
	interaction = curchr;
	if (interaction == batch_mode)
		selector = no_print;
	else
		selector = term_only;
	if (logopened)
		selector += 2;
}