#include "endname.h"
#include "overflow.h"
#include "makestring.h"

void endname(void)
{
	if (strptr+3 > maxstrings)
		overflow("number of strings", maxstrings-initstrptr);
	if (areadelimiter == 0)
		curarea = 338;
	else
	{
		curarea = strptr;
		strstart[1+strptr] = strstart[strptr]+areadelimiter;
		strptr++;
	}
	if (extdelimiter == 0)
	{
		curext = 338;
		curname = makestring();
	}
	else
	{
		curname = strptr;
		strstart[1+strptr++] = strstart[strptr]+extdelimiter-areadelimiter-1;
		curext = makestring();
	}
}
