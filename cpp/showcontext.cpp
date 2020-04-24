#include "showcontext.h"
#include "printnl.h"
#include "printint.h"
#include "printchar.h"
#include "print.h"
#include "println.h"
#include "printcs.h"
#include "showtokenlist.h"

void showcontext(void)
{
	int l;
	baseptr = inputptr;
	inputstack[baseptr] = curinput;
	int nn = -1;
	bool bottomline = false;
	while (true) 
	{
		curinput = inputstack[baseptr];
		if (curinput.statefield)
			if (curinput.namefield > 17 || baseptr == 0)
				bottomline = true;
		if (baseptr == inputptr || bottomline || nn < eqtb[5317].int_)
		{
			if (baseptr == inputptr || curinput.statefield || curinput.indexfield != 3 || curinput.locfield)
			{
				tally = 0;
				oldsetting = selector;
				if (curinput.statefield)
				{
					if (curinput.namefield <= 17)
						if (curinput.namefield == 0)
							if (baseptr == 0)
								printnl(574); //<*>
							else
								printnl(575); //<insert> 
						else
						{
							printnl(576); //<read 
							if (curinput.namefield == 17)
								printchar('*');
							else
								printint(curinput.namefield - 1);
							printchar('>');
						}
					else
					{
						printnl(577); //l.
						printint(line);
					}
					printchar(' ');
					l = tally;
					tally = 0;
					selector = 20;
					trickcount = 1000000;
					int j;
					if (buffer[curinput.limitfield] == eqtb[5311].int_)
						j = curinput.limitfield;
					else
						j = curinput.limitfield+1;
					if (j > 0)
						for (int i = curinput.startfield; i < j; i++)
						{
							if (i == curinput.locfield)
							{
								firstcount = tally;
								trickcount = tally + 1 + errorline - halferrorline;
								if (trickcount < errorline)
									trickcount = errorline;
							}
							print(buffer[i]);
						}
				}
				else
				{
					switch (curinput.indexfield)
					{
						case 0: 
							printnl(578); //<argument> 
							break;
						case 1:
						case 2:
							printnl(579); //<template> 
							break;
						case 3: 
							if (curinput.locfield == 0)
								printnl(580); //<recently read> 
							else
								printnl(581); //<to be read again> 
							break;
						case 4: 
							printnl(582); //<inserted text> 
							break;
						case 5:
							println();
							printcs(curinput.namefield);
							break;
						case 6: 
							printnl(583); //<output> 
							break;
						case 7: 
							printnl(584); //<everypar> 
							break;
						case 8: 
							printnl(585); //<everymath> 
							break;
						case 9: 
							printnl(586); //<everydisplay> 
							break;
						case 10: 
							printnl(587); //<everyhbox> 
							break;
						case 11: 
							printnl(588); //<everyvbox> 
							break;
						case 12: 
							printnl(589); //<everyjob> 
							break;
						case 13: 
							printnl(590); //<everycr> 
							break;
						case 14: 
							printnl(591); //<mark> 
							break;
						case 15: 
							printnl(592); //<write> 
							break;
						default: 
							printnl('?');
					}
					l = tally;
					tally = 0;
					selector = 20;
					trickcount = 1000000;
					if (curinput.indexfield < 5)
						showtokenlist(curinput.startfield, curinput.locfield, 100000);
					else
						showtokenlist(mem[curinput.startfield].hh.rh, curinput.locfield, 100000);
				}
				selector = oldsetting;
				if (trickcount == 1000000)
				{
					firstcount = tally;
					trickcount = tally + 1 + errorline - halferrorline;
					if (trickcount < errorline)
						trickcount = errorline;
				}
				int m;
				if (tally < trickcount)
					m = tally - firstcount;
				else
					m = trickcount - firstcount;
				int p, n;
				if (l + firstcount <= halferrorline)
				{
					p = 0;
					n = l + firstcount;
				}
				else
				{
					print(277); //...
					p = l + firstcount - halferrorline + 3;
					n = halferrorline;
				}
				for (int q = p; q < firstcount; q++)
					printchar(trickbuf[q%errorline]);
				println();
				for (int q = 0; q < n; q++)
					printchar(' ');
				if (m + n <= errorline)
					p = firstcount + m;
				else
					p = firstcount + (errorline - n - 3);
				for (int q = firstcount; q < p; q++)
					printchar(trickbuf[q%errorline]);
				if (m + n > errorline)
					print(277); //...
				nn++;
			}
		}
		else 
			if (nn == eqtb[5317].int_)
			{
				printnl(277); //...
				nn++;
			}
		if (bottomline)
			break;
		baseptr--;
	}
	curinput = inputstack[inputptr];
}
