#include "popalignment.h"
#include "noeud.h"

void popalignment(AlignRecordNode* &loop)
{
	delete curhead; 
	curtail = alignptr->tail;
	curhead = alignptr->head;
	alignstate = alignptr->state;
	loop = alignptr->loop;
	curspan = alignptr->span;
	preamble = alignptr->preamble;
	curalign = alignptr->align;
	auto p = alignptr;
	next(alignptr);
	delete p;
}
