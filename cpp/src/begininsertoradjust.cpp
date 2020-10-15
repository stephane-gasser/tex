#include "begininsertoradjust.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "sauvegarde.h"
#include "normalparagraph.h"
#include "etat.h"
#include "getnext.h"

void beginInsert(char status)
{
	auto val = scaneightbitint(status);
	if (val == 255)
	{
		error("You can't "+esc("insert")+"255", "I'm changing to \\insert0; box 255 is special.");
		val = 0;
	}
	auto m = new MemoryNode(0, 0, val);
	savestack.push_back(m);
	newsavelevel(insert_group);
	scanleftbrace(status);
	normalparagraph();
	pushnest();
	mode = -vmode;
	prev_depth = ignore_depth;
}

void beginAdjust(char status)
{
	auto m = new MemoryNode(0, 0, 255);
	savestack.push_back(m);
	newsavelevel(insert_group);
	scanleftbrace(status);
	normalparagraph();
	pushnest();
	mode = -vmode;
	prev_depth = ignore_depth;
}
