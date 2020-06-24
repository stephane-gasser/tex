#include "slowprint.h"
#include "printchar.h"


void slowprint(int s)
{
	if (s >= strptr || s < 256)
		printchar(s);
	else
		for (int j = strstart[s]; j < strstart[s+1]; j++)
			printchar(strpool[j]);
}

void slowprint(const std::string &s)
{
	for (auto c: s)
		printchar(c);
}
