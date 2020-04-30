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
	save_type(saveptr) = 3;
	save_level(saveptr) = curgroup;
	save_index(saveptr) = curboundary;
	if (curlevel == 255)
		overflow(542, 255); //grouping levels
	curboundary = saveptr;
	curlevel++;
	saveptr++;
	curgroup = c;
}
