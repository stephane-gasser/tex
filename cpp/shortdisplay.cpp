#include "shortdisplay.h"
#include "printchar.h"
#include "print.h"
#include "printesc.h"
#include "constantes.h"

void shortdisplay(int p)
{
	while (p > memmin)
	{
		if (p >= himemmin)
		{
			if (p <= memend)
			{
				if (mem[p].hh.b0 != fontinshortdisplay)
				{
					if (mem[p].hh.b0 < 0 || mem[p].hh.b0 > fontmax)
						printchar('*');
					else
						printesc(hash[frozen_null_font+mem[p].hh.b0].rh);
					printchar(' ');
					fontinshortdisplay = mem[p].hh.b0;
				}
				print(mem[p].hh.b1);
			}
		}
		else
		switch (mem[p].hh.b0)
		{
			case 0:
			case 1:
			case 3:
			case 8:
			case 4:
			case 5:
			case 13: 
				print(308); //[]
				break;
			case 2: 
				printchar('|');
				break;
			case 10: 
				if (mem[p+1].hh.lh)
					printchar(' ');
				break;
			case 9:
				printchar('$');
				break;
			case 6:
				shortdisplay(mem[p+1].hh.rh);
				break;
			case 7:
				shortdisplay(mem[p+1].hh.lh);
				shortdisplay(mem[p+1].hh.rh);
				for (int n = mem[p].hh.b1; n > 0; n--)
					if (mem[p].hh.rh)
						p = mem[p].hh.rh;
		}
		p = mem[p].hh.rh;
	}
}
