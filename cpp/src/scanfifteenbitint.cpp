#include "scanfifteenbitint.h"
#include "scanint.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

void scanfifteenbitint(void)
{
	scanint();
	if (curval < 0 || curval > 0x7F'FF)
	{
		interror(curval, "Bad mathchar", "A mathchar number must be between 0 and 0x7F'FF.\nI changed this one to zero.");
		curval = 0;
	}
}
