#include "terminput.h"
#include "inputln.h"
#include "impression.h"
#include "fatalerror.h"
#include <iostream>

void terminput(void)
{
	std::cout << std::flush;
	if (!inputln(std::cin, true))
		fatalerror("End of file on the terminal!");
	termoffset = 0;
	selector--;
	if (last != First)
		for (int k = First; k < last; k++)
			printchar(buffer[k]);
	println();
	selector++;
}
