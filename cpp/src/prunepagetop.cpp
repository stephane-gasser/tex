#include "prunepagetop.h"
#include "noeud.h"
#include "erreur.h"

LinkedNode* prunepagetop(halfword p)
{
	LinkedNode *prevp = temp_head, *q;
	LinkedNode *P;
	P->num = p;
	temp_head->link = P;
	while (P)
		switch (P->type)
		{
			case hlist_node:
			case vlist_node:
			case rule_node:
				q = newskipparam(split_top_skip_code);
				prevp->link = q;
				q->link = P;
				if (dynamic_cast<GlueNode*>(q)->glue_ptr->width > height(P->num))
					dynamic_cast<GlueNode*>(q)->glue_ptr->width -= height(P->num);
				else
					dynamic_cast<GlueNode*>(q)->glue_ptr->width = 0;
				P = nullptr;
				break;
			case whatsit_node:
			case mark_node:
			case ins_node:
				prevp = P;
				P = prevp->link;
				break;
			case glue_node:
			case kern_node:
			case penalty_node:
				q = P;
				P = q->link;
				q->link = nullptr;
				prevp->link = P;
				flushnodelist(q);
				break;
			default: 
				confusion("pruning");
		}
	return temp_head->link;
}
