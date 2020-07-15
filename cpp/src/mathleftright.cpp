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

void mathleftright(eightbits cmd, halfword chr, halfword tok)
{
	smallnumber t = chr;
	if (t == right_noad && curgroup != math_left_group)
	{
		if (curgroup == math_shift_group)
		{
			scandelimiter(garbage, false, tok);
			error("Extra "+esc("right"), "I'm ignoring a \\right that had no matching \\left.");
		}
		else
			offsave(cmd, chr, tok);
	}
	else
	{
		auto p = newnoad();
		type(p) = t;
		scandelimiter(delimiter(p), false, tok);
		if (t == left_noad)
		{
			pushmath(math_left_group);
			link(head) = p;
			tail = p;
		}
		else
		{
			p = finmlist(p);
			unsave(tok);
			tail_append(newnoad());
			type(tail) = inner_noad;
			math_type(nucleus(tail)) = sub_mlist;
			info(nucleus(tail)) = p;
		}
	}
}
