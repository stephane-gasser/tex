#include "package.h"
#include "hpack.h"
#include "unsave.h"
#include "vpackage.h"
#include "popnest.h"
#include "boxend.h"

static int box_max_depth(void) { return dimen_par(box_max_depth_code); }

void package(smallnumber c, halfword tok)
{
	scaled d = box_max_depth();
	unsave(tok);
	saveptr -= 3;
	if (mode == -hmode)
		curbox = hpack(link(head), saved(2), saved(1));
	else
	{
		curbox = vpackage(link(head), saved(2), saved(1), d);
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
