#include "deleteglueref.h"
#include "freenode.h"

void deleteglueref(halfword p)
{
	if (glue_ref_count(p) == 0)
		freenode(p, glue_spec_size);
	else
		link(p)--;
}
