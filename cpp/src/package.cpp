#include "package.h"
#include "sauvegarde.h"
#include "popnest.h"
#include "boite.h"

static int box_max_depth(void) { return dimen_par(box_max_depth_code); }

void package(smallnumber c, Token t)
{
	unsave();
	auto s2 = savestack.back().int_;
	savestack.pop_back();
	auto s1 = savestack.back().int_;
	savestack.pop_back();
	auto s0 = savestack.back().int_;
	savestack.pop_back();
	if (mode == -hmode)
		curbox = hpack(head->link, s2, s1);
	else
	{
		curbox = vpackage(head->link, s2, s1, box_max_depth());
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
	boxend(s0);
}
