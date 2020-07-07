#include "appenddiscretionary.h"
#include "newdisc.h"
#include "newcharacter.h"
#include "newsavelevel.h"
#include "lecture.h"
#include "pushnest.h"

void appenddiscretionary(void)
{
	tail_append(newdisc());
	if (curchr == 1)
	{
		int c = hyphenchar[cur_font()];
		if (c >= 0 && c < 0x1'00)
			pre_break(tail) = newcharacter(cur_font(), c);
	}
	else
	{
		savestack[saveptr++].int_ = 0;
		newsavelevel(disc_group);
		scanleftbrace();
		pushnest();
		mode = -hmode;
		space_factor = 1000;
	}
}
