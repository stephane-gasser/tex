#include "fractionrule.h"
#include "noeud.h"

halfword fractionrule(scaled t)
{
	auto p = newrule();
	height(p) = t;
	depth(p) = 0;
	return p;
}
