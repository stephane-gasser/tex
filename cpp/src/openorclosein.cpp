#include "openorclosein.h"
#include "lecture.h"
#include "packfilename.h"
#include "fichier.h"
#include "texte.h"

void openorclosein(halfword c, halfword align)
{
	auto n = scanfourbitint(align);
	if (readopen[n] != closed)
	{
		aclose(readfile[n]);
		readopen[n] = closed;
	}
	if (c)
	{
		scanoptionalequals(align);
		scanfilename(align);
		if (curext == "") 
			curext = ".tex";
		pack_cur_name();
		if (aopenin(readfile[n]))
			readopen[n] = just_open;
	}
}
