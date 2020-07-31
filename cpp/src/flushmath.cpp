#include "flushmath.h"
#include "noeud.h"

void flushmath(void)
{
	flushnodelist(head->link);
	flushnodelist(incompleat_noad);
	head->link = nullptr;
	tail = head;
	incompleat_noad = 0;
}

