#include "newgraf.h"
#include "pushnest.h"
#include "normmin.h"
#include "newparamglue.h"
#include "newnullbox.h"
#include "begintokenlist.h"
#include "buildpage.h"

void newgraf(bool indented)
{
	curlist.pgfield = 0;
	if (curlist.modefield == 1 || curlist.headfield != curlist.tailfield)
	{
		link(curlist.tailfield) = newparamglue(2);
		curlist.tailfield = link(curlist.tailfield);
	}
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
	if (indented)
	{
		curlist.tailfield = newnullbox();
		link(curlist.headfield) = curlist.tailfield;
		mem[curlist.tailfield+1].int_ = eqtb[5830].int_;
	}
	if (eqtb[3414].hh.rh)
		begintokenlist(eqtb[3414].hh.rh, 7);
	if (nestptr == 1)
		buildpage();
}
