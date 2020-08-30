#include "equivalent.h"
#include "sauvegarde.h"
#include "lecture.h"
#include "deleteglueref.h"
#include "noeud.h"

void eqdestroy(MemoryNode *w)
{
	auto Q = w->index;
	switch (w->type)
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
void define(int a, MemoryNode *p, quarterword t, halfword e) { (a >= 4 ? geqdefine : eqdefine)(p, t, e); }

void eqdefine(MemoryNode *p, quarterword t, halfword e)
{
	if (p->level == curlevel)
		eqdestroy(p);
	else 
		if (curlevel > 1)
			eqsave(p, p->level);
	p->level = curlevel;
	p->type = t;
	p->index->num = e;
}

void geqdefine(MemoryNode *p, quarterword t, halfword e)
{
	eqdestroy(p);
	p->level = 1;
	p->type = t;
	p->index->num = e;
}

void word_define(int a, MemoryNode *p, int w) { (a >= 4 ? geqworddefine : eqworddefine)(p, w); }

void eqworddefine(MemoryNode *p, int w)
{
	if (p->/*xeq*/level != curlevel)
	{
		eqsave(p, p->/*xeq*/level);
		p->/*xeq*/level = curlevel;
	}
	p->int_ = w;
}

void geqworddefine(MemoryNode *p, int w)
{
	p->int_ = w;
	p->/*xeq*/level = 1;
}

int& count(halfword p) { return eqtb_int[p+count_base-int_base].int_; }
int& dimen(halfword p) { return eqtb_dimen[p+scaled_base-dimen_base].int_; }
int& del_code(halfword p) { return eqtb_int[p+del_code_base-int_base].int_; }
int& cat_code(halfword p) { return eqtb_local[p+cat_code_base-local_base].int_; }
ShapeNode* par_shape_ptr(void) { return dynamic_cast<ShapeNode*>(eqtb_local[par_shape_loc-local_base].index); }
TokenNode* every_math(void) { return dynamic_cast<TokenNode*>(eqtb_local[every_math_loc-local_base].index); }
TokenNode* every_cr(void) { return dynamic_cast<TokenNode*>(eqtb_local[every_cr_loc-local_base].index); } //!< points to token list for \\everyvbox
TokenNode* every_vbox(void) { return dynamic_cast<TokenNode*>(eqtb_local[every_vbox_loc-local_base].index); } //!< points to token list for \\everyvbox
int& err_help(void) { return eqtb_local[err_help_loc-local_base].int_; }
int& lc_code(halfword p) { return eqtb_local[p+lc_code_base-local_base].int_; }
int& sf_code(halfword p) { return eqtb_local[p+sf_code_base-local_base].int_; }
int& math_code(halfword p) { return eqtb_local[p+math_code_base-local_base].int_; }
int& int_par(halfword p) { return eqtb_int[p].int_; }
GlueSpec* glue_par(halfword p) { return dynamic_cast<GlueSpec*>(eqtb_glue[p].index); }
int& dimen_par(halfword p) { return eqtb_dimen[p].int_; }

