#include "makeover.h"
#include "cleanbox.h"
#include "overbar.h"

void makeover(halfword q)
{
	info(nucleus(q)) = overbar(cleanbox(nucleus(q), cramped_style(curstyle))->num, 3*default_rule_thickness(), default_rule_thickness());
	math_type(nucleus(q)) = sub_box;
}
