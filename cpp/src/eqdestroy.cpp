#include "eqdestroy.h"
#include "lecture.h"
#include "deleteglueref.h"
#include "noeud.h"

static halfword equiv_field(memoryword w)
{
	return w.hh.rh;
}

static quarterword eq_type_field(memoryword w)
{
	return w.hh.b0;
}

void eqdestroy(memoryword w)
{
	halfword q;
	switch (w.hh.b0)
	{
		case call:
		case long_call:
		case outer_call:
		case long_outer_call: 
			deletetokenref(equiv_field(w));
			break;
		case glue_ref: 
			deleteglueref(equiv_field(w));
			break;
		case shape_ref:
			q = equiv_field(w);
			if (q)
				freenode(q, 2*info(q)+1);
			break;
		case box_ref: 
			flushnodelist(equiv_field(w));
	}
}
