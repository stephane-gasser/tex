#include "endgraf.h"
#include "popnest.h"
#include "linebreak.h"
#include "normalparagraph.h"

static int widow_penalty(void) { return int_par(widow_penalty_code); }

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
