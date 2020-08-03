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
			scandelimiter(garbage->num, false, tk);
			error("Extra "+esc("right"), "I'm ignoring a \\right that had no matching \\left.");
		}
		else
			offsave(tk);
	}
	else
	{
		LinkedNode *p;
		p->num = newnoad();
		p->type = t;
		scandelimiter(delimiter(p->num), false, tk);
		if (t == left_noad)
		{
			pushmath(math_left_group);
			head->link = p;
			tail = p;
		}
		else
		{
			p->num = finmlist(p->num);
			unsave();
			tail_append(newnoad());
			tail->type = inner_noad;
			math_type(nucleus(tail->num)) = sub_mlist;
			info(nucleus(tail->num)) = p->num;
		}
	}
}
