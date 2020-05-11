#include "initcol.h"
#include "backinput.h"
#include "begintokenlist.h"

void initcol(void)
{
	info(curalign+5) = curcmd;
	if (curcmd == omit)
		alignstate = 0;
	else
	{
		backinput();
		begintokenlist(u_part(curalign), 1);
	}
}
