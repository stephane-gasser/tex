#include "getxtoken.h"
#include "getnext.h"
#include "macrocall.h"
#include "expand.h"

void getxtoken(void)
{
	while (true)
	{
		getnext();
		if (curcmd <= 100)
			break;
		if (curcmd >= 111)
			if (curcmd < 115)
				macrocall();
			else
			{
				curcs = 2620;
				curcmd = 9;
				break;
			}
		else
		expand();
	}
	if (curcs == 0)
		curtok = (curcmd*256)+curchr;
	else
		curtok = 4095 + curcs;
}
