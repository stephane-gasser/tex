#include "mathleftright.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "noeud.h"
#include "pushmath.h"
#include "sauvegarde.h"
#include "formule.h"
#include "etat.h"
#include "getnext.h"

void mathleft(char status, Token t)
{
	pushmath(math_left_group);
	tail_append(new LeftRightNoad(status, t));
}

void mathright(char status, Token t)
{
	switch (curgroup)
	{
		case math_left_group:
		{
			auto p = finmlist(new LeftRightNoad(status, t));
			unsave();
			auto n = new Noad(inner_noad);
			n->nucleus.math_type = sub_mlist;
			n->nucleus.info = p;
			tail_append(n);
			break;
		}
		case math_shift_group:
		{
			Delimiter dummy;
			dummy.scan(status, false, t);
			error("Extra "+esc("right"), "I'm ignoring a \\right that had no matching \\left.");
			break;
		}
		default:
			offsave(t); //erreur curgroup
	}
}
