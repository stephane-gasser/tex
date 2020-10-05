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
			dynamic_cast<TokenList*>(Q)->deleteTokenRef();
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
void define(int a, MemoryNode *p, quarterword t, AnyNode *e) 
{
	if (a >= 4 || p->level == curlevel)
		eqdestroy(p);
	else 
		if (curlevel > level_one)
			eqsave(p, p->level);
	p->level = a >= 4 ? level_one : curlevel;
	p->type = t;
	p->index = e;
}

void define(int a, MemoryNode *p, quarterword t, halfword e) 
{
	if (a >= 4 || p->level == curlevel)
		eqdestroy(p);
	else 
		if (curlevel > level_one)
			eqsave(p, p->level);
	p->level = a >= 4 ? level_one : curlevel;
	p->type = t;
	p->int_ = e;
}

void word_define(int a, MemoryNode *p, int w) 
{
	if (a >= 4)
		p->level = level_one;
	else
		if (p->level != curlevel)
		{
			eqsave(p, p->level);
			p->level = curlevel;
		}
	p->int_ = w;
}

