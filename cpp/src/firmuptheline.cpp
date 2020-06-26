#include "firmuptheline.h"
#include "impression.h"
#include "terminput.h"

static int pausing(void) { return int_par(pausing_code); }

void firmuptheline(void)
{
	limit = last;
	if (pausing() > 0 && interaction > nonstop_mode)
	{
		println();
		for (int k = start; k < limit; k++)
			printchar(buffer[k]);
		First = limit;
		print("=>");
		terminput();
		if (last > First)
		{
			for (int k = First; k < last; k++)
				buffer[k+start-First] = buffer[k];
			limit = start+last-First;
		}
	}
}
