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
		print(std::string(buffer+start, buffer+limit)+"=>");
		First = limit;
		terminput();
		if (last > First)
		{
			for (int k = First; k < last; k++)
				buffer[k+start-First] = buffer[k];
			limit = start+last-First;
		}
	}
}
