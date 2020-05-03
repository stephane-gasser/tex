#include "newinteraction.h"
#include "println.h"

void newinteraction(void)
{
	println();
	interaction = curchr;
	if (interaction == batch_mode)
		selector = 16;
	else
		selector = 17;
	if (logopened)
		selector += 2;
}
