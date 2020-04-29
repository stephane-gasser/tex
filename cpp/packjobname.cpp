#include "packjobname.h"
#include "packfilename.h"

void packjobname(strnumber s)
{
	curarea = 338;
	curext = s;
	curname = jobname;
	packfilename(curname, curarea, curext);
}
