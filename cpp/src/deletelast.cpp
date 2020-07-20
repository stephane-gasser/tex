#include "deletelast.h"
#include "impression.h"
#include "erreur.h"
#include "noeud.h"
#include "texte.h"

void deletelast(Token t)
{
	if (mode == vmode && tail == head)
	{
		if (t.chr != '\n' || lastglue != empty_flag)
			error("You can't use `"+cmdchr(t)+"' in "+asMode(mode), "Sorry...I usually can't take things from the current page."+std::string(t.chr == kern_node ? "Try `I\\kern-\\lastkern' instead." : t.chr == glue_node ? "Try `I\\vskip-\\lastskip' instead." : "Perhaps you can make the output routine do it."));
	}
	else 
		if (tail < himemmin)
			if (type(tail) == t.chr)
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
