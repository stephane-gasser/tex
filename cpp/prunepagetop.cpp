#include "prunepagetop.h"
#include "newskipparam.h"
#include "flushnodelist.h"
#include "confusion.h"

halfword prunepagetop(halfword p)
{
	halfword prevp = temp_head, q;
	link(temp_head) = p;
	while (p)
		switch (type(p))
		{
			case 0:
			case 1:
			case 2:
				q = newskipparam(10);
				link(prevp) = q;
				link(q) = p;
				if (mem[tempptr+1].int_ > mem[p+3].int_)
					mem[tempptr+1].int_ -= mem[p+3].int_;
				else
					mem[tempptr+1].int_ = 0;
				p = 0;
				break;
			case 8:
			case 4:
			case 3:
				prevp = p;
				p = link(prevp);
				break;
			case 10:
			case 11:
			case 12:
				q = p;
				p = link(q);
				link(q) = 0;
				link(prevp) = p;
				flushnodelist(q);
				break;
			default: 
				confusion(958); //pruning
		}
	return link(temp_head);
}
