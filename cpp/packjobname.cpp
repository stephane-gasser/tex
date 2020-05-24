#include "packjobname.h"
#include "packfilename.h"
#include "texte.h"

void packjobname(const std::string &s)
{
	curarea = "";
	curext = s;
	curname = jobname;
	packfilename(curname, curarea, curext);
}
