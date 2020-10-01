#ifndef CONDITIONAL_H
#define CONDITIONAL_H

#include "globals.h"
#include "token.h"
#include "noeud.h"

void conditional(Token);

inline char iflimit = 0; // 0..4

class ConditionalNode : public LinkedNode
{
	public:
		quarterword subtype;
		int if_line_field;
		ConditionalNode(quarterword s) : subtype(s) { type = iflimit; }
};

inline ConditionalNode *condptr = nullptr;
inline int ifline = 0;
inline smallnumber curif = 0;

#endif
