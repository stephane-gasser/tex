#include "popinput.h"

//! leave an input level, re-enter the old
void pop_input(void)
{  
	inputstack.pop_back();
	curinput = inputstack.back(); 
}
