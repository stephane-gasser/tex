#include "makestring.h"
#include "erreur.h"
#include "texte.h"

std::string makestring(void)
{
	if (strptr == maxstrings)
		overflow("number of strings", maxstrings-initstrptr);
	strstart[++strptr] = poolptr;
	return TXT(strptr-1);
}
