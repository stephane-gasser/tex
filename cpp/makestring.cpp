#include "makestring.h"
#include "overflow.h"

strnumber makestring(void)
{
	if (strptr == maxstrings)
		overflow("number of strings", maxstrings-initstrptr);
	strptr++;
	strstart[strptr] = poolptr;
	return strptr-1;
}
