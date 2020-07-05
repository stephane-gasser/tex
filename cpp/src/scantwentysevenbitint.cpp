#include "scantwentysevenbitint.h"
#include "scanint.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

static void erreurScantwentysevenbitint(void)
{
	print_err("Bad delimiter code");
	helpptr = 2;
	helpline[1] = "A numeric delimiter code must be between 0 and 2^{27}-1.";
	helpline[0] = "I changed this one to zero.";
	interror(curval);
}

void scantwentysevenbitint(void)
{
	scanint();
	if (curval < 0 || curval >= 1<<27)
	{
		erreurScantwentysevenbitint();
		curval = 0;
	}
}
