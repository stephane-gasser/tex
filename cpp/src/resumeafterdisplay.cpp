#include "resumeafterdisplay.h"
#include "confusion.h"
#include "unsave.h"
#include "pushnest.h"
#include "getxtoken.h"
#include "normmin.h"
#include "buildpage.h"
#include "backinput.h"

void resumeafterdisplay(void)
{
	if (curgroup != 15)
		confusion("display");
	unsave();
	prev_graf += 3;
	pushnest();
	mode = hmode;
	space_factor = 1000;
	set_cur_lang();
	clang = curlang;
	prev_graf = (normmin(left_hyphen_min())*64+normmin(right_hyphen_min()))*0x1'00'00+curlang;
	getxtoken();
	if (curcmd != spacer)
		backinput();
	if (nestptr == 1)
		buildpage();
}
