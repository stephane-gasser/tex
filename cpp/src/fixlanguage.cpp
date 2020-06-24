#include "fixlanguage.h"
#include "newwhatsit.h"
#include "normmin.h"

void fixlanguage(void)
{
	ASCIIcode l = language();
	if (l <= 0 || l > 255)
			l = 0;
	if (l != clang)
	{
		newwhatsit(language_node, small_node_size);
		what_lang(tail) = l;
		clang = l;
		what_lhm(tail) = normmin(left_hyphen_min());
		what_rhm(tail) = normmin(right_hyphen_min());
	}
}
