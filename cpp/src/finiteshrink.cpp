#include "finiteshrink.h"
#include "impression.h"
#include "noeud.h"
#include "erreur.h"
#include "deleteglueref.h"
#include "texte.h"

halfword finiteshrink(halfword p)
{
	if (noshrinkerroryet)
		error("Infinite glue shrinkage found in a paragraph", "The paragraph just ended includes some glue that has\ninfinite shrinkability, e.g., `\\hskip 0pt minus 1fil'.\nSuch glue doesn't belong there---it allows a paragraph\nof any length to fit on one line. But it's safe to proceed,\nsince the offensive shrinkability has been made finite.", curalign);
	noshrinkerroryet = false;
	auto q = newspec(p);
	subtype(q) = 0;
	deleteglueref(p);
	return q;
}
