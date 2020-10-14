#include "begininsertoradjust.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "sauvegarde.h"
#include "normalparagraph.h"
#include "etat.h"
#include "getnext.h"

void beginInsert(void)
{
	auto val = scaneightbitint(scannerstatus);
	if (val == 255)
	{
		error("You can't "+esc("insert")+"255", "I'm changing to \\insert0; box 255 is special.");
		val = 0;
	}
	auto m = new MemoryNode;
	m->int_ = val;
	savestack.push_back(m);
	newsavelevel(insert_group);
	(void)scanleftbrace();
	normalparagraph();
	pushnest();
	mode = -vmode;
	prev_depth = ignore_depth;
}

void beginAdjust(void)
{
	auto m = new MemoryNode;
	m->int_ = 255;
	savestack.push_back(m);
	newsavelevel(insert_group);
	(void)scanleftbrace();
	normalparagraph();
	pushnest();
	mode = -vmode;
	prev_depth = ignore_depth;
}
