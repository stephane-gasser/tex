#include "prunepagetop.h"
#include "noeud.h"
#include "erreur.h"

LinkedNode* prunepagetop(halfword p)
{
	LinkedNode *prevp = temp_head, *q;
	temp_head->link->num = p;
	while (p)
		switch (type(p))
		{
			case hlist_node:
			case vlist_node:
			case rule_node:
				q->num = newskipparam(split_top_skip_code);
				prevp->link = q;
				q->link->num = p;
				if (width(tempptr) > height(p))
					width(tempptr) -= height(p);
				else
					width(tempptr) = 0;
				p = 0;
				break;
			case whatsit_node:
			case mark_node:
			case ins_node:
				prevp->num = p;
				p = prevp->link->num;
				break;
			case glue_node:
			case kern_node:
			case penalty_node:
				q->num = p;
				p = q->link->num;
				q->link = nullptr;
				prevp->link->num = p;
				flushnodelist(q);
				break;
			default: 
				confusion("pruning");
		}
	return temp_head->link;
}
