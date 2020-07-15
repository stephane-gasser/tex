#include "deletelast.h"
#include "impression.h"
#include "erreur.h"
#include "noeud.h"
#include "texte.h"

void deletelast(eightbits cmd, halfword chr)
{
	if (mode == vmode && tail == head)
	{
		if (chr != '\n' || lastglue != empty_flag)
			error("You can't use `"+cmdchr(cmd, chr)+"' in "+asMode(mode), "Sorry...I usually can't take things from the current page."+std::string(chr == 11 ? "Try `I\\kern-\\lastkern' instead." : chr == '\n' ? "Try `I\\vskip-\\lastskip' instead." : "Perhaps you can make the output routine do it."));
	}
	else 
		if (tail < himemmin)
			if (type(tail) == chr)
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
