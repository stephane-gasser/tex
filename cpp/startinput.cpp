#include "startinput.h"
#include "scanfilename.h"
#include "packfilename.h"
#include "beginfilereading.h"
#include "aopenin.h"
#include "endfilereading.h"
#include "promptfilename.h"
#include "openlogfile.h"
#include "println.h"
#include "printchar.h"
#include "slowprint.h"
#include "firmuptheline.h"
#include "amakenamestring.h"
#include "inputln.h"
#include <iostream>
#include "texte.h"

void startinput(void)
{
	scanfilename();
	if (curext == "")
		curext = ".tex";
	packfilename(curname, curarea, curext);
	while (true)
	{
		beginfilereading();
		if (aopenin(inputfile[curinput.indexfield]))
			break;
		if (curarea == "")
		{
			packfilename(curname, "TeXinputs:", curext);
			if (aopenin(inputfile[curinput.indexfield]))
				break;
		}
		endfilereading();
		promptfilename("input file name", ".tex");
	}
	curinput.namefield = amakenamestring(inputfile[curinput.indexfield]);
	if (jobname == "")
	{
		jobname = curname;
		openlogfile();
	}
	if (termoffset+strstart[curinput.namefield+1]-strstart[curinput.namefield] > maxprintline-2)
		println();
	else 
		if (termoffset > 0 || fileoffset > 0)
		printchar(' ');
	printchar('(');
	openparens++;
	slowprint(curinput.namefield);
	std::cout << std::flush;
	curinput.statefield = 33;
	if (curinput.namefield == strptr-1)
	{
		strptr--;
		poolptr = strstart[strptr];
		curinput.namefield = txt(curname);
	}
	line = 1;
	if (inputln(inputfile[curinput.indexfield], false))
		firmuptheline();
	if ((int_par(end_line_char_code) < 0 || int_par(end_line_char_code) > 255))
		curinput.limitfield--;
	else
		buffer[curinput.limitfield] = int_par(end_line_char_code);
	First = curinput.limitfield+1;
	curinput.locfield = curinput.startfield;
}
