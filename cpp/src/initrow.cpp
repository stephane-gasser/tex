#include "initrow.h"
#include "pushnest.h"
#include "initspan.h"
#include "noeud.h"

void initrow(halfword &span, halfword &align)
{
	pushnest();
	mode = -(hmode+vmode+mode);
	if (mode == -hmode)
		space_factor = 0;
	else
		prev_depth = 0;
	tail_append(newglue(glue_ptr(preamble())));
	subtype(tail) = tab_skip_code+1;
	align = link(link(align_head));
	curtail = curhead;
	initspan(align, span);
}
