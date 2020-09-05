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
void define_(int a, MemoryNode *p, quarterword t, AnyNode *e) { (a >= 4 ? geqdefine_ : eqdefine_)(p, t, e); }

void eqdefine_(MemoryNode *p, quarterword t, AnyNode *e)
{
	if (p->level == curlevel)
		eqdestroy(p);
	else 
		if (curlevel > level_one)
			eqsave(p, p->level);
	p->level = curlevel;
	p->type = t;
	p->index = e;
}

void geqdefine_(MemoryNode *p, quarterword t, AnyNode *e)
{
	eqdestroy(p);
	p->level = level_one;
	p->type = t;
	p->index = e;
}

void eqdefine(MemoryNode *p, quarterword t, halfword e)
{
	if (p->level == curlevel)
		eqdestroy(p);
	else 
		if (curlevel > level_one)
			eqsave(p, p->level);
	p->level = curlevel;
	p->type = t;
	p->int_ = e;
}

void geqdefine(MemoryNode *p, quarterword t, halfword e)
{
	eqdestroy(p);
	p->level = level_one;
	p->type = t;
	p->int_ = e;
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
	p->/*xeq*/level = level_one;
}

