#include "scanrulespec.h"
#include "newrule.h"
#include "scankeyword.h"
#include "scandimen.h"

halfword scanrulespec(void)
{
	auto q = newrule();
	if (curcmd == 35)
		mem[q+1].int_ = 26214;
	else
	{
		mem[q+3].int_ = 26214;
		mem[q+2].int_ = 0;
	}
	while (true)
	{
		if (scankeyword(732)) //width
		{
			scandimen(false, false, false);
			mem[q+1].int_ = curval;
			continue;
		}
		if (scankeyword(733)) //height
		{
			scandimen(false, false, false);
			mem[q+3].int_ = curval;
			continue;
		}
		if (scankeyword(734)) //depth
		{
			scandimen(false, false, false);
			mem[q+2].int_ = curval;
			continue;
		}
	break;
	}
	return q;
}
