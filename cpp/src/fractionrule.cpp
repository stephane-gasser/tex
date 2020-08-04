#include "fractionrule.h"
#include "noeud.h"

RuleNode *fractionrule(scaled t)
{
	auto p = new RuleNode;
	p->height = t;
	p->depth = 0;
	return p;
}
