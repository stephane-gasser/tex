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
		while (curchr == 256 && curcmd == 4)
		{
			gettoken();
			if (curcmd > 100)
			{
				expand();
				gettoken();
			}
		}
		if (curcmd == 9)
			fatalerror(595); //(interwoven alignment preambles are not allowed)
		if (curcmd == 75 && curchr == 2893)
		{
			scanoptionalequals();
			scanglue(2);
			if (eqtb[5306].int_ > 0)
				geqdefine(2893, 117, curval);
			else
				eqdefine(2893, 117, curval);
			continue;
		}
		break;
	}
}
