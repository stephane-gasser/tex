#include "prunepagetop.h"
#include "noeud.h"
#include "erreur.h"

halfword prunepagetop(halfword p)
{
	halfword prevp = temp_head, q;
	link(temp_head) = p;
	while (p)
		switch (type(p))
		{
			case hlist_node:
			case vlist_node:
			case rule_node:
				q = newskipparam(split_top_skip_code);
				link(prevp) = q;
				link(q) = p;
				if (width(tempptr) > height(p))
					width(tempptr) -= height(p);
				else
					width(tempptr) = 0;
				p = 0;
				break;
			case whatsit_node:
			case mark_node:
			case ins_node:
				prevp = p;
				p = link(prevp);
				break;
			case glue_node:
			case kern_node:
			case penalty_node:
				q = p;
				p = link(q);
				link(q) = 0;
				link(prevp) = p;
				flushnodelist(q);
				break;
			default: 
				confusion("pruning");
		}
	return link(temp_head);
}
