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

void startinput(void)
{
	scanfilename();
	if (curext == 338) //
		curext = 790; //.tex
	packfilename(curname, curarea, curext);
	while (true)
	{
		beginfilereading();
		if (aopenin(inputfile[curinput.indexfield]))
			break;
		if (curarea == 338) //
		{
			packfilename(curname, 783, curext); //TeXinputs:
			if (aopenin(inputfile[curinput.indexfield]))
				break;
		}
		endfilereading();
		promptfilename(786, 790); //input file name//.tex
	}
	curinput.namefield = amakenamestring(inputfile[curinput.indexfield]);
	if (jobname == 0)
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
		curinput.namefield = curname;
	}
	line = 1;
	if (inputln(inputfile[curinput.indexfield], false))
		firmuptheline();
	if ((eqtb[5311].int_ < 0 || eqtb[5311].int_ > 255))
		curinput.limitfield--;
	else
		buffer[curinput.limitfield] = eqtb[5311].int_;
	First = curinput.limitfield+1;
	curinput.locfield = curinput.startfield;
}
