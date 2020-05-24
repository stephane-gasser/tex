#include "newsavelevel.h"
#include "overflow.h"

void newsavelevel(groupcode c)
{
	if (saveptr > maxsavestack)
	{
		maxsavestack = saveptr;
		if (maxsavestack > savesize-6)
			overflow("save size", savesize);
	}
	save_type(saveptr) = 3;
	save_level(saveptr) = curgroup;
	save_index(saveptr) = curboundary;
	if (curlevel == 255)
		overflow("grouping levels", 255);
	curboundary = saveptr;
	curlevel++;
	saveptr++;
	curgroup = c;
}
