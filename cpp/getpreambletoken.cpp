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
		while (curchr == 256 && curcmd == tab_mark)
		{
			gettoken();
			if (curcmd > max_command)
			{
				expand();
				gettoken();
			}
		}
		if (curcmd == endv)
			fatalerror(595); //(interwoven alignment preambles are not allowed)
		if (curcmd == assign_glue && curchr == 2893)
		{
			scanoptionalequals();
			scanglue(2);
			if (int_par(global_defs_code) > 0)
				geqdefine(2893, glue_ref, curval);
			else
				eqdefine(2893, glue_ref, curval);
			continue;
		}
		break;
	}
}
