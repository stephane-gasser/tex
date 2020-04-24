#include "flushnodelist.h"
#include "freenode.h"
#include "deleteglueref.h"
#include "deletetokenref.h"
#include "confusion.h"

void flushnodelist(halfword p)
{
	while (p)
	{
		auto q = mem[p].hh.rh;
		if (p >= himemmin)
		{
			mem[p].hh.rh = avail;
			avail = p;
		}
		else
		{
			switch (mem[p].hh.b0)
			{
				case 0:
				case 1:
				case 13:
					flushnodelist(mem[p+5].hh.rh);
					freenode(p, 7);
					break;
				case 2:
					freenode(p, 4);
					break;
				case 3:
					flushnodelist(mem[p+4].hh.lh);
					deleteglueref(mem[p+4].hh.rh);
					freenode(p, 5);
					break;
				case 8:
					switch (mem[p].hh.b1)
					{
						case 0:
							freenode(p, 3);
							break;
						case 1:
						case 3:
							deletetokenref(mem[p+1].hh.rh);
							freenode(p, 2);
							break;
						case 2:
						case 4: 
							freenode(p, 2);
							break;
						default: 
							confusion(1294); //ext3
					}
					break;
				case 10:
					if (mem[mem[p+1].hh.lh].hh.rh == 0)
						freenode(mem[p+1].hh.lh, 4);
					else
						mem[mem[p+1].hh.lh].hh.rh--;
					if (mem[p+1].hh.rh)
						flushnodelist(mem[p+1].hh.rh);
					freenode(p, 2);
					break;
				case 11:
				case 9:
				case 12: 
					freenode(p, 2);
					break;
				case 6: 
					flushnodelist(mem[p+1].hh.rh);
					freenode(p, 2);
					break;
				case 4: 
					deletetokenref(mem[p+1].int_);
					freenode(p, 2);
					break;
				case 7:
					flushnodelist(mem[p+1].hh.lh);
					flushnodelist(mem[p+1].hh.rh);
					freenode(p, 2);
					break;
				case 5: 
					flushnodelist(mem[p+1].int_);
					freenode(p, 2);
					break;
				case 14:
					freenode(p, 3);
					break;
				case 15:
					flushnodelist(mem[p+1].hh.lh);
					flushnodelist(mem[p+1].hh.rh);
					flushnodelist(mem[p+2].hh.lh);
					flushnodelist(mem[p+2].hh.rh);
					freenode(p, 3);
					break;
				case 16:
				case 17:
				case 18:
				case 19:
				case 20:
				case 21:
				case 22:
				case 23:
				case 24:
				case 27:
				case 26:
				case 29:
				case 28:
					if (mem[p+1].hh.rh >= 2)
						flushnodelist(mem[p+1].hh.lh);
					if (mem[p+2].hh.rh >= 2)
						flushnodelist(mem[p+2].hh.lh);
					if (mem[p+3].hh.rh >= 2)
						flushnodelist(mem[p+3].hh.lh);
					if (mem[p].hh.b0 == 24)
						freenode(p, 5);
					else 
						if (mem[p].hh.b0 == 28)
							freenode(p, 5);
						else
						freenode(p, 4);
					break;
				case 30:
				case 31:
					freenode(p, 4);
					break;
				case 25:
					flushnodelist(mem[p+2].hh.lh);
					flushnodelist(mem[p+3].hh.lh);
					freenode(p, 6);
					break;
				default: 
					confusion(353); //flushing
			}
		}
		p = q;
	}
}
