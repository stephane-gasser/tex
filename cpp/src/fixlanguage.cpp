#include "fixlanguage.h"
#include "noeud.h"
#include "equivalent.h"

void fixlanguage(void)
{
	ASCIIcode l = language();
	if (l <= 0 || l > 255)
		l = 0;
	if (l != clang)
	{
		clang = l;
		auto w = new LanguageWhatsitNode(l);
		w->what_lhm = left_hyphen_min();
		w->what_rhm = right_hyphen_min();
		tail_append(w);
	}
}
