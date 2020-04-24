#include "clearforerrorprompt.h"
#include "println.h"
#include "endfilereading.h"
#include <iostream>

void clearforerrorprompt(void)
{
	while (curinput.statefield && curinput.namefield == 0 && inputptr > 0 && curinput.locfield > curinput.limitfield)
		endfilereading();
	println();
	std::cin.clear();
}
