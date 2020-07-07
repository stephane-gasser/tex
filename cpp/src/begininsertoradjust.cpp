#include "begininsertoradjust.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "newsavelevel.h"
#include "normalparagraph.h"
#include "pushnest.h"
#include "texte.h"

void begininsertoradjust(void)
{
	if (curcmd == vadjust)
		curval = 255;
	else
	{
		curval = scaneightbitint();
		if (curval == 255)
		{
			error("You can't "+esc("insert")+"255", "I'm changing to \\insert0; box 255 is special.");
			curval = 0;
		}
	}
	savestack[saveptr++].int_ = curval;
	newsavelevel(insert_group);
	scanleftbrace();
	normalparagraph();
	pushnest();
	mode = -vmode;
	prev_depth = ignore_depth;
}
