#include "itsallover.h"
#include "backinput.h"
#include "noeud.h"
#include "buildpage.h"
#include "erreur.h"

bool itsallover(eightbits cmd, halfword chr, halfword tok, halfword align)
{
	if (privileged(cmd, chr))
	{
		if (page_head == pagetail && head == tail && deadcycles == 0)
			return true;
		backinput(tok);
		tail_append(newnullbox());
		width(tail) = hsize();
		tail_append(newglue(fill_glue));
		tail_append(newpenalty(null_flag));
		buildpage(align);
	}
	return false;
}
