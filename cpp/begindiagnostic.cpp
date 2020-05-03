#include "begindiagnostic.h"

void begindiagnostic(void)
{
	oldsetting = selector;
	if (int_par(tracing_online_code) <= 0 && selector == 19)
	{
		selector--;
		if (history == spotless)
			history = warning_issued;
	}
}
