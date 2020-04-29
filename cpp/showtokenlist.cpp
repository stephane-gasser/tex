#include "showtokenlist.h"
#include "printesc.h"
#include "printcs.h"
#include "print.h"
#include "printchar.h"

void showtokenlist(int p, int  q, int l)
{
	ASCIIcode matchchr = '#';
	ASCIIcode n = '0';
	tally = 0;
	while (p && tally < l)
	{
		if (p == q)
		{
			firstcount = tally;
			trickcount = tally + 1 + errorline - halferrorline;
			if (trickcount < errorline)
				trickcount = errorline;
		}
		if (p < himemmin || p > memend)
		{
			printesc(309); //CLOBBERED.
			return;
		}
		if (info(p) >= 4095)
			printcs(info(p)-4095);
		else
		{
			int m = info(p)/256;
			int c = info(p)%256;
			if (info(p) < 0)
				printesc(555); //BAD.
			else
				switch (m)
				{
					case 1:
					case 2:
					case 3:
					case 4:
					case 7:
					case 8:
					case 10:
					case 11:
					case 12: 
						print(c);
						break;
					case 6:
						print(c);
						print(c);
						break;
					case 5:
						print(matchchr);
						if (c <= 9)
							printchar(c+'0');
						else
						{
							printchar('!');
							return;
						}
						break;
					case 13:
						matchchr = c;
						print(c);
						n++;
						printchar(n);
						if (n > 57)
							return;
						break;
					case 14: 
						print(556); //->
						break;
					default:
			  			printesc(555); //BAD.
				}
		}
		p = link(p);
	}
	if (p)
		printesc(554); //ETC.
}
