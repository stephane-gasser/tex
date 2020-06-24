#include "beginfilereading.h"
#include "overflow.h"
#include "pushinput.h"

void beginfilereading(void)
{
	if (inopen == maxinopen)
		overflow("text input levels", maxinopen); 
	if (First == bufsize)
		overflow("buffer size", bufsize);
	inopen++;
	push_input();
	index = inopen;
	linestack[index] = line;
	start = First;
	state = mid_line;
	name = "";
}
