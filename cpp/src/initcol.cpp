#include "initcol.h"
#include "backinput.h"
#include "lecture.h"

void initcol(Token t)
{
	curalign->extra_info = t.cmd;
	if (t.cmd == omit)
		alignstate = 0;
	else
	{
		backinput(t);
		begintokenlist(dynamic_cast<TokenNode*>(curalign->u_part), u_template);
	}
}
