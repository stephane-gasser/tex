#include "alignpeek.h"
#include "lecture.h"
#include "sauvegarde.h"
#include "normalparagraph.h"
#include "finalign.h"
#include "initrow.h"
#include "initcol.h"

void alignpeek(AlignRecordNode* &loop)
{
	while (true)
	{
		alignstate = 1000000;
		auto t = getXTokenSkipSpace();
		if (t.cmd == no_align)
		{
			t = scanleftbrace();
			newsavelevel(no_align_group);
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

