#include "begindiagnostic.h"

void begindiagnostic(void)
{
	oldsetting = selector;
	if (tracing_online() <= 0 && selector == term_and_log)
	{
		selector--;
		if (history == spotless)
			history = warning_issued;
	}
}
