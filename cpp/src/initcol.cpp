#include "initcol.h"
#include "backinput.h"
#include "lecture.h"

void initcol(eightbits cmd, halfword tok)
{
	extra_info(curalign) = cmd;
	if (cmd == omit)
		alignstate = 0;
	else
	{
		backinput(tok);
		begintokenlist(u_part(curalign), u_template);
	}
}
