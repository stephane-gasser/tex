#include "packbufferedname.h"

void packbufferedname(smallnumber n, int a, int b)
{
	if (n+b-a+5 > filenamesize)
		b = a+filenamesize-n-5;
	int k = 0;
	for (int j = 1; j <= n; j++)
	{
		c = xord[TEXformatdefault[j]];
		k++;
		if (k <= filenamesize)
			nameoffile[k] = xchr[c];
	}
	for (int j = a; j <= b; j++)
	{
		c = buffer[j];
		k++;
		if (k <= filenamesize)
			nameoffile[k] = xchr[c];
	}
	for (int j = 17; j < 21; j++)
	{
		c = xord[TEXformatdefault[j]];
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
