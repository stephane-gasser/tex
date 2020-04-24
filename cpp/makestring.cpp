#include "makestring.h"
#include "overflow.h"

strnumber makestring(void)
{
	if (strptr == maxstrings)
		overflow(258, maxstrings-initstrptr); //number of strings
	strptr++;
	strstart[strptr] = poolptr;
	return strptr-1;
}
