#include "resumeafterdisplay.h"
#include "erreur.h"
#include "sauvegarde.h"
#include "pushnest.h"
#include "lecture.h"
#include "buildpage.h"
#include "backinput.h"
#include "cesure.h"

void resumeafterdisplay(Token t)
{
	if (curgroup != math_shift_group)
		confusion("display");
	unsave();
	prev_graf += 3;
	pushnest();
	mode = hmode;
	space_factor = 1000;
	set_cur_lang();
	clang = curlang;
	prev_graf = (((left_hyphen_min()<<6)+right_hyphen_min())<<16)+curlang;
	t = getxtoken();
	if (t.cmd != spacer)
		backinput(t);
	if (nest.size() == 2)
		buildpage();
}
