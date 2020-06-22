#include "packbufferedname.h"

void packbufferedname(smallnumber n, int a, int b)
{
	if (n+b-a+1+format_ext_length > filenamesize)
		b = a+filenamesize-n-1-format_ext_length;
	int k = 0;
	for (int j = 1; j <= n; j++)
		append_to_name(k,xord[TEXformatdefault[j]]);
	for (int j = a; j <= b; j++)
		append_to_name(k, buffer[j]);
	for (int j = format_default_length-format_ext_length+1; j <= format_default_length; j++)
		append_to_name(k, xord[TEXformatdefault[j]]);
	namelength = std::min(k, filenamesize);
	for (k = namelength+1; k <= filenamesize; k++)
		nameoffile[k] = ' ';
}
