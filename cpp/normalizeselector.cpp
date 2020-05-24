#include "normalizeselector.h"
#include "openlogfile.h"

void normalizeselector(void)
{
	if (logopened)
		selector = term_and_log;
	else
	selector = term_only;
	if (jobname == "")
		openlogfile();
	if (interaction == batch_mode)
		selector--;
}
