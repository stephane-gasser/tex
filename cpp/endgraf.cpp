#include "endgraf.h"
#include "popnest.h"
#include "linebreak.h"
#include "normalparagraph.h"

void endgraf(void)
{
	if (mode == hmode)
	{
		if (head == tail)
			popnest();
		else
			linebreak(int_par(widow_penalty_code));
		normalparagraph();
		errorcount = 0;
	}
}
