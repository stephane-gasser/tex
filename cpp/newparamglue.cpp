#include "newparamglue.h"
#include "getnode.h"

halfword newparamglue(smallnumber n)
{
	auto p = getnode(2);
	type(p) = glue_node;
	subtype(p) = n+1;
	link(p+1) = 0;
	auto q = glue_par(n);
	info(p+1) = q;
	link(q)++;
	return p;
}
