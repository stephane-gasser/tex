#include "printdelimiter.h"
#include "printint.h"
#include "printhex.h"

void printdelimiter(halfword p)
{
	int a = mem[p].qqqq.b0*0x1'00+mem[p].qqqq.b1;
	a = a*0x10'00+mem[p].qqqq.b2*0x1'00+mem[p].qqqq.b3;
	if (a < 0)
		printint(a);
	else
		printhex(a);
}
