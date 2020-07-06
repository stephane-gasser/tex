#include "scantwentysevenbitint.h"
#include "scanint.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

void scantwentysevenbitint(void)
{
	scanint();
	if (curval < 0 || curval >= 1<<27)
	{
		interror(curval, "Bad delimiter code", "A numeric delimiter code must be between 0 and 2^{27}-1.\nI changed this one to zero.");
		curval = 0;
	}
}
