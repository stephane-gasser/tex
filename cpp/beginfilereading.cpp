#include "beginfilereading.h"
#include "overflow.h"

void beginfilereading(void)
{
	if (inopen == maxinopen)
		overflow("text input levels", maxinopen); 
	if (First == bufsize)
		overflow("buffer size", bufsize);
	inopen++;
	if (inputptr > maxinstack)
	{
		maxinstack = inputptr;
		if (inputptr == stacksize)
		overflow("input stack size", stacksize);
	}
	inputstack[inputptr] = curinput;
	inputptr++;
	curinput.indexfield = inopen;
	linestack[curinput.indexfield] = line;
	curinput.startfield = First;
	curinput.statefield = 1;
	curinput.namefield = 0;
}
