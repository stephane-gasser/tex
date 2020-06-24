#include "newstyle.h"
#include "getnode.h"

halfword newstyle(smallnumber s)
{
	auto p = getnode(style_node_size);
	type(p) = style_node;
	subtype(p) = s;
	width(p) = 0;
	depth(p) = 0;
	return p;
}
