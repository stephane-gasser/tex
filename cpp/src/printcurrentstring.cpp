#include "printcurrentstring.h"
#include "printchar.h"

void printcurrentstring(void)
{
	for (auto j = strstart[strptr]; j < poolptr; j++)
		printchar(strpool[j]);
}
