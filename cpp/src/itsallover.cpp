#include "itsallover.h"
#include "backinput.h"
#include "noeud.h"
#include "buildpage.h"
#include "equivalent.h"
#include "erreur.h"

bool itsallover(Token t)
{
	if (privileged(t))
	{
		if (page_head == pagetail && head == tail && deadcycles == 0)
			return true;
		backinput(t);
		auto b = new BoxNode;
		b->width = hsize();
		tail_append(b);
		tail_append(new GlueNode(fill_glue));
		tail_append(new PenaltyNode(null_flag));
		buildpage();
	}
	return false;
}
