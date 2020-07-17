#include "finmlist.h"
#include "erreur.h"
#include "popnest.h"

halfword finmlist(halfword p)
{
	halfword q;
	if (incompleat_noad)
	{
		link(incompleat_noad+3) = 3;
		info(incompleat_noad+3) = link(head);
		if (p == 0)
			q = incompleat_noad;
		else
		{
			q = info(incompleat_noad+2);
			if (type(q) != 30)
				confusion("right", curalign);
			info(incompleat_noad+2) = link(q);
			link(q) = incompleat_noad;
			link(incompleat_noad) = p;
		}
	}
	else
	{
		link(tail) = p;
		q = link(head);
	}
	popnest();
	return q;
}
