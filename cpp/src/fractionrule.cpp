#include "fractionrule.h"
#include "newrule.h"

halfword fractionrule(scaled t)
{
	auto p = newrule();
	height(p) = t;
	depth(p) = 0;
	return p;
}
