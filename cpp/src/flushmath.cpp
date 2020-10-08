#include "flushmath.h"
#include "noeud.h"
#include "etat.h"

void flushmath(void)
{
	flushnodelist(head->link);
	flushnodelist(incompleat_noad);
	head->link = nullptr;
	tail = head;
	incompleat_noad = nullptr;
}

