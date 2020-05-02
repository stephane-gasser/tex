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
	if (int_par(cur_fam_code) <= 0)
		curlang = 0;
	else 
		if (int_par(cur_fam_code) > 255)
			curlang = 0;
		else
		curlang = int_par(cur_fam_code);
	n = 0;
	p = 0;
	getxtoken();
	while (true)
	{
		switch (curcmd)
		{
			case letter:
			case other_char:
			case char_given:
				if (curchr == '-')
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
					if (lc_code(curchr) == 0)
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
							hc[n] = lc_code(curchr);
						}
				break;
			case char_num:
				scancharnum();
				curchr = curval;
				curcmd = char_given;
				continue;
			case spacer:
			case right_brace:
				if (n > 1)
				{
					n++;
					hc[n] = curlang;
					if (poolptr+n > poolsize)
						overflow(257, poolsize-initpoolptr); //pool size
					h = 0;
					for (j = 1; j <= n; j++)
					{
						h = (2*h+hc[j])%hyph_size;
						strpool[poolptr++] = hc[j];
					}
					s = makestring();
					if (hyphcount == hyph_size)
						overflow(947, hyph_size); //exception dictionary
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
							h = hyph_size;
					}
					hyphword[h] = s;
					hyphlist[h] = p;
				}
				if (curcmd == right_brace)
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
