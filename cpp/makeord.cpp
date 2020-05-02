#include "makeord.h"
#include "fetch.h"
#include "pauseforinstructions.h"
#include "newkern.h"
#include "newnoad.h"
#include "freenode.h"

void makeord(halfword q)
{
	bool label20 = false;
	do
	{
		if (link(q+3) == 0 && link(q+2) == 0 && link(q+1) == 1)
		{
			halfword p = link(q);
			if (p && type(p) >= 16 && type(p) <= 22 && link(p+1) == 1 && type(p+1) == type(q+1))
			{
				link(q+1) = 4;
				fetch(q+1);
				if (curi.b2%4 == 1)
				{
					int a = ligkernbase[curf]+curi.b3;
					curc = subtype(p+1);
					curi = fontinfo[a].qqqq;
					if (curi.b0 > 128)
					{
						a = ligkernbase[curf]+0x1'00*curi.b2+curi.b3;
						curi = fontinfo[a].qqqq;
					}
					while (true)
					{
						halfword r;
						if (curi.b1 == curc)
							if (curi.b0 <= 128)
								if (curi.b2 >= 128)
								{
									p = newkern(fontinfo[kernbase[curf]+0x1'00*curi.b2+curi.b3].int_);
									link(p) = link(q);
									link(q) = p;
									return;
								}
								else
								{
									if (interrupt)
										pauseforinstructions();
									switch (curi.b2)
									{
										case 1:
										case 5: 
											subtype(q+1) = curi.b3;
											break;
										case 2:
										case 6: 
											subtype(p+1) = curi.b3;
											break;
										case 3:
										case 7:
										case 11:
											r = newnoad();
											subtype(r+1) = curi.b3;
											type(r+1) = type(q+1);
											link(q) = r;
											link(r) = p;
											if (curi.b2 < 11)
												link(r+1) = 1;
											else
												link(r+1) = 4;
											break;
										default:
											link(q) = link(p);
											subtype(q+1) = curi.b3;
											mem[q+3] = mem[p+3];
											mem[q+2] = mem[p+2];
											freenode(p, 4);
									}
									if (curi.b2 > 3)
										return;
									link(q+1) = 1;
									label20 = true;
								}
						if (label20)
							break;
						if (curi.b0 >= 128)
							return;
						a += curi.b0+1;
						curi = fontinfo[a].qqqq;
					}
				}
			}
		}
	} while (label20);
}
