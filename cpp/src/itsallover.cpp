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
		if (page_head == pagetail && head == tail && deadcycles == 0)
			return true;
		backinput();
		tail_append(newnullbox());
		width(tail) = hsize();
		tail_append(newglue(fill_glue));
		tail_append(newpenalty(null_flag));
		buildpage();
	}
	return false;
}
