#include "flushnodelist.h"
#include "freenode.h"
#include "deleteglueref.h"
#include "deletetokenref.h"
#include "confusion.h"

void flushnodelist(halfword p)
{
	while (p)
	{
		auto q = link(p);
		if (p >= himemmin)
		{
			link(p) = avail;
			avail = p;
		}
		else
		{
			switch (type(p))
			{
				case 0:
				case 1:
				case 13:
					flushnodelist(link(p+5));
					freenode(p, 7);
					break;
				case 2:
					freenode(p, 4);
					break;
				case 3:
					flushnodelist(info(p+4));
					deleteglueref(link(p+4));
					freenode(p, 5);
					break;
				case 8:
					switch (subtype(p))
					{
						case 0:
							freenode(p, 3);
							break;
						case 1:
						case 3:
							deletetokenref(link(p+1));
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
					if (link(info(p+1)) == 0)
						freenode(info(p+1), 4);
					else
						link(info(p+1))--;
					if (link(p+1))
						flushnodelist(link(p+1));
					freenode(p, 2);
					break;
				case 11:
				case 9:
				case 12: 
					freenode(p, 2);
					break;
				case 6: 
					flushnodelist(link(p+1));
					freenode(p, 2);
					break;
				case 4: 
					deletetokenref(mem[p+1].int_);
					freenode(p, 2);
					break;
				case 7:
					flushnodelist(info(p+1));
					flushnodelist(link(p+1));
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
					flushnodelist(info(p+1));
					flushnodelist(link(p+1));
					flushnodelist(info(p+2));
					flushnodelist(link(p+2));
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
					if (link(p+1) >= 2)
						flushnodelist(info(p+1));
					if (link(p+2) >= 2)
						flushnodelist(info(p+2));
					if (link(p+3) >= 2)
						flushnodelist(info(p+3));
					if (type(p) == 24)
						freenode(p, 5);
					else 
						if (type(p) == 28)
							freenode(p, 5);
						else
						freenode(p, 4);
					break;
				case 30:
				case 31:
					freenode(p, 4);
					break;
				case 25:
					flushnodelist(info(p+2));
					flushnodelist(info(p+3));
					freenode(p, 6);
					break;
				default: 
					confusion(353); //flushing
			}
		}
		p = q;
	}
}
