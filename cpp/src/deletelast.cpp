#include "deletelast.h"
#include "impression.h"
#include "erreur.h"
#include "noeud.h"

void deletelast(Token t)
{
	if (mode == vmode && tail == head)
	{
		if (t.chr != '\n' || lastglue)
			error("You can't use `"+cmdchr(t)+"' in "+asMode(mode), "Sorry...I usually can't take things from the current page."+std::string(t.chr == kern_node ? "Try `I\\kern-\\lastkern' instead." : t.chr == glue_node ? "Try `I\\vskip-\\lastskip' instead." : "Perhaps you can make the output routine do it."));
	}
	else 
		if (tail->type == t.chr)
		{
			LinkedNode *q = head, *p;
			do
			{
				auto p = q;
				if (q->type == disc_node) 
				{
					for (quarterword m = 1; m <= dynamic_cast<DiscNode*>(q)->replace_count; m++)
						next(p);
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
