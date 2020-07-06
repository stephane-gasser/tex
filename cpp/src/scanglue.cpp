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
		if (curtok == other_token+'-')
		{
			negative = !negative;
			curtok = other_token+'+';
		}
	} while (curtok != other_token+'+');
	if (curcmd >= min_internal && curcmd <= max_internal)
	{
		scansomethinginternal(level, negative);
		if (curvallevel >= 2)
		{
			if (curvallevel != level)
				error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.");
			return;
		}
		if (curvallevel == 0)
			scandimen(mu, false, true);
		else 
			if (level == 3)
				error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.");
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
