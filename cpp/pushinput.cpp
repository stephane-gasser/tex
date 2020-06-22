#include "pushinput.h"
#include "overflow.h"

void push_input(void)
{
	if (inputptr > maxinstack)
	{
		maxinstack = inputptr;
		if (inputptr == stacksize)
		overflow("input stack size", stacksize);
	}
	inputstack[inputptr++] = curinput;
}
