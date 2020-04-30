#include "openfmtfile.h"
#include "wopenin.h"
#include "packbufferedname.h"
#include <iostream>

bool openfmtfile(void)
{
	auto j = curinput.locfield;
	if (buffer[curinput.locfield] == '&')
	{
		curinput.locfield++;
		j = curinput.locfield;
		buffer[last] = ' ';
		while (buffer[j] != ' ')
			j++;
		packbufferedname(0, curinput.locfield, j-1);
		if (wopenin(fmtfile))
		{
			curinput.locfield = j;
			return true;
		}
		packbufferedname(11, curinput.locfield, j-1);
		if (wopenin(fmtfile))
		{
			curinput.locfield = j;
			return true;
		}
		std::cout << "Sorry, I can't find that format;\n will try PLAIN.\n" << std::flush;
	}
	packbufferedname(16, 1, 0);
	if (!wopenin(fmtfile))
	{
		std::cout << "I can't find the PLAIN format file!\n";
		return false;
	}
	curinput.locfield = j;
	return true;
}
