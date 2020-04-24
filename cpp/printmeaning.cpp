#include "printmeaning.h"
#include "printcmdchr.h"
#include "printchar.h"
#include "println.h"
#include "tokenshow.h"

void printmeaning(void)
{
	printcmdchr(curcmd, curchr);
	if (curcmd >= 111)
	{
		printchar(':');
		println();
		tokenshow(curchr);
	}
	else 
		if (curcmd = 110)
		{
			printchar(':');
			println();
			tokenshow(curmark[curchr]);
		}
}
