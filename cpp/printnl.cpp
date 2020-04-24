#include "printnl.h"
#include "println.h"
#include "print.h"

void printnl(strnumber s)
{
	if ((termoffset > 0 && selector%2 == 1) || (fileoffset > 0 && selector >= 18))
		println();
	print(s);
}
