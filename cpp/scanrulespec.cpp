#include "scanrulespec.h"
#include "newrule.h"
#include "scankeyword.h"
#include "scandimen.h"

halfword scanrulespec(void)
{
	auto q = newrule();
	if (curcmd == vrule)
		width(q) = default_rule;
	else
	{
		height(q) = default_rule;
		depth(q) = 0;
	}
	while (true)
	{
		if (scankeyword(732)) //width
		{
			scandimen(false, false, false);
			width(q) = curval;
			continue;
		}
		if (scankeyword(733)) //height
		{
			scandimen(false, false, false);
			height(q) = curval;
			continue;
		}
		if (scankeyword(734)) //depth
		{
			scandimen(false, false, false);
			depth(q) = curval;
			continue;
		}
	break;
	}
	return q;
}
