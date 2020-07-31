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
		if (!tail->is_char_node())
			if (tail->type == t.chr)
			{
				LinkedNode *q = head, *p;
				do
				{
					p = q;
					if (!q->is_char_node()&& q->type == disc_node) 
					{
						for (quarterword m = 1; m <= subtype(q->num); m++)
							p = p->link;
						if (p == tail)
							return;
					}
					q = p->link;
				} while (q != tail);
				p->link = nullptr;
				flushnodelist(tail);
				tail = p;
			}
}
