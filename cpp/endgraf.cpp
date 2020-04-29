#include "endgraf.h"
#include "popnest.h"
#include "linebreak.h"
#include "normalparagraph.h"

void endgraf(void)
{
	if (curlist.modefield == 102)
	{
		if (curlist.headfield == curlist.tailfield)
			popnest();
		else
			linebreak(eqtb[5269].int_);
		normalparagraph();
		errorcount = 0;
	}
}
