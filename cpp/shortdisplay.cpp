#include "shortdisplay.h"
#include "printchar.h"
#include "print.h"
#include "printesc.h"
#include "texte.h"

void shortdisplay(int p)
{
	while (p > memmin)
	{
		if (p >= himemmin)
		{
			if (p <= memend)
			{
				if (type(p) != fontinshortdisplay)
				{
					if (type(p) < 0 || type(p) > fontmax)
						printchar('*');
					else
						printesc(TXT(text(frozen_null_font+type(p))));
						
					printchar(' ');
					fontinshortdisplay = type(p);
				}
				print(std::string(1, subtype(p)));
			}
		}
		else
		switch (type(p))
		{
			case 0:
			case 1:
			case 3:
			case 8:
			case 4:
			case 5:
			case 13: 
				print("[]");
				break;
			case 2: 
				printchar('|');
				break;
			case 10: 
				if (info(p+1))
					printchar(' ');
				break;
			case 9:
				printchar('$');
				break;
			case 6:
				shortdisplay(link(p+1));
				break;
			case 7:
				shortdisplay(info(p+1));
				shortdisplay(link(p+1));
				for (int n = subtype(p); n > 0; n--)
					if (link(p))
						p = link(p);
		}
		p = link(p);
	}
}
