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
			linebreak(widow_penalty());
		normalparagraph();
		errorcount = 0;
	}
}
