#include "subsup.h"
#include "noeud.h"
#include "impression.h"
#include "erreur.h"
#include "lecture.h"
#include "texte.h"

static bool scripts_allowed(halfword tail) { return type(tail) >= ord_noad && type(tail) < left_noad; }

void subsup(eightbits cmd, halfword align)
{
	smallnumber t = 0;
	halfword p = 0;
	if (tail != head)
		if (scripts_allowed(tail))
		{
			p = supscr(tail)+cmd-sup_mark;
			t = link(p);
		}
	if (p == 0 || t)
	{
		tail_append(newnoad());
		p = supscr(tail)+cmd-sup_mark;
		if (t)
		{
			if (cmd == sup_mark)
				error("Double superscript", "I treat `x^1^2' essentially like `x^1{}^2'.", align);
			else
				error("Double subscript", "I treat `x_1_2' essentially like `x_1{}_2'.", align);
		}
	}
	scanmath(p, align);
}
