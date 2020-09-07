#include "prunepagetop.h"
#include "noeud.h"
#include "erreur.h"

LinkedNode* prunepagetop(LinkedNode *p)
{
	LinkedNode *prevp = temp_head;
	temp_head->link = p;
	while (p)
		switch (p->type)
		{
			case hlist_node:
			case vlist_node:
			case rule_node:
			{
				auto q = newskipparam(split_top_skip_code);
				auto P = dynamic_cast<RuleNode*>(p);
				prevp->link = q;
				q->link = p;
				if (q->glue_ptr->width > P->height)
					q->glue_ptr->width -= P->height;
				else
					q->glue_ptr->width = 0;
				p = nullptr;
				break;
			}
			case whatsit_node:
			case mark_node:
			case ins_node:
				prevp = p;
				next(p);
				break;
			case glue_node:
			case kern_node:
			case penalty_node:
			{
				auto q = p;
				next(p);
				q->link = nullptr;
				prevp->link = p;
				flushnodelist(q);
				break;
			}
			default: 
				confusion("pruning");
		}
	return temp_head->link;
}
