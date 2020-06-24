#include "initcol.h"
#include "backinput.h"
#include "begintokenlist.h"

void initcol(void)
{
	extra_info(curalign) = curcmd;
	if (curcmd == omit)
		alignstate = 0;
	else
	{
		backinput();
		begintokenlist(u_part(curalign), u_template);
	}
}
