#include "overbar.h"
#include "newkern.h"
#include "fractionrule.h"
#include "vpackage.h"

halfword overbar(halfword b, scaled k, scaled  t)
{
	auto p = newkern(k);
	link(p) = b;
	auto q = fractionrule(t);
	link(q) = p;
	p = newkern(t);
	link(p) = q;
	return vpackage(p, 0, 1, max_dimen);
}
