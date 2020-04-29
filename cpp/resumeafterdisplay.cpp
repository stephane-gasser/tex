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
	curlist.pgfield += 3;
	pushnest();
	curlist.modefield = 102;
	curlist.auxfield.hh.lh = 1000;
	if (eqtb[5313].int_ <= 0)
		curlang = 0;
	else 
		if (eqtb[5313].int_ > 255)
			curlang = 0;
		else
		curlang = eqtb[5313].int_;
	curlist.auxfield.hh.rh = curlang;
	curlist.pgfield = (normmin(eqtb[5314].int_)*64+normmin(eqtb[5315].int_))*65536+curlang;
	getxtoken();
	if (curcmd != 10)
		backinput();
	if (nestptr == 1)
		buildpage();
}
