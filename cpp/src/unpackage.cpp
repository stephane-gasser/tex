#include "unpackage.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "noeud.h"

void unpackage(halfword c)
{
	int val = scaneightbitint();
	auto p = box[val];
	if (p == nullptr)
		return;
	if (abs(mode) == mmode || (abs(mode) == vmode && p->type != vlist_node) || (abs(mode) == hmode && p->type != hlist_node))
	{
		error("Incompatible list can't be unboxed", "Sorry, Pandora. (You sneaky devil.)\nI refuse to unbox an \\hbox in vertical mode or vice versa.\nAnd I can't open any boxes in math mode.");
		return;
	}
	if (c == copy_code)
		tail->link = copynodelist(p->list_ptr);
	else
	{
		tail->link = p->list_ptr;
		box[val] = nullptr;
		delete p;
	}
	while (tail->link)
		tail = tail->link;
}
