#include "printchar.h"
#include "println.h"
#include <iostream>

void printchar(ASCIIcode s)
{
	if (s == new_line_char())
		if (selector < pseudo)
		{
			println();
			return;
		}
	switch (selector)
	{
		case term_and_log:
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
		case log_only:
			logfile << xchr[s];
			fileoffset++;
			if (fileoffset == maxprintline)
			println();
			break;
		case term_only:
			std::cout << xchr[s];
			termoffset++;
			if (termoffset == maxprintline)
				println();
			break;
		case no_print:
			break;
		case pseudo: 
			if (tally < trickcount)
				trickbuf[tally%errorline] = s;
			break;
		case new_string: 
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
