#include "fixlanguage.h"
#include "newwhatsit.h"
#include "normmin.h"

void fixlanguage(void)
{
	ASCIIcode l;
	if (int_par(language_code) <= 0)
		l = 0;
	else 
		if (int_par(language_code) > 255)
			l = 0;
		else
			l = int_par(language_code);
	if (l != curlist.auxfield.hh.rh)
	{
		newwhatsit(4, 2);
		link(curlist.tailfield+1) = l;
		curlist.auxfield.hh.rh = l;
		type(curlist.tailfield+1) = normmin(int_par(left_hyphen_min_code));
		subtype(curlist.tailfield+1) = normmin(int_par(right_hyphen_min_code));
	}
}
