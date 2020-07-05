#include "finiteshrink.h"
#include "impression.h"
#include "newspec.h"
#include "erreur.h"
#include "deleteglueref.h"
#include "texte.h"

static void erreurFiniteshrink(void)
{
	print_err("Infinite glue shrinkage found in a paragraph");
	helpptr = 5;
	helpline[4] = "The paragraph just ended includes some glue that has";
	helpline[3] = "infinite shrinkability, e.g., `\\hskip 0pt minus 1fil'.";
	helpline[2] = "Such glue doesn't belong there---it allows a paragraph";
	helpline[1] = "of any length to fit on one line. But it's safe to proceed,";
	helpline[0] = "since the offensive shrinkability has been made finite.";
	error();
}

halfword finiteshrink(halfword p)
{
	halfword q;
	if (noshrinkerroryet)
	{
		noshrinkerroryet = false;
		erreurFiniteshrink();
	}
	q = newspec(p);
	subtype(q) = 0;
	deleteglueref(p);
	return q;
}
