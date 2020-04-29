#include "changeiflimit.h"
#include "confusion.h"

void changeiflimit(smallnumber l, halfword p)
{
	if (p == condptr)
		iflimit = l;
	else
	{
		auto q = condptr;
		while (true)
		{
			if (q == 0)
				confusion(756); //if
			if (link(q) == p)
			{
				type(q) = l;
				return;
			}
			q = link(q);
		}
	}
}
