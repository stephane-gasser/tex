#include "initcol.h"
#include "backinput.h"
#include "begintokenlist.h"

void initcol(void)
{
	info(curalign+5) = curcmd;
	if (curcmd == 63)
		alignstate = 0;
	else
	{
		backinput();
		begintokenlist(mem[curalign+3].int_, 1);
	}
}
