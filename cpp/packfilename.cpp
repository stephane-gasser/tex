#include "packfilename.h"

void packfilename(const std::string &n, const std::string &a, const std::string &e)
{
	int k = 0;
	for (auto c: a)
	{
		k++;
		if (k <= filenamesize)
			nameoffile[k] = xchr[c];
	}
	for (auto c: n)
	{
		k++;
		if (k <= filenamesize)
			nameoffile[k] = xchr[c];
	}
	for (auto c: e)
	{
		k++;
		if (k <= filenamesize)
			nameoffile[k] = xchr[c];
	}
	namelength = std::min(k, filenamesize);
	for (k = namelength+1; k <= filenamesize; k++)
		nameoffile[k] = ' ';
}
