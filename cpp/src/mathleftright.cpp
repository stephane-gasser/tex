#include "mathleftright.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "offsave.h"
#include "noeud.h"
#include "pushmath.h"
#include "unsave.h"
#include "finmlist.h"
#include "texte.h"

void mathleftright(Token tk)
{
	smallnumber t = tk.chr;
	if (t == right_noad && curgroup != math_left_group)
	{
		if (curgroup == math_shift_group)
		{
			scandelimiter(garbage, false, tk);
			error("Extra "+esc("right"), "I'm ignoring a \\right that had no matching \\left.");
		}
		else
			offsave(tk);
	}
	else
	{
		auto p = newnoad();
		type(p) = t;
		scandelimiter(delimiter(p), false, tk);
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
