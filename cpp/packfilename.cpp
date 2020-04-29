#include "packfilename.h"

void packfilename(strnumber n, strnumber a, strnumber e)
{
	int k = 0;
	for (auto j = strstart[a]; j < strstart[a+1]; j++)
	{
		auto c = strpool[j];
		k++;
		if (k <= filenamesize)
			nameoffile[k] = xchr[c];
	}
	for (auto j = strstart[n]; j <strstart[n+1]; j++)
	{
		auto c = strpool[j];
		k++;
		if (k <= filenamesize)
			nameoffile[k] = xchr[c];
	}
	for (auto j = strstart[e]; j < strstart[e+1]; j++)
	{
		auto c = strpool[j];
		k++;
		if (k <= filenamesize)
			nameoffile[k] = xchr[c];
	}
	if (k <= filenamesize)
		namelength = k;
	else
		namelength = filenamesize;
	for (k = namelength+1; k <= filenamesize; k++)
		nameoffile[k] = ' ';
}
