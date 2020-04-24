#include "printcurrentstring.h"
#include "printchar.h"

void printcurrentstring(void)
{
	auto j = strstart[strptr];
	while (j < poolptr)
		printchar(strpool[j++]);
}
