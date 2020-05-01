#include "printchar.h"
#include "println.h"
#include <iostream>

void printchar(ASCIIcode s)
{
	if (s == int_par(new_line_char_code))
		if (selector < 20)
		{
			println();
			return;
		}
	switch (selector)
	{
		case 19:
			std::cout << xchr[s];
			logfile << xchr[s];
			termoffset++;
			fileoffset++;
			if (termoffset == maxprintline)
			{
				std::cout << "\n";
				termoffset = 0;
			}
			if (fileoffset == maxprintline)
			{
				logfile << "\n";
				fileoffset = 0;
			}
			break;
		case 18:
			logfile << xchr[s];
			fileoffset++;
			if (fileoffset = maxprintline)
			println();
			break;
		case 17:
			std::cout << xchr[s];
			termoffset++;
			if (termoffset == maxprintline)
				println();
			break;
		case 16:
			break;
		case 20: 
			if (tally < trickcount)
				trickbuf[tally%errorline] = s;
			break;
		case 21: 
			if (poolptr < poolsize)
			{
				strpool[poolptr] = s;
				poolptr++;
			}
			break;
		default: 
			writefile[selector] << xchr[s];
	}
	tally++;
}
