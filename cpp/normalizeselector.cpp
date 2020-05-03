#include "normalizeselector.h"
#include "openlogfile.h"

void normalizeselector(void)
{
	if (logopened)
		selector = 19;
	else
	selector = 17;
	if (jobname == 0)
		openlogfile();
	if (interaction == batch_mode)
		selector--;
}
