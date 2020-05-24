#include "inputln.h"
#include "overflow.h"
#include <iostream>

bool inputln(std::istream& f, bool bypasseoln)
{
	if (bypasseoln && !f.eof())
		f.get();
	last = First;
	if (f.eof())
		return false;
	std::string line;
	getline(f, line);
	int lastnonblank = First;
	for (char c: line)
	{
		if (last >= maxbufstack)
		{
			maxbufstack = last+1;
			if (maxbufstack == bufsize)
				if (formatident == 0)
				{
					std::cout << "Buffer size exceeded!\n";
					throw std::string();
				}
				else
				{
					curinput.locfield = First;
					curinput.limitfield = last-1;
					overflow("buffer size", bufsize); 
				}
		}
		buffer[last] = xord[c];
		last++;
		if (buffer[last-1] != ' ')
			lastnonblank = last;
	}
	last = lastnonblank;
	return true;
}
