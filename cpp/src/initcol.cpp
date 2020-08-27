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
		TokenNode *T;
		T->num = u_part(curalign);
		begintokenlist(T, u_template);
	}
}
