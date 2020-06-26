#include "subsup.h"
#include "newnoad.h"
#include "impression.h"
#include "error.h"
#include "scanmath.h"
#include "texte.h"

static bool scripts_allowed(halfword tail)
{
	return type(tail) >= ord_noad && type(tail) < left_noad;
}

void subsup(void)
{
	smallnumber t = 0;
	halfword p = 0;
	if (tail != head)
		if (scripts_allowed(tail))
		{
			p = tail+2+curcmd-sup_mark;
			t = link(p);
		}
	if (p == 0 || t)
	{
		tail_append(newnoad());
		p = tail+2+curcmd-sup_mark;
		if (t)
		{
			if (curcmd == sup_mark)
			{
				print_err("Double superscript");
				helpptr = 1;
				helpline[0] = "I treat `x^1^2' essentially like `x^1{}^2'.";
			}
			else
			{
				print_err("Double subscript");
				helpptr = 1;
				helpline[0] = "I treat `x_1_2' essentially like `x_1{}_2'.";
			}
			error();
		}
	}
	scanmath(p);
}
