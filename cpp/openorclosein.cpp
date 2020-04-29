#include "openorclosein.h"
#include "scanfourbitint.h"
#include "aclose.h"
#include "scanoptionalequals.h"
#include "scanfilename.h"
#include "packfilename.h"
#include "aopenin.h"

void openorclosein(void)
{
	auto c = curchr;
	scanfourbitint();
	auto n = curval;
	if (readopen[n] != 2)
	{
	aclose(readfile[n]);
	readopen[n] = 2;
	}
	if (c)
	{
		scanoptionalequals();
		scanfilename();
		if (curext == 338) //
			curext = 790; //.tex
		packfilename(curname, curarea, curext);
		if (aopenin(readfile[n]))
			readopen[n] = 1;
	}
}
