#include "fractionrule.h"
#include "newrule.h"

halfword fractionrule(scaled t)
{
	auto p = newrule();
	mem[p+3].int_ = t;
	mem[p+2].int_ = 0;
	return p;
}
