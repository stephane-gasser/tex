#include "makeunder.h"
#include "noeud.h"
#include "cleanbox.h"
#include "vpackage.h"
#include "fractionrule.h"

void makeunder(halfword q)
{
	auto x = cleanbox(nucleus(q), curstyle);
	auto p = newkern(3*default_rule_thickness());
	link(x) = p;
	link(p) = fractionrule(default_rule_thickness());
	auto y = vpack(x, 0, additional);
	scaled delta = height(y)+depth(y)+default_rule_thickness();
	height(y) = height(x);
	depth(y) = delta-height(y);
	info(nucleus(q)) = y;
	math_type(nucleus(q)) = sub_box;
}
