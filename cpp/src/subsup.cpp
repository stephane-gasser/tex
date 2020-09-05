#include "subsup.h"
#include "noeud.h"
#include "impression.h"
#include "erreur.h"
#include "lecture.h"

static bool scripts_allowed(LinkedNode *tail) { return tail->type >= ord_noad && tail->type < left_noad; }

void subsup(eightbits cmd) //sub_mark || sup_mark
{
	smallnumber t = 0;
	NoadContent *p = nullptr;
	if (tail != head && scripts_allowed(tail))
	{
		auto Tail = dynamic_cast<Noad*>(tail);
		p = cmd == sup_mark ? &Tail->supscr : &Tail->subscr;
		t = p->math_type;
	}
	if (p == nullptr || t)
	{
		auto n = new Noad;
		p = cmd == sup_mark ? &n->supscr : &n->subscr;
		tail_append(n);
		if (t)
			if (cmd == sup_mark)
				error("Double superscript", "I treat `x^1^2' essentially like `x^1{}^2'.");
			else
				error("Double subscript", "I treat `x_1_2' essentially like `x_1{}_2'.");
	}
	scanmath(*p);
}
