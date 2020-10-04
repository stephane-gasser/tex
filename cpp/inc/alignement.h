#ifndef ALIGNEMENT_H
#define ALIGNEMENT_H

#include "globals.h"
#include "token.h"
#include "noeud.h"

class SpanNode : public LinkedNode
{
	public:
		halfword nb; // Link
		SpanNode *info;
		scaled width;
		SpanNode(void) {}
		SpanNode(halfword n, SpanNode *i, scaled w) : nb(n), info(i), width(w) {}
		~SpanNode(void) { if (info) delete info; }
};

inline SpanNode * const end_span = dynamic_cast<SpanNode*>(&heads[9]); //!< tail of spanned-width lists

class AlignRecordNode : public SpanNode
{
	public:
		halfword &extra_info = SpanNode::nb;
		TokenList uPart;
		TokenList vPart;
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
