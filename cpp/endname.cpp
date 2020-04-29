#include "endname.h"
#include "overflow.h"
#include "makestring.h"

void endname(void)
{
	if (strptr+3 > maxstrings)
		overflow(258, maxstrings-initstrptr);
	if (areadelimiter == 0)
		curarea = 338;
	else
	{
		curarea = strptr;
		strstart[1+strptr++] = strstart[strptr]+areadelimiter;
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
