#include "inputln.h"
#include "overflow.h"
#include <iostream>

bool inputln(alphafile& f, bool bypasseoln)
{
	if (bypasseoln)
		if (!f.eof())
			f.get();
	last = First;
	if (f.eof())
		return false;
	int lastnonblank = First;
	while (f.peek() != '\n')
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
					overflow(256, bufsize); //buffer size
				}
		}
		buffer[last] = xord[f.get()];
		last++;
		if (buffer[last-1] != ' ')
			lastnonblank = last;
	}
	last = lastnonblank;
	return true;
}
