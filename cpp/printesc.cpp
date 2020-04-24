#include "printesc.h"
#include "print.h"
#include "slowprint.h"

void printesc(strnumber s)
{
	auto &c = eqtb[5308].int_;
	if (c >= 0)
		if (c < 256)
			print(c);
	slowprint(s);
}
