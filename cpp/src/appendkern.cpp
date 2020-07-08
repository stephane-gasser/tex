#include "appendkern.h"
#include "lecture.h"
#include "noeud.h"

void appendkern(void)
{
	auto s = curchr;
	tail_append(newkern(scandimen(s == mu_glue, false, false)));
	subtype(tail) = s;
}
