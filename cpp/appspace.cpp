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
				mainp = newspec(zero_glue);
				maink = 2+parambase[cur_font()];
				width(mainp) = param(space_code, cur_font());
				stretch(mainp) = param(space_stretch_code, cur_font());
				shrink(mainp) = param(space_shrink_code, cur_font());
				fontglue[cur_font()] = mainp;
			}
		}
		mainp = newspec(mainp);
		if (space_factor >= 2000)
			width(mainp) += param(extra_space_code, cur_font());
		stretch(mainp) = xnoverd(stretch(mainp), space_factor, 1000);
		shrink(mainp) = xnoverd(shrink(mainp), 1000, space_factor);
		q = newglue(mainp);
		link(mainp) = 0;
	}
	tail_append(q);
}
