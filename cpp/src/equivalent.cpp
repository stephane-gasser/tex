#include "equivalent.h"
#include "sauvegarde.h"
#include "lecture.h"
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

void MemoryNode::defineCommon(int prefix, quarterword t) 
{
	if (prefix >= globalPrefix || level == curlevel)
		eqdestroy();
	else 
		if (curlevel > level_one)
			eqsave(level);
	level = prefix >= globalPrefix ? level_one : curlevel;
	type = t;
}

void MemoryNode::define(int prefix, quarterword t, AnyNode *e) 
{
	defineCommon(prefix, t);
	index = e;
}

void MemoryNode::define(int prefix, quarterword t, halfword e) 
{
	defineCommon(prefix, t);
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

template<int loc, int text> void every(void)
{
	if (auto e = dynamic_cast<TokenList*>(eqtb_local[loc-local_base].index); e)
		e->beginAboveMacro(text);
}

void everyPar(void) { every<every_par_loc, every_par_text>(); } //!< points to token list for \\everypar
void everyCr(void) { every<every_cr_loc, every_cr_text>(); } //!< points to token list for \\everyvbox
void everyMath(void) { every<every_math_loc, every_math_text>(); }
void everyDisplay(void) { every<every_display_loc, every_display_text>(); }
void everyHBox(void) { every<every_hbox_loc, every_hbox_text>(); }
void everyVBox(void) { every<every_vbox_loc, every_vbox_text>(); }
void everyJob(void) { every<every_job_loc, every_job_text>(); }
void outputRoutine(void) { output_routine()->beginAboveMacro(output_text); }
void writeRoutine(TokenList *tl) { tl->beginAboveMacro(write_text); }

void markRoutine(int i)
{
	if (curmark[i])
		curmark[i]->beginAboveMacro(mark_text);
}

