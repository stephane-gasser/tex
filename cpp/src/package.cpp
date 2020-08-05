#include "package.h"
#include "hpack.h"
#include "unsave.h"
#include "vpackage.h"
#include "popnest.h"
#include "boite.h"

static int box_max_depth(void) { return dimen_par(box_max_depth_code); }

void package(smallnumber c, Token t)
{
	scaled d = box_max_depth();
	unsave();
	saveptr -= 3;
	if (mode == -hmode)
		curbox = hpack(head->link, saved(2), saved(1))->num;
	else
	{
		curbox = vpackage(head->link->num, saved(2), saved(1), d);
		if (c == 4)
		{
			scaled h = 0;
			auto p = list_ptr(curbox);
			if (p && type(p) <= rule_node)
				h = height(p);
			depth(curbox) += -h+height(curbox);
			height(curbox) = h;
		}
	}
	popnest();
	boxend(saved(0));
}
