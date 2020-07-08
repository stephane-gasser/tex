#include "begininsertoradjust.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "noeud.h"
#include "normalparagraph.h"
#include "pushnest.h"
#include "texte.h"

void begininsertoradjust(void)
{
	int val = 255;
	if (curcmd != vadjust)
	{
		val = scaneightbitint();
		if (val == 255)
		{
			error("You can't "+esc("insert")+"255", "I'm changing to \\insert0; box 255 is special.");
			val = 0;
		}
	}
	savestack[saveptr++].int_ = val;
	newsavelevel(insert_group);
	scanleftbrace();
	normalparagraph();
	pushnest();
	mode = -vmode;
	prev_depth = ignore_depth;
}
