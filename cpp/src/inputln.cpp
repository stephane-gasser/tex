#include "inputln.h"
#include "erreur.h"
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
				if (formatident == "")
				{
					std::cout << "Buffer size exceeded!\n";
					throw std::string();
				}
				else
				{
					loc = First;
					limit = last-1;
					overflow("buffer size", bufsize, curalign); 
				}
		}
		buffer[last++] = xord[c];
		if (buffer[last-1] != ' ')
			lastnonblank = last;
	}
	last = lastnonblank;
	return true;
}
