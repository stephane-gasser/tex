#include "equivalent.h"
#include "sauvegarde.h"
#include "lecture.h"
#include "deleteglueref.h"
#include "noeud.h"

static quarterword eq_type_field(memoryword w) { return w.hh.b0; }
static halfword equiv_field(memoryword w) { return w.hh.rh; }

void eqdestroy(memoryword w)
{
	halfword q = equiv_field(w);
	AnyNode *Q;
	Q->num = q;
	switch (eq_type_field(w))
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
				delete Q;
			break;
		case box_ref: 
			flushnodelist(dynamic_cast<BoxNode*>(Q));
	}
}
void define(int a, halfword p, quarterword t, halfword e) { (a >= 4 ? geqdefine : eqdefine)(p, t, e); }
void word_define(int a, halfword p, int w) { (a >= 4 ? geqworddefine : eqworddefine)(p, w); }

void eqdefine(halfword p, quarterword t, halfword e)
{
	if (eq_level(p) == curlevel)
		eqdestroy(eqtb[p]);
	else 
		if (curlevel > 1)
			eqsave(p, eq_level(p));
	eq_level(p) = curlevel;
	eq_type(p) = t;
	equiv(p) = e;
}

void geqdefine(halfword p, quarterword t, halfword e)
{
	eqdestroy(eqtb[p]);
	subtype(p) = 1;
	type(p) = t;
	equiv(p) = e;
}

void eqworddefine(halfword p, int w)
{
	if (xeqlevel[p] != curlevel)
	{
		eqsave(p, xeqlevel[p]);
		xeqlevel[p] = curlevel;
	}
	eqtb[p].int_ = w;
}

void geqworddefine(halfword p, int w)
{
	eqtb[p].int_ = w;
	xeqlevel[p] = 1;
}
