#include "finiteshrink.h"
#include "printnl.h"
#include "print.h"
#include "newspec.h"
#include "error.h"
#include "deleteglueref.h"
#include "texte.h"

halfword finiteshrink(halfword p)
{
	halfword q;
	if (noshrinkerroryet)
	{
		noshrinkerroryet = false;
		printnl("! ");
		print("Infinite glue shrinkage found in a paragraph");
		helpptr = 5;
		helpline[4] = "The paragraph just ended includes some glue that has";
		helpline[3] = "infinite shrinkability, e.g., `\\hskip 0pt minus 1fil'.";
		helpline[2] = "Such glue doesn't belong there---it allows a paragraph";
		helpline[1] = "of any length to fit on one line. But it's safe to proceed,";
		helpline[0] = "since the offensive shrinkability has been made finite.";
		error();
	}
	q = newspec(p);
	subtype(q) = 0;
	deleteglueref(p);
	return q;
}
