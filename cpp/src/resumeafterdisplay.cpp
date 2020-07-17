#include "resumeafterdisplay.h"
#include "erreur.h"
#include "unsave.h"
#include "pushnest.h"
#include "lecture.h"
#include "normmin.h"
#include "buildpage.h"
#include "backinput.h"

void resumeafterdisplay(halfword tok, halfword align)
{
	if (curgroup != math_shift_group)
		confusion("display", align);
	unsave(tok);
	prev_graf += 3;
	pushnest();
	mode = hmode;
	space_factor = 1000;
	set_cur_lang();
	clang = curlang;
	prev_graf = (((normmin(left_hyphen_min())<<6)+normmin(right_hyphen_min()))<<16)+curlang;
	eightbits cmd;
	std::tie(cmd, std::ignore, tok, std::ignore) = getxtoken(align);
	if (cmd != spacer)
		backinput(tok);
	if (nestptr == 1)
		buildpage(align);
}
