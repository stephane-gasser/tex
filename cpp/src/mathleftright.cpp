#include "mathleftright.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "offsave.h"
#include "noeud.h"
#include "pushmath.h"
#include "sauvegarde.h"
#include "formule.h"

void mathleft(Token t)
{
	auto p = new LeftRightNoad(t);
	pushmath(math_left_group);
	head->link = p;
	tail = p;
}

void mathright(Token t)
{
	switch (curgroup)
	{
		case math_shift_group:
		{
			Delimiter dummy;
			scandelimiter(dummy, false, t);
			error("Extra "+esc("right"), "I'm ignoring a \\right that had no matching \\left.");
			break;
		}
		case math_left_group:
		{
			auto p = finmlist(new LeftRightNoad(t));
			unsave();
			auto n = new Noad(inner_noad);
			n->nucleus.math_type = sub_mlist;
			n->nucleus.info = p;
			tail_append(n);
			break;
		}
		default:
			offsave(t);
	}
}
