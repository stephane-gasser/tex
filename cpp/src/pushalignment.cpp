#include "pushalignment.h"
#include "noeud.h"

void pushalignment(AlignRecordNode* loop)
{
	alignptr = new AlignStackNode;
	alignptr->link = alignptr;
	alignptr->align = curalign;
	alignptr->preamble = preamble;
	alignptr->span = curspan;
	alignptr->loop = loop;
	alignptr->state = alignstate;
	alignptr->head = curhead;
	alignptr->tail = curtail;
	curhead = new LinkedNode;
}
