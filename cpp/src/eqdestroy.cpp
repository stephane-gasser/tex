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
	halfword q = equiv_field(w);
	AnyNode *Q;
	Q->num = q;
	switch (w.hh.b0)
	{
		case call:
		case long_call:
		case outer_call:
		case long_outer_call: 
			deletetokenref(dynamic_cast<TokenNode*>(Q));
			break;
		case glue_ref:
			deleteglueref(dynamic_cast<GlueSpec*>(Q));
			break;
		case shape_ref:
			if (Q)
				freenode(q, 2*info(q)+1);
			break;
		case box_ref: 
			flushnodelist(dynamic_cast<BoxNode*>(Q));
	}
}
