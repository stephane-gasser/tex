#include "printnl.h"
#include "println.h"
#include "print.h"

void printnl(const std::string &s)
{
	if ((termoffset > 0 && selector%2 == 1) || (fileoffset > 0 && selector >= log_only))
		println();
	print(s);
}
