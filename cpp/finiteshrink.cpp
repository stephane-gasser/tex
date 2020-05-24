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
		helpline[4] = txt("The paragraph just ended includes some glue that has");
		helpline[3] = txt("infinite shrinkability, e.g., `\\hskip 0pt minus 1fil'.");
		helpline[2] = txt("Such glue doesn't belong there---it allows a paragraph");
		helpline[1] = txt("of any length to fit on one line. But it's safe to proceed,");
		helpline[0] = txt("since the offensive shrinkability has been made finite.");
		error();
	}
	q = newspec(p);
	subtype(q) = 0;
	deleteglueref(p);
	return q;
}
