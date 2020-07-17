#include "initcol.h"
#include "backinput.h"
#include "lecture.h"

void initcol(eightbits cmd, halfword tok, halfword align)
{
	extra_info(align) = cmd;
	if (cmd == omit)
		alignstate = 0;
	else
	{
		backinput(tok);
		begintokenlist(u_part(align), u_template);
	}
}
