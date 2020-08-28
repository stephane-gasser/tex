#include "mathleftright.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "offsave.h"
#include "noeud.h"
#include "pushmath.h"
#include "sauvegarde.h"
#include "formule.h"
#include "texte.h"

void mathleftright(Token tk)
{
	smallnumber t = tk.chr;
	if (t == right_noad && curgroup != math_left_group)
	{
		if (curgroup == math_shift_group)
		{
			Delimiter dummy;
			scandelimiter(dummy, false, tk);
			error("Extra "+esc("right"), "I'm ignoring a \\right that had no matching \\left.");
		}
		else
			offsave(tk);
	}
	else
	{
		auto p = new LeftRightNoad(t);
		scandelimiter(p->delimiter, false, tk);
		if (t == left_noad)
		{
			pushmath(math_left_group);
			head->link = p;
			tail = p;
		}
		else
		{
			auto P = finmlist(p);
			unsave();
			auto n = new Noad;
			n->type = inner_noad;
			n->nucleus.math_type = sub_mlist;
			n->nucleus.info = P;
			tail_append(n);
		}
	}
}
