#include "scanrulespec.h"
#include "newrule.h"
#include "scankeyword.h"
#include "scandimen.h"

constexpr int default_rule = 26214; //0.4\thinspace pt


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
		if (scankeyword("width"))
		{
			scan_normal_dimen();
			width(q) = curval;
			continue;
		}
		if (scankeyword("height"))
		{
			scan_normal_dimen();
			height(q) = curval;
			continue;
		}
		if (scankeyword("depth"))
		{
			scan_normal_dimen();
			depth(q) = curval;
			continue;
		}
		break;
	}
	return q;
}
