#include "newchoice.h"
#include "getnode.h"

halfword newchoice(void)
{
	auto p = getnode(style_node_size);
	type(p) = choice_node;
	subtype(p) = 0;
	display_mlist(p) = 0;
	text_mlist(p) = 0;
	script_mlist(p) = 0;
	script_script_mlist(p) = 0;
	return p;
}
