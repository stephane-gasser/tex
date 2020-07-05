#include "scaneightbitint.h"
#include "scanint.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

static void erreurScaneightbitint(void)
{
	print_err("Bad register code");
	helpptr = 2;
	helpline[1] = "A register number must be between 0 and 255.";
	helpline[0] = "I changed this one to zero.";
	interror(curval);
}

void scaneightbitint(void)
{
	scanint();
	if (curval < 0 || curval > 255)
	{
		erreurScaneightbitint();
		curval = 0;
	}
}
