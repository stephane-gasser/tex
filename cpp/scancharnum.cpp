#include "scancharnum.h"
#include "scanint.h"
#include "printnl.h"
#include "print.h"
#include "interror.h"
#include "texte.h"

void scancharnum(void)
{
	scanint();
	if (curval < 0 || curval > 255)
	{
		printnl("! ");
		print("Bad character code");
		helpptr = 2;
		helpline[1] = txt("A character number must be between 0 and 255.");
		helpline[0] = txt("I changed this one to zero.");
		interror(curval);
		curval = 0;
	}
}
