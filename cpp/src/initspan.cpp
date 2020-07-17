#include "initspan.h"
#include "pushnest.h"
#include "normalparagraph.h"

void initspan(halfword p, halfword &span)
{
	pushnest();
	if (mode == -hmode)
		space_factor = 1000;
	else
	{
		prev_depth = -0x1'00'00*1000;
		normalparagraph();
	}
	span = p;
}
