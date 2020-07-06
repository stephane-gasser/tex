#include "scanfourbitint.h"
#include "scanint.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

void scanfourbitint(void)
{
	scanint();
	if (curval < 0 || curval > 15)
	{
		interror(curval, "Bad number", "Since I expected to read a number between 0 and 15,\nI changed this one to zero.");
		curval = 0;
	}
}
