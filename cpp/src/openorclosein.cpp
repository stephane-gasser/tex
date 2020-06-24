#include "openorclosein.h"
#include "scanfourbitint.h"
#include "aclose.h"
#include "scanoptionalequals.h"
#include "scanfilename.h"
#include "packfilename.h"
#include "aopenin.h"
#include "texte.h"

void openorclosein(void)
{
	auto c = curchr;
	scanfourbitint();
	auto n = curval;
	if (readopen[n] != closed)
	{
		aclose(readfile[n]);
		readopen[n] = closed;
	}
	if (c)
	{
		scanoptionalequals();
		scanfilename();
		if (curext == "") 
			curext = ".tex";
		pack_cur_name();
		if (aopenin(readfile[n]))
			readopen[n] = just_open;
	}
}
