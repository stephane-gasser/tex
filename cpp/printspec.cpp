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
		printscaled(width(p));
		if (s)
			print(s);
		if (stretch(p))
		{
			print(312); // plus 
			printglue(stretch(p), type(p), s);
		}
		if (shrink(p))
		{
			print(313); // minus 
			printglue(shrink(p), subtype(p), s);
		}
	}
}
