#include "newhyphexceptions.h"
#include "scanleftbrace.h"
#include "getxtoken.h"
#include "getavail.h"
#include "printnl.h"
#include "print.h"
#include "error.h"
#include "scancharnum.h"
#include "overflow.h"
#include "makestring.h"
#include "printesc.h"
#include "error.h"

void newhyphexceptions(void)
{
	char n, j;
	hyphpointer h;
	strnumber k;
	halfword p, q;
	strnumber s, t;
	poolpointer u, v;
	scanleftbrace();
	if (eqtb[5313].int_ <= 0)
		curlang = 0;
	else 
		if (eqtb[5313].int_ > 255)
			curlang = 0;
		else
		curlang = eqtb[5313].int_;
	n = 0;
	p = 0;
	getxtoken();
	while (true)
	{
		switch (curcmd)
		{
			case 11:
			case 12:
			case 68:
				if (curchr == 45)
				{
					if (n < 63)
					{
						q = getavail();
						link(q) = p;
						info(q) = n;
						p = q;
					}
				}
				else 
					if (eqtb[4239+curchr].hh.rh == 0)
					{
						if (interaction == 3)
							printnl(262); //! 
						print(944); //Not a letter
						helpptr = 2;
						helpline[1] = 945; //Letters in \hyphenation words must have \lccode>0.
						helpline[0] = 946; //7Proceed; I'll ignore the character I just read.
						error();
					}
					else 
						if (n < 63)
						{
							n++;
							hc[n] = eqtb[4239+curchr].hh.rh;
						}
				break;
			case 16:
				scancharnum();
				curchr = curval;
				curcmd = 68;
				continue;
			case 10:
			case 2:
				if (n > 1)
				{
					n++;
					hc[n] = curlang;
					if (poolptr+n > poolsize)
						overflow(257, poolsize-initpoolptr); //pool size
					h = 0;
					for (j = 1; j <= n; j++)
					{
						h = (2*h+hc[j])%307;
						strpool[poolptr++] = hc[j];
					}
					s = makestring();
					if (hyphcount == 307)
						overflow(947, 307); //exception dictionary
					hyphcount++;
					while (hyphword[h])
					{
						k = hyphword[h];
						if (strstart[k+1]-strstart[k] < strstart[s+1]-strstart[s])
						{
							q = hyphlist[h];
							hyphlist[h] = p;
							p = q;
							t = hyphword[h];
							hyphword[h] = s;
							s = t;
						}
						else 
							if (strstart[k+1]-strstart[k] == strstart[s+1]-strstart[s])
							{
								u = strstart[k];
								v = strstart[s];
								bool label45 = false;
								do
								{
									if (strpool[u] < strpool[v])
									{
										q = hyphlist[h];
										hyphlist[h] = p;
										p = q;
										t = hyphword[h];
										hyphword[h] = s;
										s = t;
										label45 = true;
									}
									if (strpool[u] > strpool[v])
										label45 = true;
									if (label45)
										break;
									u++;
									v++;
								} while (u != strstart[k+1]);
								if (!label45)
								{
									q = hyphlist[h];
									hyphlist[h] = p;
									p = q;
									t = hyphword[h];
									hyphword[h] = s;
									s = t;
								}
							}
						if (h > 0)
							h--;
						else
							h = 307;
					}
					hyphword[h] = s;
					hyphlist[h] = p;
				}
				if (curcmd == 2)
					return;
				n = 0;
				p = 0;
				break;
			default:
				{
				if (interaction == 3)
					printnl(262); //! 
				print(680); //Improper 
				}
				printesc(940); //hyphenation
				print(941); // will be flushed
				{
				helpptr = 2;
				helpline[1] = 942; //Hyphenation exceptions must contain only letters
				helpline[0] = 943; //and hyphens. But continue; I'll forgive and forget.
				}
				error();
		}
		getxtoken();
	}
}
