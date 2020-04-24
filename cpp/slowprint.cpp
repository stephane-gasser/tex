#include "slowprint.h"
#include "print.h"

void slowprint(int s)
{
	if (s >= strptr || s < 256)
		print(s);
	else
		for (int j = strstart[s]; j < strstart[s+1]; j++)
			print(strpool[j]);
}
