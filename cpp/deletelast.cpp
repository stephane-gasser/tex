#include "deletelast.h"
#include "youcant.h"
#include "error.h"
#include "flushnodelist.h"

void deletelast(void)
{
	if (mode == vmode && tail == head)
	{
		if (curchr != '\n' || lastglue != empty_flag)
		{
			youcant();
			helpptr = 2;
			helpline[1] = 1070; //Sorry...I usually can't take things from the current page.
			helpline[0] = 1086; //Try `I\vskip-\lastskip' instead.
			if (curchr == 11)
				helpline[0] = 1087; //Try `I\kern-\lastkern' instead.
			else 
				if (curchr != '\n')
					helpline[0] = 1088; //Perhaps you can make the output routine do it.
			error();
		}
	}
	else 
		if (tail < himemmin)
			if (type(tail) == curchr)
			{
				halfword q = head, p;
				do
				{
					p = q;
					if (q < himemmin && type(q) == disc_node) //7
					{
						for (quarterword m = 1; m <= subtype(q); m++)
							p = link(p);
						if (p == tail)
							return;
					}
					q = link(p);
				} while (q != tail);
				link(p) = 0;
				flushnodelist(tail);
				tail = p;
			}
}
