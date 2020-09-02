#include "initterminal.h"
#include "inputln.h"
#include <iostream>

void initterminal(void)
{
	while (true)
	{
		std::cout << "**" << std::flush;
		std::cin.clear();
		if (!inputln(std::cin, false))
		{
			std::cout << std::endl;
			std::cout << "! End of file on the terminal... why?'";
			throw std::string();
		}
		loc = First;
		while (loc < last && buffer[loc] == ' ')
			loc++;
		if (loc < last)
			return;
		std::cout << "Please type the name of your input file.\n";
	}
}
