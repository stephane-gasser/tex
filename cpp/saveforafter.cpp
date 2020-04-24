#include "saveforafter.h"
#include "overflow.h"

void saveforafter(halfword t)
{
	if (curlevel > 1)
	{
		if (saveptr > maxsavestack)
		{
			maxsavestack = saveptr;
			if (maxsavestack > savesize - 6)
				overflow(541, savesize); //save size
		}
		savestack[saveptr].hh.b0 = 2;
		savestack[saveptr].hh.b1 = 0;
		savestack[saveptr].hh.rh = t;
		saveptr++;
	}
}
