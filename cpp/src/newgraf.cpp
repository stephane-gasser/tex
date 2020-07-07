#include "newgraf.h"
#include "pushnest.h"
#include "normmin.h"
#include "newparamglue.h"
#include "newnullbox.h"
#include "lecture.h"
#include "buildpage.h"

static halfword& every_par(void) { return equiv(every_par_loc); }

void newgraf(bool indented)
{
	prev_graf = 0;
	if (mode == vmode || head != tail)
		tail_append(newparamglue(par_skip_code));
	pushnest();
	mode = hmode;
	space_factor = 1000;
	set_cur_lang();
	clang = curlang;
	prev_graf = (normmin(left_hyphen_min())<<6+normmin(right_hyphen_min()))<<16+curlang;
	if (indented)
	{
		tail = newnullbox();
		link(head) = tail;
		width(tail) = par_indent();
	}
	if (every_par())
		begintokenlist(every_par(), every_par_text);
	if (nestptr == 1)
		buildpage();
}
