#include "initcol.h"
#include "backinput.h"
#include "lecture.h"

void initcol(Token t)
{
	extra_info(curalign) = t.cmd;
	if (t.cmd == omit)
		alignstate = 0;
	else
	{
		backinput(t);
		begintokenlist(u_part(curalign), u_template);
	}
}
