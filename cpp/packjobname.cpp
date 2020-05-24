#include "packjobname.h"
#include "packfilename.h"
#include "texte.h"

void packjobname(const std::string &s)
{
	curarea = txt("");
	curext = txt(s);
	curname = jobname;
	packfilename(curname, curarea, curext);
}
