#include "finmlist.h"
#include "confusion.h"
#include "popnest.h"

halfword finmlist(halfword p)
{
	halfword q;
	if (curlist.auxfield.int_)
	{
		link(curlist.auxfield.int_+3) = 3;
		info(curlist.auxfield.int_+3) = link(curlist.headfield);
		if (p == 0)
			q = curlist.auxfield.int_;
		else
		{
			q = info(curlist.auxfield.int_+2);
			if (type(q) != 30)
				confusion(876);
			info(curlist.auxfield.int_+2) = link(q);
			link(q) = curlist.auxfield.int_;
			link(curlist.auxfield.int_) = p;
		}
	}
	else
	{
		link(curlist.tailfield) = p;
		q = link(curlist.headfield);
	}
	popnest();
	return q;
}
