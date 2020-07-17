#include "begininsertoradjust.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "noeud.h"
#include "normalparagraph.h"
#include "pushnest.h"
#include "texte.h"

void begininsertoradjust(eightbits cmd, halfword align)
{
	int val = 255;
	if (cmd != vadjust)
	{
		val = scaneightbitint(align);
		if (val == 255)
		{
			error("You can't "+esc("insert")+"255", "I'm changing to \\insert0; box 255 is special.", align);
			val = 0;
		}
	}
	saved(0) = val;
	saveptr++;
	newsavelevel(insert_group);
	std::tie(cmd, std::ignore, std::ignore) = scanleftbrace(align);
	normalparagraph();
	pushnest();
	mode = -vmode;
	prev_depth = ignore_depth;
}
