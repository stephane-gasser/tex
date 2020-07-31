#include "overbar.h"
#include "noeud.h"
#include "fractionrule.h"
#include "vpackage.h"

halfword overbar(halfword b, scaled k, scaled  t)
{
	auto p = new KernNode(k);
	p->link->num = b;
	auto q = fractionrule(t);
	link(q) = p->num;
	p = new KernNode(t);
	p->link->num = q;
	return vpack(p->num, 0, additional);
}
