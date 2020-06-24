#include "printmeaning.h"
#include "printcmdchr.h"
#include "printchar.h"
#include "println.h"
#include "tokenshow.h"

void printmeaning(void)
{
	printcmdchr(curcmd, curchr);
	if (curcmd >= call)
	{
		printchar(':');
		println();
		tokenshow(curchr);
	}
	else 
		if (curcmd == top_bot_mark)
		{
			printchar(':');
			println();
			tokenshow(curmark[curchr]);
		}
}
