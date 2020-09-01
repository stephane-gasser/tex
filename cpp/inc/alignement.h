#ifndef ALIGNEMENT_H
#define ALIGNEMENT_H

#include "globals.h"

class SpanNode : public LinkedNode
{
	public:
		halfword Link;
		SpanNode *info;
		scaled width;
		SpanNode(void) {}
		~SpanNode(void) { if (info) delete info; }
};

inline SpanNode * const end_span = dynamic_cast<SpanNode*>(&heads[9]); //!< tail of spanned-width lists

class AlignRecordNode : public LinkedNode
{
	public:
		SpanNode *info;
		halfword extra_info;
		LinkedNode *u_part;
		LinkedNode *v_part;
		scaled width;
		GlueSpec *glue_ptr; //!< pointer to a glue specification
};

inline AlignRecordNode *curalign = nullptr;

void alignpeek(AlignRecordNode*&);
void doendv(Token, AlignRecordNode*&);
void initalign(Token, AlignRecordNode*&);

#endif
