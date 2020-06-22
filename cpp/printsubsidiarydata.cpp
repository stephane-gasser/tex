#include "printsubsidiarydata.h"
#include "println.h"
#include "print.h"
#include "printfamandchar.h"
#include "showinfo.h"
#include "printcurrentstring.h"

void printsubsidiarydata(halfword p, ASCIIcode c)
{
	if (cur_length() >= depththreshold)
	{
		if (link(p))
			print(" []");
	}
	else
	{
		append_char(c);
		tempptr = p;
		switch (link(p))
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
				if (info(p) == 0)
				{
					println();
					printcurrentstring();
					print("{}");
				}
				else
					showinfo();
		}
		poolptr--;
	}
}

