#include "makestring.h"
#include "erreur.h"
#include "texte.h"

std::string makestring(void)
{
	strings.push_back(currentString);
	currentString = "";
	return strings.back();
}
