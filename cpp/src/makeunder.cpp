#include "makeunder.h"
#include "noeud.h"
#include "cleanbox.h"
#include "vpackage.h"
#include "fractionrule.h"

void makeunder(halfword q)
{
	auto x = cleanbox(nucleus(q), curstyle);
	auto p = new KernNode(3*default_rule_thickness());
	x->link = p;
	p->link = fractionrule(default_rule_thickness());
	auto y = vpack(x->num, 0, additional);
	scaled delta = height(y)+depth(y)+default_rule_thickness();
	height(y) = x->height;
	depth(y) = delta-height(y);
	info(nucleus(q)) = y;
	math_type(nucleus(q)) = sub_box;
}
