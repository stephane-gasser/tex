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
	if (l != clang)
	{
		newwhatsit(4, 2);
		link(tail+1) = l;
		clang = l;
		type(tail+1) = normmin(int_par(left_hyphen_min_code));
		subtype(tail+1) = normmin(int_par(right_hyphen_min_code));
	}
}
