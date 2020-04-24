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
			switch (mem[p].hh.b0)
			{
				case 0:
				case 1:
				case 13:
					r = getnode(7);
					mem[r+6] = mem[p+6];
					mem[r+5] = mem[p+5];
					mem[r+5].hh.rh = copynodelist(mem[p+5].hh.rh);
					words = 5;
					break;
				case 2:
					r = getnode(4);
					words = 4;
					break;
				case 3:
					r = getnode(5);
					mem[r+4] = mem[p+4];
					mem[mem[p+4].hh.rh].hh.rh++;
					mem[r+4].hh.lh = copynodelist(mem[p+4].hh.lh);
					words = 4;
					break;
				case 8:
					switch (mem[p].hh.b1)
					{
						case 0:
							r = getnode(3);
							words = 3;
							break;
						case 1:
						case 3:
							r = getnode(2);
							mem[mem[p+1].hh.rh].hh.lh++;
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
					mem[mem[p+1].hh.lh].hh.rh++;
					mem[r+1].hh.lh = mem[p+1].hh.lh;
					mem[r+1].hh.rh = copynodelist(mem[p+1].hh.rh);
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
					mem[r+1].hh.rh = copynodelist(mem[p+1].hh.rh);
					break;
				case 7:
					r = getnode(2);
					mem[r+1].hh.lh = copynodelist(mem[p+1].hh.lh);
					mem[r+1].hh.rh = copynodelist(mem[p+1].hh.rh);
					break;
				case 4:
					r = getnode(2);
					mem[mem[p+1].int_].hh.lh++;
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
		mem[q].hh.rh = r;
		q = r;
		p = mem[p].hh.rh;
	}
	mem[q].hh.rh = 0;
	q = mem[h].hh.rh;
	mem[h].hh.rh = avail;
	avail = h;
	return q;
}
