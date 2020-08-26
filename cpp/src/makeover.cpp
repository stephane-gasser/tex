#include "makeover.h"
#include "boite.h"
#include "overbar.h"

void makeover(halfword q)
{
	Noad *Q;
	Q->num = q;
	Q->nucleus.math_type = sub_box;
	Q->nucleus.info = overbar(cleanbox(nucleus(q), cramped_style(curstyle))->num, 3*default_rule_thickness(), default_rule_thickness());
}
