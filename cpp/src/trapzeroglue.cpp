#include "trapzeroglue.h"
#include "noeud.h"
#include "deleteglueref.h"

GlueSpec *trapzeroglue(GlueSpec *g)
{
	if (g->width == 0 && g->stretch == 0 && g->shrink == 0)
	{
		zero_glue->glue_ref_count++;
		deleteglueref(g);
		return nullptr;
	}
	return g;
}
