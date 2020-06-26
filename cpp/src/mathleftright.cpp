#include "mathleftright.h"
#include "scandelimiter.h"
#include "impression.h"
#include "error.h"
#include "offsave.h"
#include "newnoad.h"
#include "pushmath.h"
#include "unsave.h"
#include "finmlist.h"
#include "texte.h"

void mathleftright(void)
{
	smallnumber t = curchr;
	if (t == right_noad && curgroup != math_left_group)
	{
		if (curgroup == math_shift_group)
		{
			scandelimiter(garbage, false);
			print_err("Extra "+esc("right"));
			helpptr = 1;
			helpline[0] = "I'm ignoring a \\right that had no matching \\left.";
			error();
		}
		else
			offsave();
	}
	else
	{
		auto p = newnoad();
		type(p) = t;
		scandelimiter(delimiter(p), false);
		if (t == left_noad)
		{
			pushmath(math_left_group);
			link(head) = p;
			tail = p;
		}
		else
		{
			p = finmlist(p);
			unsave();
			tail_append(newnoad());
			type(tail) = inner_noad;
			math_type(nucleus(tail)) = sub_mlist;
			info(nucleus(tail)) = p;
		}
	}
}
