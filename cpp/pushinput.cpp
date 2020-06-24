#include "pushinput.h"
#include "overflow.h"

//! //enter a new input level, save the old
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
