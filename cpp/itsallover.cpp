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
		width(tail) = dimen_par(hsize_code);
		tail_append(newglue(8));
		tail_append(newpenalty(-0x40'00'00'00));
		buildpage();
	}
	return false;
}
