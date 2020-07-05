#include "deletelast.h"
#include "youcant.h"
#include "erreur.h"
#include "flushnodelist.h"
#include "texte.h"

static void erreurDeletelast(void)
{
	youcant();
	helpptr = 2;
	helpline[1] = "Sorry...I usually can't take things from the current page.";
	helpline[0] = curchr == 11 ? "Try `I\\kern-\\lastkern' instead." : curchr == '\n' ? "Try `I\\vskip-\\lastskip' instead." : "Perhaps you can make the output routine do it.";
	error();
}

void deletelast(void)
{
	if (mode == vmode && tail == head)
	{
		if (curchr != '\n' || lastglue != empty_flag)
			erreurDeletelast();
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
