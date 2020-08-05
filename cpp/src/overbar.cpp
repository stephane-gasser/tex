#include "overbar.h"
#include "noeud.h"
#include "fractionrule.h"
#include "boite.h"

BoxNode* overbar(halfword b, scaled k, scaled t)
{
	auto p = new KernNode(k);
	p->link->num = b;
	auto q = fractionrule(t);
	q->link = p;
	p = new KernNode(t);
	p->link = q;
	return vpack(p, 0, additional);
}
