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
		savestack[saveptr].hh.b0 = 1;
	else
	{
		savestack[saveptr++] = eqtb[p];
		savestack[saveptr].hh.b0 = 0;
	}
	savestack[saveptr].hh.b1 = l;
	savestack[saveptr].hh.rh = p;
	saveptr++;
}
