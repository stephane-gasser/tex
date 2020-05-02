#include "newwritewhatsit.h"
#include "newwhatsit.h"
#include "scanfourbitint.h"
#include "scanint.h"


void newwritewhatsit(smallnumber w)
{
	newwhatsit(curchr, w);
	if (w != 2)
		scanfourbitint();
	else
	{
		scanint();
		if (curval < 0)
			curval = 17;
		else 
			if (curval > 15)
				curval = 16;
	}
	info(tail+1) = curval;
}
