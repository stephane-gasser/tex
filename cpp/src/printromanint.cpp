#include "printromanint.h"
#include "printchar.h"

void printromanint(int n)
{
	static const std::string s = "m2d5c2l5x2v5i";
	int j = 0;
	int v = 1000;
	while (true)
	{
		while (n >= v)
		{
			printchar(s[j]);
			n -= v;
		}
		if (n <= 0)
			return;
		int k = j+2;
		int u = v/(s[j+1]-'0');
		if (s[j+1] == '2')
		{
			k += 2;
			u /= s[j+3]-'0';
		}
		if (n+u >= v)
		{
			printchar(s[k]);
			n += u;
		}
		else
		{
			j += 2;
			v /= s[j-1]-'0';
		}
	}
}
