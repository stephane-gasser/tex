#include "makestring.h"
#include "overflow.h"
#include "texte.h"

std::string makestring(void)
{
	if (strptr == maxstrings)
		overflow("number of strings", maxstrings-initstrptr);
	strptr++;
	strstart[strptr] = poolptr;
	return TXT(strptr-1);
}
