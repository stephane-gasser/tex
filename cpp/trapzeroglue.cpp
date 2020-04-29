#include "trapzeroglue.h"
#include "deleteglueref.h"

void trapzeroglue(void)
{
	if (mem[curval+1].int_ == 0 && mem[curval+2].int_ == 0 && mem[curval+3].int_ == 0)
	{
		link(0)++;
		deleteglueref(curval);
		curval = 0;
	}
}
