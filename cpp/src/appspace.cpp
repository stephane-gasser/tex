#include "appspace.h"
#include "newparamglue.h"
#include "newspec.h"
#include "xnoverd.h"
#include "newglue.h"

//! additional space at end of sentence
static int& extra_space(internalfontnumber f) { return param(extra_space_code, f); }

static halfword& xspace_skip(void) { return glue_par(xspace_skip_code); }

//! Handle spaces when <em> space_factor != 1000 </em>.
void appspace(halfword &mainp, fontindex &maink)
{
	halfword q; // glue node
	if (space_factor >= 2000 && xspace_skip() != zero_glue)
		q = newparamglue(xspace_skip_code);
	else
	{
		if (space_skip() != zero_glue)
			mainp = space_skip();
		else // Find the glue specification, \a main_p, for text spaces in the current font
		{
			mainp = fontglue[cur_font()];
			if (mainp == 0)
			{
				mainp = newspec(zero_glue);
				maink = space_code+parambase[cur_font()];
				width(mainp) = space(cur_font());
				stretch(mainp) = space_stretch(cur_font());
				shrink(mainp) = space_shrink(cur_font());
				fontglue[cur_font()] = mainp;
			}
		}
		mainp = newspec(mainp);
		// Modify the glue specification in \a main_p according to the space factor
		if (space_factor >= 2000)
			width(mainp) += extra_space(cur_font());
		stretch(mainp) = xnoverd(stretch(mainp), space_factor, 1000);
		shrink(mainp) = xnoverd(shrink(mainp), 1000, space_factor);
		q = newglue(mainp);
		link(mainp) = 0;
	}
	tail_append(q);
}
