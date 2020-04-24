#include "printromanint.h"
#include "printchar.h"

void printromanint(int n)
{
	int j = strstart[260];
	int v = 1000;
	while (true)
	{
		while (n >= v)
		{
			printchar(strpool[j]);
			n -= v;
		}
		if (n <= 0)
			return;
		int k = j + 2;
		int u = v/(strpool[k-1]-'0');
		if (strpool[k-1] == '2')
		{
			k += 2;
			u /= strpool[k-1]-'0';
		}
		if (n + u >= v)
		{
			printchar(strpool[k]);
			n += u;
		}
		else
		{
			j += 2;
			v /= strpool[j-1]-'0';
		}
	}
}
