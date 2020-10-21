#include "begininsertoradjust.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "sauvegarde.h"
#include "normalparagraph.h"
#include "etat.h"
#include "getnext.h"

static void beginCommon(char status, int val)
{
	savestack.push_back(new MemoryNode(val));
	newsavelevel(insert_group);
	scanner.leftBrace(status);
	normalparagraph();
	pushnest();
	mode = -vmode;
	prev_depth = ignore_depth;
}

void beginInsert(char status)
{
	auto val = scanner.getUInt8(status);
	if (val == 255)
	{
		error("You can't "+esc("insert")+"255", "I'm changing to \\insert0; box 255 is special.");
		val = 0;
	}
	beginCommon(status, val);
}

void beginAdjust(char status) { beginCommon(status, 255); }
