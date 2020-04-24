#include "printdelimiter.h"
#include "printint.h"
#include "printhex.h"

void printdelimiter(halfword p)
{
	int a = mem[p].qqqq.b0*256+mem[p].qqqq.b1;
	a = a*4096+mem[p].qqqq.b2*256+mem[p].qqqq.b3;
	if (a < 0)
		printint(a);
	else
		printhex(a);
}
