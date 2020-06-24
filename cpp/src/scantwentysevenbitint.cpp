#include "scantwentysevenbitint.h"
#include "scanint.h"
#include "printnl.h"
#include "print.h"
#include "interror.h"
#include "texte.h"

void scantwentysevenbitint(void)
{
	scanint();
	if (curval < 0 || curval > 134217727)
	{
		printnl("! ");
		print("Bad delimiter code");
		helpptr = 2;
		helpline[1] = "A numeric delimiter code must be between 0 and 2^{27}-1.";
		helpline[0] = "I changed this one to zero.";
		interror(curval);
		curval = 0;
	}
}
