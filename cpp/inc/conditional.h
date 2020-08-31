#ifndef CONDITIONAL_H
#define CONDITIONAL_H

#include "globals.h"

void conditional(Token);

class ConditionalNode : public LinkedNode
{
	public:
		quarterword subtype;
		int if_line_field;
		ConditionalNode(quarterword s) : subtype(s) { type = iflimit; }
};

inline ConditionalNode *condptr = nullptr;

#endif
