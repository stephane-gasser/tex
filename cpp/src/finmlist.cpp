#include "finmlist.h"
#include "erreur.h"
#include "popnest.h"

Noad* finmlist(Noad *p)
{
	static Noad *q;
	if (incompleat_noad) 
	{
		incompleat_noad->denominator.math_type = sub_mlist;
		incompleat_noad->denominator.info = head->link;
		if (p == nullptr)
			q = incompleat_noad;
		else
		{
			q = dynamic_cast<Noad*>(incompleat_noad->numerator.info);
			if (q->type != left_noad)
				confusion("right");
			incompleat_noad->numerator.info = q->link;
			q->link = incompleat_noad;
			incompleat_noad->link = p;
		}
	}
	else
	{
		tail->link = p;
		q = dynamic_cast<Noad*>(head->link);
	}
	popnest();
	return q;
}
