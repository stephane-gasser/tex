#include "printtwo.h"
#include "printchar.h"

void printtwo(int n)
{
	n = abs(n)%100;
	printchar('0'+n/10);
	printchar('0'+n%10);
}
