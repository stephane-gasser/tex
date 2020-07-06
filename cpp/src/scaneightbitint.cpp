#include "scaneightbitint.h"
#include "scanint.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

void scaneightbitint(void)
{
	scanint();
	if (curval < 0 || curval > 255)
	{
		interror(curval, "Bad register code", "A register number must be between 0 and 255.\nI changed this one to zero.");
		curval = 0;
	}
}
