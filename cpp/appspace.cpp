#include "appspace.h"
#include "newparamglue.h"
#include "newspec.h"
#include "xnoverd.h"
#include "newglue.h"

void appspace(void)
{
	halfword q;
	if (space_factor >= 2000 && xspace_skip())
		q = newparamglue(13);
	else
	{
		if (space_skip())
			mainp = space_skip();
		else
		{
			mainp = fontglue[cur_font()];
			if (mainp == 0)
			{
				mainp = newspec(0);
				maink = parambase[cur_font()]+2;
				mem[mainp+1].int_ = fontinfo[maink].int_;
				mem[mainp+2].int_ = fontinfo[maink+1].int_;
				mem[mainp+3].int_ = fontinfo[maink+2].int_;
				fontglue[cur_font()] = mainp;
			}
		}
		mainp = newspec(mainp);
		if (space_factor >= 2000)
			mem[mainp+1].int_ += fontinfo[7+parambase[cur_font()]].int_;
		mem[mainp+2].int_ = xnoverd(mem[mainp+2].int_, space_factor, 1000);
		mem[mainp+3].int_ = xnoverd(mem[mainp+3].int_, 1000, space_factor);
		q = newglue(mainp);
		link(mainp) = 0;
	}
	tail_append(q);
}
