#include "package.h"
#include "unsave.h"
#include "popnest.h"
#include "boite.h"

static int box_max_depth(void) { return dimen_par(box_max_depth_code); }

void package(smallnumber c, Token t)
{
	unsave();
	saveptr -= 3;
	if (mode == -hmode)
		curbox = hpack(head->link, saved(2), saved(1));
	else
	{
		curbox = vpackage(head->link, saved(2), saved(1), box_max_depth());
		if (c == 4)
		{
			scaled h = 0;
			auto p = curbox->list_ptr;
			if (p && p->type <= rule_node)
				h = dynamic_cast<RuleNode*>(p)->height;
			curbox->depth += -h+curbox->height;
			curbox->height = h;
		}
	}
	popnest();
	boxend(saved(0));
}
