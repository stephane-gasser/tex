#include "firmuptheline.h"
#include "println.h"
#include "print.h"
#include "printchar.h"
#include "terminput.h"

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
