#include "firmuptheline.h"
#include "impression.h"
#include "terminput.h"
#include "equivalent.h"

void firmuptheline(void)
{
	limit = last;
	if (pausing() > 0 && interaction > nonstop_mode)
	{
		print("\n"+std::string(buffer+start, buffer+limit)+"=>");
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
