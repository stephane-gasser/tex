#include "scanfourbitint.h"
#include "scanint.h"
#include "printnl.h"
#include "print.h"
#include "interror.h"
#include "texte.h"

void scanfourbitint(void)
{
	scanint();
	if (curval < 0 || curval > 15)
	{
		printnl("! ");
		print("Bad number");
		helpptr = 2;
		helpline[1] = txt("Since I expected to read a number between 0 and 15,");
		helpline[0] = txt("I changed this one to zero.");
		interror(curval);
		curval = 0;
	}
}
