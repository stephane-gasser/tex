#include "backinput.h"
#include "endtokenlist.h"
#include "getavail.h"
#include "overflow.h"

void backinput(void)
{
	while (curinput.statefield == 0 && curinput.locfield == 0 && curinput.indexfield != 2)
		endtokenlist();
	auto p = getavail();
	mem[p].hh.lh = curtok;
	if (curtok < 768)
		if (curtok < 512)
			alignstate--;
		else
			alignstate++;
	if (inputptr > maxinstack)
	{
		maxinstack = inputptr;
		if (inputptr == stacksize)
			overflow(593, stacksize); // input stack size
	}
	inputstack[inputptr++] = curinput;
	curinput.statefield = 0;
	curinput.startfield = p;
	curinput.indexfield = 3;
	curinput.locfield = p;
}
