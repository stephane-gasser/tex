#include "deleteglueref.h"
#include "noeud.h"

[[deprecated]] void deleteglueref(halfword p)
{
	if (glue_ref_count(p) == 0)
		freenode(p, glue_spec_size);
	else
		link(p)--;
}

void deleteglueref(GlueSpec *p)
{
	if (p->glue_ref_count == 0)
		delete p;
	else
		p->glue_ref_count--;
}
