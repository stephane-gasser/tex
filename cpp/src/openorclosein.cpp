#include "openorclosein.h"
#include "lecture.h"
#include "packfilename.h"
#include "fichier.h"
#include "texte.h"

void openorclosein(void)
{
	auto c = curchr;
	auto n = scanfourbitint();
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
