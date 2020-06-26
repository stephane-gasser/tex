#include "scanfourbitint.h"
#include "scanint.h"
#include "impression.h"
#include "interror.h"
#include "texte.h"

void scanfourbitint(void)
{
	scanint();
	if (curval < 0 || curval > 15)
	{
		print_err("Bad number");
		helpptr = 2;
		helpline[1] = "Since I expected to read a number between 0 and 15,";
		helpline[0] = "I changed this one to zero.";
		interror(curval);
		curval = 0;
	}
}
