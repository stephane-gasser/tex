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
		while (curcmd == 10);
		if (curcmd == 34)
		{
			scanleftbrace();
			newsavelevel(7);
			if (curlist.modefield == -1)
				normalparagraph();
		}
		else 
			if (curcmd == 2)
				finalign();
			else 
				if (curcmd == 5 && curchr == 258)
					continue;
				else
				{
					initrow();
					initcol();
				}
		break;
	}
}

