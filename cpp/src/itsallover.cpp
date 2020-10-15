#include "itsallover.h"
#include "etat.h"
#include "noeud.h"
#include "buildpage.h"
#include "equivalent.h"
#include "erreur.h"
#include "getnext.h"

bool itsallover(char status, Token t)
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
		buildpage(status);
	}
	return false;
}
