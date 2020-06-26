#include "scancharnum.h"
#include "scanint.h"
#include "impression.h"
#include "interror.h"
#include "texte.h"

void scancharnum(void)
{
	scanint();
	if (curval < 0 || curval > 255)
	{
		print_err("Bad character code");
		helpptr = 2;
		helpline[1] = "A character number must be between 0 and 255.";
		helpline[0] = "I changed this one to zero.";
		interror(curval);
		curval = 0;
	}
}
