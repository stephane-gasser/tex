#include "flushmath.h"
#include "noeud.h"

void flushmath(void)
{
	flushnodelist(link(head));
	flushnodelist(incompleat_noad);
	link(head) = 0;
	tail = head;
	incompleat_noad = 0;
}

