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
	auto G = new GlueNode(dynamic_cast<GlueNode*>(preamble)->glue_ptr);
	G->subtype = tab_skip_code+1;
	tail_append(G);
	curalign = dynamic_cast<AlignRecordNode*>(preamble->link);
	curtail = curhead;
	initspan(dynamic_cast<SpanNode*>(curalign));
}
