#include "equivalent.h"
#include "sauvegarde.h"
#include "lecture.h"
#include "deleteglueref.h"
#include "noeud.h"

void MemoryNode::eqdestroy(void)
{
	switch (type)
	{
		case call:
		case long_call:
		case outer_call:
		case long_outer_call: 
			dynamic_cast<TokenList*>(index)->deleteTokenRef();
			break;
		case glue_ref:
			deleteglueref(dynamic_cast<GlueSpec*>(index));
			break;
		case shape_ref:
			if (index)
				delete index;
			break;
		case box_ref: 
			flushnodelist(dynamic_cast<BoxNode*>(index));
	} 
}
void MemoryNode::define(int prefix, quarterword t, AnyNode *e) 
{
	if (prefix >= globalPrefix || level == curlevel)
		eqdestroy();
	else 
		if (curlevel > level_one)
			eqsave(level);
	level = prefix >= globalPrefix ? level_one : curlevel;
	type = t;
	index = e;
}

void MemoryNode::define(int prefix, quarterword t, halfword e) 
{
	if (prefix >= globalPrefix || level == curlevel)
		eqdestroy();
	else 
		if (curlevel > level_one)
			eqsave(level);
	level = prefix >= globalPrefix ? level_one : curlevel;
	type = t;
	int_ = e;
}

void MemoryNode::word_define(int prefix, int w)
{
	if (prefix >= globalPrefix)
		level = level_one;
	else
		if (level != curlevel)
		{
			eqsave(level);
			level = curlevel;
		}
	int_ = w;
}

