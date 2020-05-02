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
		confusion(1168); //display
	unsave();
	prev_graf += 3;
	pushnest();
	mode = hmode;
	space_factor = 1000;
	if (int_par(language_code) <= 0)
		curlang = 0;
	else 
		if (int_par(language_code) > 255)
			curlang = 0;
		else
		curlang = int_par(language_code);
	clang = curlang;
	prev_graf = (normmin(int_par(left_hyphen_min_code))*64+normmin(int_par(right_hyphen_min_code)))*0x1'00'00+curlang;
	getxtoken();
	if (curcmd != spacer)
		backinput();
	if (nestptr == 1)
		buildpage();
}
