#include "begininsertoradjust.h"
#include "scaneightbitint.h"
#include "impression.h"
#include "error.h"
#include "newsavelevel.h"
#include "scanleftbrace.h"
#include "normalparagraph.h"
#include "pushnest.h"
#include "texte.h"

void begininsertoradjust(void)
{
	if (curcmd == vadjust)
		curval = 255;
	else
	{
		scaneightbitint();
		if (curval == 255)
		{
			print_err("You can't "+esc("insert")+"255");
			helpptr = 1;
			helpline[0] = "I'm changing to \\insert0; box 255 is special.";
			error();
			curval = 0;
		}
	}
	savestack[saveptr++].int_ = curval;
	newsavelevel(insert_group);
	scanleftbrace();
	normalparagraph();
	pushnest();
	mode = -vmode;
	prev_depth = ignore_depth;
}
