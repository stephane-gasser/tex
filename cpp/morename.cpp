#include "morename.h"
#include "overflow.h"

bool morename(ASCIIcode c)
{
	if (c == ' ')
	return false;
	if (poolptr+1 > poolsize)
	overflow(257, poolsize-initpoolptr); //pool size
	strpool[poolptr++] = c;
	if (c == '>' || c == ':')
	{
		areadelimiter = poolptr-strstart[strptr];
		extdelimiter = 0;
	}
	else 
		if (c == '.' && extdelimiter == 0)
			extdelimiter = poolptr-strstart[strptr];
	return true;
}
