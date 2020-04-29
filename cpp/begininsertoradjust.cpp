#include "begininsertoradjust.h"
#include "scaneightbitint.h"
#include "printnl.h"
#include "print.h"
#include "printesc.h"
#include "printint.h"
#include "error.h"
#include "newsavelevel.h"
#include "scanleftbrace.h"
#include "normalparagraph.h"
#include "pushnest.h"

void begininsertoradjust(void)
{
	if (curcmd == 38)
		curval = 255;
	else
	{
		scaneightbitint();
		if (curval == 255)
		{
			if (interaction == 3)
				printnl(262); //! 
			print(1084); //You can't 
			printesc(330); //insert
			printint(255);
			helpptr = 1;
			helpline[0] = 1085; //I'm changing to \insert0; box 255 is special.
			error();
			curval = 0;
		}
	}
	savestack[saveptr++].int_ = curval;
	newsavelevel(11);
	scanleftbrace();
	normalparagraph();
	pushnest();
	curlist.modefield = -1;
	curlist.auxfield.int_ = -65536000;
}
