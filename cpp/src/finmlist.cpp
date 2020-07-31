#include "finmlist.h"
#include "erreur.h"
#include "popnest.h"

halfword finmlist(halfword p)
{
	LinkedNode *q;
	if (incompleat_noad)
	{
		math_type(denominator(incompleat_noad)) = sub_mlist;
		info(denominator(incompleat_noad)) = head->link->num;
		if (p == 0)
			q->num = incompleat_noad;
		else
		{
			q->num = info(numerator(incompleat_noad));
			if (q->type != left_noad)
				confusion("right");
			info(numerator(incompleat_noad)) = q->link->num;
			q->link->num = incompleat_noad;
			link(incompleat_noad) = p;
		}
	}
	else
	{
		tail->link->num = p;
		q = head->link;
	}
	popnest();
	return q->num;
}
