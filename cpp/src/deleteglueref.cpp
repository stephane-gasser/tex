#include "deleteglueref.h"
#include "noeud.h"

void deleteglueref(GlueSpec *p)
{
	if (p->glue_ref_count == 0)
		delete p;
	else
		p->glue_ref_count--;
}
