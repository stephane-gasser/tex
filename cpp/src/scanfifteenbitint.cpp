#include "scanfifteenbitint.h"
#include "scanint.h"
#include "impression.h"
#include "interror.h"
#include "texte.h"

void scanfifteenbitint(void)
{
	scanint();
	if (curval < 0 || curval > 0x7F'FF)
	{
		print_err("Bad mathchar");
		helpptr = 2;
		helpline[1] = "A mathchar number must be between 0 and 0x7F'FF.";
		helpline[0] = "I changed this one to zero.";
		interror(curval);
		curval = 0;
	}
}
