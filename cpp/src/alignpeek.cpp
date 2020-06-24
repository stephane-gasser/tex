#include "alignpeek.h"
#include "getxtoken.h"
#include "scanleftbrace.h"
#include "newsavelevel.h"
#include "normalparagraph.h"
#include "finalign.h"
#include "initrow.h"
#include "initcol.h"

void alignpeek(void)
{
	while (true)
	{
		alignstate = 1000000;
		do
			getxtoken();
		while (curcmd == spacer);
		if (curcmd == no_align)
		{
			scanleftbrace();
			newsavelevel(7);
			if (mode == -vmode)
				normalparagraph();
		}
		else 
			if (curcmd == right_brace)
				finalign();
			else 
				if (curcmd == car_ret && curchr == 258)
					continue;
				else
				{
					initrow();
					initcol();
				}
		break;
	}
}

