#include "makenamestring.h"
#include "makestring.h"

strnumber makenamestring(void)
{
	if (poolptr+namelength > poolsize || strptr == maxstrings || poolptr-strstart[strptr] > 0)
		return 63;
	else
	{
		for (int k = 1; k <= namelength; k++)
			strpool[poolptr++] = xord[nameoffile[k]];
		return makestring();
	}
}
