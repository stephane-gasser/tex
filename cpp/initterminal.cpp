#include "initterminal.h"
#include "inputln.h"
#include <iostream>

bool initterminal(void)
{
	while (true)
	{
		std::cout << "**" << std::flush;
		std::cin.clear();
		if (!inputln(std::cin, false))
		{
			std::cout << std::endl;
			std::cout << "! End of file on the terminal... why?'";
			return false;
		}
		curinput.locfield = First;
		while (curinput.locfield < last && buffer[curinput.locfield] == ' ')
			curinput.locfield++;
		if (curinput.locfield < last)
			return true;
		std::cout << "Please type the name of your input file.\n";
	}
}
