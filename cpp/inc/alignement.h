#ifndef ALIGNEMENT_H
#define ALIGNEMENT_H

#include "globals.h"
#include "noeud.h"

class SpanNode : public LinkedNode
{
	public:
		halfword nb; // Link
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
		TokenNode *u_part;
		TokenNode *v_part;
		scaled width;
		GlueSpec *glue_ptr; //!< pointer to a glue specification
};

inline AlignRecordNode *curalign = nullptr;
inline scaled totalstretch[4], totalshrink[4];
inline int packbeginline = 0;
inline int alignstate = 1000000;

void alignpeek(AlignRecordNode*&);
void doendv(Token, AlignRecordNode*&);
void initalign(Token, AlignRecordNode*&);

#endif
