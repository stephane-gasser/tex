#include "appenddiscretionary.h"
#include "newdisc.h"
#include "newcharacter.h"
#include "newsavelevel.h"
#include "scanleftbrace.h"
#include "pushnest.h"

void appenddiscretionary(void)
{
	link(curlist.tailfield) = newdisc();
	curlist.tailfield = link(curlist.tailfield);
	if (curchr == 1)
	{
		int c = hyphenchar[eqtb[3934].hh.rh];
		if (c >= 0 && c < 256)
			info(curlist.tailfield+1) = newcharacter(eqtb[3934].hh.rh, c);
	}
	else
	{
		savestack[saveptr++].int_ = 0;
		newsavelevel(10);
		scanleftbrace();
		pushnest();
		curlist.modefield = -102;
		curlist.auxfield.hh.lh = 1000;
	}
}
