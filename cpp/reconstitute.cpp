#include "reconstitute.h"
#include "getavail.h"
#include "newligitem.h"
#include "pauseforinstructions.h"
#include "freenode.h"
#include "newligature.h"
#include "newkern.h"

smallnumber reconstitute(smallnumber j, smallnumber n, halfword bchar, halfword hchar)
{
	halfword p, t;
	fourquarters q;
	halfword currh, testchar;
	scaled w;
	fontindex k;
	hyphenpassed = 0;
	t = hold_head;
	w = 0;
	link(hold_head) = 0;
	curl = hu[j];
	curq = t;
	if (j == 0)
	{
		ligaturepresent = initlig;
		p = initlist;
		if (ligaturepresent)
			lfthit = initlft;
		while (p > 0)
		{
			link(t) = getavail();
			t = link(t);
			type(t) = hf;
			subtype(t) = subtype(p);
			p = link(p);
		}
	}
	else 
		if (curl < 256)
		{
			link(t) = getavail();
			t = link(t);
			type(t) = hf;
			subtype(t) = curl;
		}
	ligstack = 0;
	if (j < n)
		curr = hu[j+1];
	else
		curr = bchar;
	if (hyf[j]%2)
		currh = hchar;
	else
		currh = 256;
	bool skipLoop;
	bool recommence;
	do
	{
		recommence = false;
		skipLoop = false;
		if (curl == 256)
		{
			k = bcharlabel[hf];
			if (k == 0)
				skipLoop = true;
			else
				q = fontinfo[k].qqqq;
		}
		else
		{
			q = fontinfo[charbase[hf]+curl].qqqq;
			if (q.b2%4 != 1)
				skipLoop = true;
			else
			{
				k = ligkernbase[hf]+q.b3;
				q = fontinfo[k].qqqq;
				if (q.b0 > 0x80)
				{
					k = ligkernbase[hf]+0x1'00*q.b2+q.b3;
					q = fontinfo[k].qqqq;
				}
			}
		}
		if (!skipLoop)
			if (currh < 256)
				testchar = currh;
			else
				testchar = curr;
		while (!skipLoop)
		{
			if (q.b1 == testchar)
				if (q.b0 <= 128)
					if (currh < 256)
					{
						hyphenpassed = j;
						hchar = 256;
						currh = 256;
						recommence = true;
						break;
					}
					else
					{
						if (hchar < 256 && hyf[j]%2)
						{
							hyphenpassed = j;
							hchar = 256;
						}
						if (q.b2 < 128)
						{
							if (curl == 256)
								lfthit = true;
							if (j == n && ligstack == 0)
								rthit = true;
							if (interrupt)
								pauseforinstructions;
							switch (q.b2)
							{
								case 1:
								case 5:
									curl = q.b3;
									ligaturepresent = true;
									break;
								case 2:
								case 6:
									curr = q.b3;
									if (ligstack > 0)
										subtype(ligstack) = curr;
									else
									{
										ligstack = newligitem(curr);
										if (j == n)
											bchar = 256;
										else
										{
											p = getavail();
											link(ligstack+1) = p;
											subtype(p) = hu[j+1];
											type(p) = hf;
										}
									}
									break;
								case 3:
									curr = q.b3;
									p = ligstack;
									ligstack = newligitem(curr);
									link(ligstack) = p;
									break;
								case 7:
								case 11:
									if (ligaturepresent)
									{
										p = newligature(hf, curl, link(curq));
										if (lfthit)
										{
											subtype(p) = 2;
											lfthit = false;
										}
										link(curq) = p;
										t = p;
										ligaturepresent = false;
									}
									curq = t;
									curl = q.b3;
									ligaturepresent = true;
									break;
								default:
									curl = q.b3;
									ligaturepresent = true;
									if (ligstack > 0)
									{
										if (link(ligstack+1) > 0)
										{
											link(t) = link(ligstack+1);
											t = link(t);
											j++;
										}
										p = ligstack;
										ligstack = link(p);
										freenode(p, 2);
										if (ligstack == 0)
										{
											if (j < n)
												curr = hu[j+1];
											else
												curr = bchar;
											if (hyf[j]%2)
												currh = hchar;
											else
												currh = 256;
										}
										else
											curr = subtype(ligstack);
									}
									else 
										if (j == n)
										{
											skipLoop = true;
											continue;
										}
										else
										{
											link(t) = getavail();
											t = link(t);
											type(t) = hf;
											subtype(t) = curr;
											j++;
											if (j < n)
												curr = hu[j+1];
											else
												curr = bchar;
											if (hyf[j]%2)
												currh = hchar;
											else
												currh = 256;
										}
							}
							if (q.b2 > 4 && q.b2 != 7)
							{
								skipLoop = true;
								continue;
							}
							recommence = true;
							break;
						}
						w = fontinfo[kernbase[hf]+0x1'00*q.b2+q.b3].int_;
						skipLoop = true;
						continue;
					}
			if (q.b0 >= 128)
				if (currh == 256)
				{
					skipLoop = true;
					continue;
				}
				else
				{
					currh = 256;
					recommence = true;
					break;
				}
			k += q.b0+1;
			q = fontinfo[k].qqqq;
		}
		if (recommence)
			continue;
		if (ligaturepresent)
		{
			p = newligature(hf, curl, link(curq));
			if (lfthit)
			{
				subtype(p) = 2;
				lfthit = false;
			}
			if (rthit && ligstack == 0)
			{
				subtype(p)++;
				rthit = false;
			}
			link(curq) = p;
			t = p;
			ligaturepresent = false;
		}
		if (w)
		{
			link(t) = newkern(w);
			t = link(t);
			w = 0;
		}
		if (ligstack > 0)
		{
			curq = t;
			curl = subtype(ligstack);
			ligaturepresent = true;
			{
			if (link(ligstack+1) > 0)
			{
				link(t) = link(ligstack+1);
				t = link(t);
				j++;
			}
			p = ligstack;
			ligstack = link(p);
			freenode(p, 2);
			if (ligstack == 0)
			{
				if (j < n)
					curr = hu[j+1];
				else
					curr = bchar;
				if (hyf[j]%2)
					currh = hchar;
				else
					currh = 256;
			}
			else
				curr = subtype(ligstack);
			}
			recommence = true;
			continue;
		}
	} while (recommence);
	return j;
}
