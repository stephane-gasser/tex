#include "printsubsidiarydata.h"
#include "println.h"
#include "print.h"
#include "printfamandchar.h"
#include "showinfo.h"
#include "printcurrentstring.h"

void printsubsidiarydata(halfword p, ASCIIcode c)
{
	if (poolptr-strstart[strptr] >= depththreshold)
	{
		if (mem[p].hh.rh)
			print(314);// []
	}
	else
	{
		strpool[poolptr++] = c;
		tempptr = p;
		switch (mem[p].hh.rh)
		{
			case 1:
				println();
				printcurrentstring();
				printfamandchar(p);
				break;
			case 2: 
				showinfo();
				break;
			case 3: 
				if (mem[p].hh.lh == 0)
				{
					println();
					printcurrentstring();
					print(859); //{}
				}
				else
					showinfo();
		}
		poolptr--;
	}
}

