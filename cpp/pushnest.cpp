#include "pushnest.h"
#include "overflow.h"
#include "getavail.h"

void pushnest(void)
{
	if (nestptr > maxneststack)
	{
		maxneststack = nestptr;
	if (nestptr == nestsize)
		overflow(362, nestsize); //semantic nest size
	}
	nest[nestptr++] = curlist;
	tail = head = getavail();
	prev_graf = 0;
	mode_line = line;
}
