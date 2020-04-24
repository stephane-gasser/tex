#include "println.h"
#include <iostream>

void println(void)
{
	switch (selector)
	{
		case 19:
			std::cout << "\n";
			logfile << "\n";
			termoffset = 0;
			fileoffset = 0;
			break;
		case 18:
			logfile << "\n";
			fileoffset = 0;
			break;
		case 17:
			std::cout << "\n";
			termoffset = 0;
			break;
		case 16:
		case 20:
		case 21: 
			break;
		default: 
			writefile[selector] << "\n";
	}
}
