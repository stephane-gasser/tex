#include "newnullbox.h"
#include "getnode.h"

halfword newnullbox(void)
{
	halfword p = getnode(7);
	type(p) = hlist_node;
	subtype(p) = 0;
	width(p) = 0;
	depth(p) = 0;
	height(p) = 0;
	shift_amount(p) = 0;
	list_ptr(p) = 0;
	glue_sign(p) = normal;
	glue_order(p) = 0;
	glue_set(p) = 0.0;
	return p;
}
