#include "finiteshrink.h"
#include "printnl.h"
#include "print.h"
#include "newspec.h"
#include "error.h"
#include "deleteglueref.h"

halfword finiteshrink(halfword p)
{
	halfword q;
	if (noshrinkerroryet)
	{
		noshrinkerroryet = false;
		printnl(262); //! 
		print(916); //Infinite glue shrinkage found in a paragraph
		helpptr = 5;
		helpline[4] = 917; //The paragraph just ended includes some glue that has
		helpline[3] = 918; //infinite shrinkability, e.g., `\hskip 0pt minus 1fil'.
		helpline[2] = 919; //Such glue doesn't belong there---it allows a paragraph
		helpline[1] = 920; //of any length to fit on one line. But it's safe to proceed,
		helpline[0] = 921; //since the offensive shrinkability has been made finite.
		error();
	}
	q = newspec(p);
	subtype(q) = 0;
	deleteglueref(p);
	return q;
}
