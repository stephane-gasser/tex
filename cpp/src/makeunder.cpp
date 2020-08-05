#include "makeunder.h"
#include "noeud.h"
#include "boite.h"
#include "fractionrule.h"

void makeunder(halfword q)
{
	auto x = cleanbox(nucleus(q), curstyle);
	auto p = new KernNode(3*default_rule_thickness());
	x->link = p;
	p->link = fractionrule(default_rule_thickness());
	auto y = vpack(x, 0, additional);
	scaled delta = y->height+y->depth+default_rule_thickness();
	y->height = x->height;
	y->depth = delta-y->height;
	info(nucleus(q)) = y->num;
	math_type(nucleus(q)) = sub_box;
}
