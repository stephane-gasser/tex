#include "deletelast.h"
#include "youcant.h"
#include "error.h"
#include "flushnodelist.h"

void deletelast(void)
{
	if (curlist.modefield == 1 && curlist.tailfield == curlist.headfield)
	{
		if (curchr != '\n' || lastglue != 65535)
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
		if (curlist.tailfield < himemmin)
			if (type(curlist.tailfield) == curchr)
			{
				halfword q = curlist.headfield, p;
				do
				{
					p = q;
					if (q < himemmin && type(q) == disc_node) //7
					{
						for (quarterword m = 1; m <= subtype(q); m++)
							p = link(p);
						if (p == curlist.tailfield)
							return;
					}
					q = link(p);
				} while (q != curlist.tailfield);
				link(p) = 0;
				flushnodelist(curlist.tailfield);
				curlist.tailfield = p;
			}
}
