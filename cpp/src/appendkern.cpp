#include "appendkern.h"
#include "scandimen.h"
#include "newkern.h"

void appendkern(void)
{
	auto s = curchr;
	scandimen(s == mu_glue, false, false);
	tail_append(newkern(curval));
	subtype(tail) = s;
}
