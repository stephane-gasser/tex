#include "copynodelist.h"
#include "getavail.h"
#include "getnode.h"
#include "confusion.h"

halfword copynodelist(halfword p)
{
	auto h = getavail();
	auto q = h;
	while (p)
	{
		int words = 1;
		halfword r;
		if (p >= himemmin)
			r = getavail();
		else
			switch (type(p))
			{
				case hlist_node:
				case vlist_node:
				case unset_node:
					r = getnode(7);
					mem[r+6] = mem[p+6];
					mem[r+5] = mem[p+5];
					link(r+5) = copynodelist(link(p+5));
					words = 5;
					break;
				case rule_node:
					r = getnode(4);
					words = 4;
					break;
				case ins_node:
					r = getnode(5);
					mem[r+4] = mem[p+4];
					link(link(p+4))++;
					info(r+4) = copynodelist(info(p+4));
					words = 4;
					break;
				case whatsit_node:
					switch (subtype(p))
					{
						case 0:
							r = getnode(3);
							words = 3;
							break;
						case 1:
						case 3:
							r = getnode(2);
							info(link(p+1))++;
							words = 2;
							break;
						case 2:
						case 4:
							r = getnode(2);
							words = 2;
							break;
						default:
							confusion(1293); //ext2
					}
					break;
				case glue_node:
					r = getnode(2);
					link(info(p+1))++;
					info(r+1) = info(p+1);
					link(r+1) = copynodelist(link(p+1));
					break;
				case kern_node:
				case math_node:
				case penalty_node:
					r = getnode(2);
					words = 2;
					break;
				case ligature_node:
					r = getnode(2);
					mem[r+1] = mem[p+1];
					link(r+1) = copynodelist(link(p+1));
					break;
				case disc_node:
					r = getnode(2);
					info(r+1) = copynodelist(info(p+1));
					link(r+1) = copynodelist(link(p+1));
					break;
				case mark_node:
					r = getnode(2);
					info(mark_ptr(p))++;
					words = 2;
					break;
				case adjust_node:
					r = getnode(2);
					adjust_ptr(r) = copynodelist(adjust_ptr(p));
					break;
				default: 
					confusion(354); //copying
			}
		;
		for (;words > 0; words--)
			mem[r+words] = mem[p+words];
		link(q) = r;
		q = r;
		p = link(p);
	}
	link(q) = 0;
	q = link(h);
	link(h) = avail;
	avail = h;
	return q;
}
