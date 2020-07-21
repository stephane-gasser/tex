#include "alignpeek.h"
#include "lecture.h"
#include "noeud.h"
#include "normalparagraph.h"
#include "finalign.h"
#include "initrow.h"
#include "initcol.h"

void alignpeek(halfword &loop)
{
	while (true)
	{
		alignstate = 1000000;
		auto t = getXTokenSkipSpace();
		if (t.cmd == no_align)
		{
			t = scanleftbrace();
			newsavelevel(7);
			if (mode == -vmode)
				normalparagraph();
		}
		else 
			if (t.cmd == right_brace)
				finalign(loop);
			else 
				if (t.cmd == car_ret && t.chr == 258)
					continue;
				else
				{
					initrow();
					initcol(t);
				}
		break;
	}
}

