#include "initrow.h"
#include "pushnest.h"
#include "initspan.h"
#include "noeud.h"

void initrow(void)
{
	pushnest();
	mode = -103-mode;
	if (mode == -hmode)
		space_factor = 0;
	else
		prev_depth = 0;
	tail_append(newglue(info(link(align_head)+1)));
	subtype(tail) = 12;
	curalign = link(link(align_head));
	curtail = curhead;
	initspan(curalign);
}
