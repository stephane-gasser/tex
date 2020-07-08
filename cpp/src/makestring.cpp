#include "makestring.h"
#include "erreur.h"
#include "texte.h"

std::string makestring(void)
{
/*	if (strptr == maxstrings)
		overflow("number of strings", maxstrings-initstrptr);*/
	strings.push_back(currentString);
	currentString = "";
	return strings.back();
//	strstart[++strptr] = poolptr;
//	return TXT(strptr-1);
}
