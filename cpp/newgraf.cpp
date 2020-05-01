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
	if (int_par(cur_fam_code) <= 0)
		curlang = 0;
	else 
		if (int_par(cur_fam_code) > 255)
			curlang = 0;
		else
			curlang = int_par(cur_fam_code);
	curlist.auxfield.hh.rh = curlang;
	curlist.pgfield = (normmin(int_par(left_hyphen_min_code))*64+normmin(int_par(right_hyphen_min_code)))*65536+curlang;
	if (indented)
	{
		curlist.tailfield = newnullbox();
		link(curlist.headfield) = curlist.tailfield;
		mem[curlist.tailfield+1].int_ = dimen_par(par_indent_code);
	}
	if (every_par())
		begintokenlist(every_par(), 7);
	if (nestptr == 1)
		buildpage();
}
