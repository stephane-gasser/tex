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
		loc = First;
		while (loc < last && buffer[loc] == ' ')
			loc++;
		if (loc < last)
			return true;
		std::cout << "Please type the name of your input file.\n";
	}
}
