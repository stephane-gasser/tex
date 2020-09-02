#include "pushinput.h"
#include "erreur.h"

//! //enter a new input level, save the old
void push_input(void)
{
	if (inputstack.size()-1 == stacksize)
		overflow("input stack size", stacksize);
	inputstack.push_back(curinput);
}
