#include "prunepagetop.h"
#include "erreur.h"

LinkedNode* prunepagetop(LinkedNode *p)
{
	LinkedNode head;
	head.link = p; 
	LinkedNode *prevp = &head; // prevp -> p
	while (p)
		switch (p->type)
		{
			case hlist_node:
			case vlist_node:
			case rule_node:
			{
				auto q = newskipparam(split_top_skip_code);
				prevp->link = q; 
				q->link = p; // prevp -> q -> p
				if (auto P = dynamic_cast<RuleNode*>(p); q->glue_ptr->width > P->height)
					q->glue_ptr->width -= P->height;
				else
					q->glue_ptr->width = 0;
				return head.link;
			}
			case whatsit_node:
			case mark_node:
			case ins_node:
				next(prevp);
				next(p); // prevp -> p
				break;
			case glue_node:
			case kern_node:
			case penalty_node:
			{
				removeNodeAtStart(p);
				prevp->link = p; // prevp -> p
				break;
			}
			default: 
				confusion("pruning");
		}
	return head.link;
}
