#include "scancharnum.h"
#include "scanint.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

void scancharnum(void)
{
	scanint();
	if (curval < 0 || curval > 255)
	{
		interror(curval, "Bad character code", "A character number must be between 0 and 255.\nI changed this one to zero.");
		curval = 0;
	}
}
