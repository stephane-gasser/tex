#include "newsavelevel.h"
#include "overflow.h"

void newsavelevel(groupcode c)
{
	if (saveptr > maxsavestack)
	{
		maxsavestack = saveptr;
		if (maxsavestack > savesize - 6)
			overflow(541, savesize); //save size
	}
	savestack[saveptr].hh.b0 = 3;
	savestack[saveptr].hh.b1 = curgroup;
	savestack[saveptr].hh.rh = curboundary;
	if (curlevel == 255)
		overflow(542, 255); //grouping levels
	curboundary = saveptr;
	curlevel++;
	saveptr++;
	curgroup = c;
}
