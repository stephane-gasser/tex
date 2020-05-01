#include "itsallover.h"
#include "backinput.h"
#include "newnullbox.h"
#include "newglue.h"
#include "newpenalty.h"
#include "buildpage.h"
#include "privileged.h"

bool itsallover(void)
{
	if (privileged())
	{
		if (29998 == pagetail && curlist.headfield == curlist.tailfield &&deadcycles == 0)
			return true;
		backinput();
		link(curlist.tailfield) = newnullbox();
		curlist.tailfield = link(curlist.tailfield);
		mem[curlist.tailfield+1].int_ = dimen_par(hsize_code);
		link(curlist.tailfield) = newglue(8);
		curlist.tailfield = link(curlist.tailfield);
		link(curlist.tailfield) = newpenalty(-1073741824);
		curlist.tailfield = link(curlist.tailfield);
		buildpage();
	}
	return false;
}
