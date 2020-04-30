#include "eqsave.h"
#include "overflow.h"

void eqsave(halfword p, quarterword l)
{
	if (saveptr > maxsavestack)
	{
		maxsavestack = saveptr;
		if (maxsavestack > savesize - 6)
			overflow(541, savesize); //save size
	}
	if (l == 0)
		save_type(saveptr) = 1;
	else
	{
		savestack[saveptr++] = eqtb[p];
		save_type(saveptr) = 0;
	}
	save_level(saveptr) = l;
	save_index(saveptr) = p;
	saveptr++;
}
