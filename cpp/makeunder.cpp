#include "makeunder.h"
#include "newkern.h"
#include "cleanbox.h"
#include "vpackage.h"
#include "fractionrule.h"

void makeunder(halfword q)
{
	auto x = cleanbox(nucleus(q), curstyle);
	auto p = newkern(3*default_rule_thickness());
	link(x) = p;
	link(p) = fractionrule(default_rule_thickness());
	auto y = vpackage(x, 0, 1, max_dimen);
	scaled delta = height(y)+depth(y)+default_rule_thickness();
	height(y) = height(x);
	depth(y) = delta-height(y);
	info(nucleus(q)) = y;
	math_type(nucleus(q)) = sub_box;
}
