#include "overbar.h"
#include "noeud.h"
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
	return vpack(p, 0, additional);
}
