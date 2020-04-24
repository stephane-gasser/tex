#include "beginfilereading.h"
#include "overflow.h"

void beginfilereading(void)
{
	if (inopen == maxinopen)
		overflow(596, maxinopen); //text input levels
	if (First == bufsize)
		overflow(256, bufsize); //buffer size
	inopen++;
	if (inputptr > maxinstack)
	{
		maxinstack = inputptr;
		if (inputptr == stacksize)
		overflow(593, stacksize); //input stack size
	}
	inputstack[inputptr] = curinput;
	inputptr++;
	curinput.indexfield = inopen;
	linestack[curinput.indexfield] = line;
	curinput.startfield = First;
	curinput.statefield = 1;
	curinput.namefield = 0;
}
