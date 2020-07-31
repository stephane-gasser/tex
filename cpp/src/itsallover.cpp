#include "itsallover.h"
#include "backinput.h"
#include "noeud.h"
#include "buildpage.h"
#include "erreur.h"

bool itsallover(Token t)
{
	if (privileged(t))
	{
		if (page_head == pagetail && head == tail && deadcycles == 0)
			return true;
		backinput(t);
		tail_append(newnullbox());
		width(tail->num) = hsize();
		tail_append(newglue(fill_glue));
		tail_append(newpenalty(null_flag));
		buildpage();
	}
	return false;
}
