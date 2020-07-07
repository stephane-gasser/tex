#include "appendkern.h"
#include "lecture.h"
#include "newkern.h"

void appendkern(void)
{
	auto s = curchr;
	curval = scandimen(s == mu_glue, false, false);
	tail_append(newkern(curval));
	subtype(tail) = s;
}
