#include "printspec.h"
#include "printchar.h"
#include "print.h"
#include "printglue.h"
#include "printscaled.h"

void printspec(int p, strnumber s)
{
	if (p < memmin || p >= lomemmax)
		printchar('*');
	else
	{
		printscaled(mem[p+1].int_);
		if (s)
			print(s);
		if (mem[p+2].int_)
		{
			print(312); // plus 
			printglue(mem[p+2].int_, mem[p].hh.b0, s);
		}
		if (mem[p+3].int_)
		{
			print(313); // minus 
			printglue(mem[p+3].int_, mem[p].hh.b1, s);
		}
	}
}
