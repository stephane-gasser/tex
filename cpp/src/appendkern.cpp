#include "appendkern.h"
#include "scandimen.h"
#include "newkern.h"

void appendkern(void)
{
	auto s = curchr;
	scandimen(s == 99, false, false);
	tail_append(newkern(curval));
	subtype(tail) = s;
}
