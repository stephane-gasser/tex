#include "getpreambletoken.h"
#include "gettoken.h"
#include "expand.h"
#include "fatalerror.h"
#include "scanoptionalequals.h"
#include "scanglue.h"
#include "geqdefine.h"
#include "eqdefine.h"

void getpreambletoken(void)
{
	while (true)
	{
		gettoken();
		while (curchr == span_code && curcmd == tab_mark)
		{
			gettoken();
			if (curcmd > max_command)
			{
				expand();
				gettoken();
			}
		}
		if (curcmd == endv)
			fatalerror("(interwoven alignment preambles are not allowed)");
		if (curcmd == assign_glue && curchr == glue_base+tab_skip_code)
		{
			scanoptionalequals();
			scanglue(glue_val);
			(global_defs() > 0 ? geqdefine : eqdefine)(glue_base+tab_skip_code, glue_ref, curval);
			continue;
		}
		break;
	}
}
