#include "scanglue.h"
#include "getxtoken.h"
#include "scansomethinginternal.h"
#include "erreur.h"
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
		while (curcmd == spacer);
		if (curtok == other_char*0x1'00+'-')
		{
			negative = !negative;
			curtok = other_char*0x1'00+'+';
		}
	} while (curtok != other_char*0x1'00+'+');
	if (curcmd >= min_internal && curcmd <= max_internal)
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
	auto q = newspec(zero_glue);
	width(q) = curval;
	if (scankeyword("plus"))
	{
		scandimen(mu, true, false);
		stretch(q) = curval;
		type(q) = curorder;
	}
	if (scankeyword("minus"))
	{
		scandimen(mu, true, false);
		shrink(q) = curval;
		subtype(q) = curorder;
	}
	curval = q;
}
