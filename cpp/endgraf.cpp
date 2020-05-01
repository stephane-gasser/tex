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
			linebreak(int_par(widow_penalty_code));
		normalparagraph();
		errorcount = 0;
	}
}
