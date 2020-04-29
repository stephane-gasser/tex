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
				case 0:
				case 1:
				case 13:
					r = getnode(7);
					mem[r+6] = mem[p+6];
					mem[r+5] = mem[p+5];
					link(r+5) = copynodelist(link(p+5));
					words = 5;
					break;
				case 2:
					r = getnode(4);
					words = 4;
					break;
				case 3:
					r = getnode(5);
					mem[r+4] = mem[p+4];
					link(link(p+4))++;
					info(r+4) = copynodelist(info(p+4));
					words = 4;
					break;
				case 8:
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
				case 10:
					r = getnode(2);
					link(info(p+1))++;
					info(r+1) = info(p+1);
					link(r+1) = copynodelist(link(p+1));
					break;
				case 11:
				case 9:
				case 12:
					r = getnode(2);
					words = 2;
					break;
				case 6:
					r = getnode(2);
					mem[r+1] = mem[p+1];
					link(r+1) = copynodelist(link(p+1));
					break;
				case 7:
					r = getnode(2);
					info(r+1) = copynodelist(info(p+1));
					link(r+1) = copynodelist(link(p+1));
					break;
				case 4:
					r = getnode(2);
					info(mem[p+1].int_)++;
					words = 2;
					break;
				case 5:
					r = getnode(2);
					mem[r+1].int_ = copynodelist(mem[p+1].int_);
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
