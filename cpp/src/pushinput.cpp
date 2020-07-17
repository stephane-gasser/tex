#include "pushinput.h"
#include "erreur.h"

//! //enter a new input level, save the old
void push_input(void)
{
	if (inputptr > maxinstack)
	{
		maxinstack = inputptr;
		if (inputptr == stacksize)
		overflow("input stack size", stacksize, curalign);
	}
	inputstack[inputptr++] = curinput;
}
