#include "fixlanguage.h"
#include "noeud.h"
#include "normmin.h"

void fixlanguage(void)
{
	ASCIIcode l = language();
	if (l <= 0 || l > 255)
		l = 0;
	if (l != clang)
	{
		clang = l;
		auto w = new LanguageWhatsitNode(l);
		w->what_lhm = normmin(left_hyphen_min());
		w->what_rhm = normmin(right_hyphen_min());
		tail_append(w);
	}
}
