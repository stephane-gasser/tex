#include "openfmtfile.h"
#include "wopenin.h"
#include "packbufferedname.h"
#include <iostream>

bool openfmtfile(void)
{
	auto j = loc;
	if (buffer[loc] == '&')
	{
		loc++;
		j = loc;
		buffer[last] = ' ';
		while (buffer[j] != ' ')
			j++;
		packbufferedname(0, loc, j-1);
		if (wopenin(fmtfile))
		{
			loc = j;
			return true;
		}
		packbufferedname(format_area_length, loc, j-1);
		if (wopenin(fmtfile))
		{
			loc = j;
			return true;
		}
		std::cout << "Sorry, I can't find that format;\n will try PLAIN.\n" << std::flush;
	}
	packbufferedname(format_default_length-format_ext_length, 1, 0);
	if (!wopenin(fmtfile))
	{
		std::cout << "I can't find the PLAIN format file!\n";
		return false;
	}
	loc = j;
	return true;
}
