#include "scanfifteenbitint.h"
#include "scanint.h"
#include "printnl.h"
#include "print.h"
#include "interror.h"
#include "texte.h"

void scanfifteenbitint(void)
{
	scanint();
	if (curval < 0 || curval > 0x7F'FF)
	{
		printnl("! ");
		print("Bad mathchar");
		helpptr = 2;
		helpline[1] = txt("A mathchar number must be between 0 and 0x7F'FF.");
		helpline[0] = txt("I changed this one to zero.");
		interror(curval);
		curval = 0;
	}
}
