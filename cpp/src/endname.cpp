#include "endname.h"
#include "erreur.h"
#include "makestring.h"
#include "texte.h"

void endname(void)
{
	curarea = currentString.substr(0, areadelimiter);
	if (areadelimiter)
		strings.push_back(curarea);
	if (extdelimiter == 0)
	{
		curext = "";
		curname = currentString.substr(areadelimiter);
	}
	else
	{
		curext = currentString.substr(extdelimiter-1);
		curname = currentString.substr(areadelimiter, extdelimiter-1);
	}
	strings.push_back(curname);
	if (extdelimiter)
		strings.push_back(curext);
}
