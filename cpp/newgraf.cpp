#include "newgraf.h"
#include "pushnest.h"
#include "normmin.h"
#include "newparamglue.h"
#include "newnullbox.h"
#include "begintokenlist.h"
#include "buildpage.h"

void newgraf(bool indented)
{
	prev_graf = 0;
	if (mode == vmode || head != tail)
		tail_append(newparamglue(2));
	pushnest();
	mode = hmode;
	space_factor = 1000;
	if (int_par(cur_fam_code) <= 0)
		curlang = 0;
	else 
		if (int_par(cur_fam_code) > 255)
			curlang = 0;
		else
			curlang = int_par(cur_fam_code);
	clang = curlang;
	prev_graf = (normmin(int_par(left_hyphen_min_code))*0x40+normmin(int_par(right_hyphen_min_code)))*0x1'00'00+curlang;
	if (indented)
	{
		tail = newnullbox();
		link(head) = tail;
		mem[tail+1].int_ = dimen_par(par_indent_code);
	}
	if (every_par())
		begintokenlist(every_par(), 7);
	if (nestptr == 1)
		buildpage();
}
