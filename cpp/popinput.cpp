#include "popinput.h"

void pop_input(void)
{  
	curinput = inputstack[--inputptr]; 
}
