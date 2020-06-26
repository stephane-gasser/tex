#include "clearforerrorprompt.h"
#include "impression.h"
#include "endfilereading.h"
#include <iostream>

void clearforerrorprompt(void)
{
	while (state != token_list && terminal_input(name) && inputptr > 0 && loc > limit)
		endfilereading();
	println();
	std::cin.clear();
}
