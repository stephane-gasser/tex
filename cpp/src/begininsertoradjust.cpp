#include "begininsertoradjust.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "sauvegarde.h"
#include "normalparagraph.h"
#include "pushnest.h"
#include "texte.h"

void begininsertoradjust(Token t)
{
	int val = 255;
	if (t.cmd != vadjust)
	{
		val = scaneightbitint();
		if (val == 255)
		{
			error("You can't "+esc("insert")+"255", "I'm changing to \\insert0; box 255 is special.");
			val = 0;
		}
	}
	memoryword m;
	m.int_ = val;
	savestack.push_back(m);
	newsavelevel(insert_group);
	t = scanleftbrace();
	normalparagraph();
	pushnest();
	mode = -vmode;
	prev_depth = ignore_depth;
}
