#include "finmlist.h"
#include "erreur.h"
#include "popnest.h"

halfword finmlist(halfword p)
{
	LinkedNode *q;
	if (incompleat_noad) 
	{
		incompleat_noad->denominator.math_type = sub_mlist;
		incompleat_noad->denominator.info = head->link;
		if (p == 0)
			q = incompleat_noad;
		else
		{
			q = incompleat_noad->numerator.info;
			if (q->type != left_noad)
				confusion("right");
			incompleat_noad->numerator.info = q->link;
			q->link = incompleat_noad;
			incompleat_noad->link->num = p;
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
