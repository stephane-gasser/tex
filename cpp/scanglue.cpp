#include "scanglue.h"
#include "getxtoken.h"
#include "scansomethinginternal.h"
#include "muerror.h"
#include "scandimen.h"
#include "backinput.h"
#include "newspec.h"
#include "scankeyword.h"

void scanglue(smallnumber level)
{
	bool mu = level == 3;
	bool negative = false;
	do
	{
		do
			getxtoken();
		while (curcmd == 10);
		if (curtok == 3117)
		{
			negative = !negative;
			curtok = 3115;
		}
	} while (curtok != 3115);
	if (curcmd >= 68 && curcmd <= 89)
	{
		scansomethinginternal(level, negative);
		if (curvallevel >= 2)
		{
			if (curvallevel != level)
				muerror();
			return;
		}
		if (curvallevel == 0)
			scandimen(mu, false, true);
		else 
			if (level == 3)
				muerror();
	}
	else
	{
		backinput();
		scandimen(mu, false, false);
		if (negative)
			curval = -curval;
	}
	auto q = newspec(0);
	mem[q+1].int_ = curval;
	if (scankeyword(730)) //plus
	{
		scandimen(mu, true, false);
		mem[q+2].int_ = curval;
		type(q) = curorder;
	}
	if (scankeyword(731)) //minus
	{
		scandimen(mu, true, false);
		mem[q+3].int_ = curval;
		subtype(q) = curorder;
	}
	curval = q;
}
