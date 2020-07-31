#include "initrow.h"
#include "pushnest.h"
#include "initspan.h"
#include "noeud.h"

void initrow(void)
{
	pushnest();
	mode = (-hmode-vmode)-mode;
	if (mode == -hmode)
		space_factor = 0;
	else
		prev_depth = 0;
	tail_append(newglue(glue_ptr(preamble())));
	subtype(tail->num) = tab_skip_code+1;
	curalign = link(preamble());
	curtail = curhead;
	initspan(curalign);
}
