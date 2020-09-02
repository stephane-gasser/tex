#include "openorclosein.h"
#include "lecture.h"
#include "fichier.h"
#include "texte.h"

void openorclosein(halfword c)
{
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
		if (aopenin(readfile[n], pack_cur_name()))
			readopen[n] = just_open;
	}
}
