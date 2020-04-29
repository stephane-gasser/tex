#include "shipout.h"
#include "printnl.h"
#include "println.h"
#include "error.h"
#include "bopenout.h"
#include "preparemag.h"
#include "bmakenamestring.h"
#include "print.h"
#include "printtwo.h"
#include "printint.h"
#include "printchar.h"
#include "begindiagnostic.h"
#include "enddiagnostic.h"
#include "showbox.h"
#include "flushnodelist.h"
#include "openlogfile.h"
#include "packjobname.h"
#include "promptfilename.h"
#include "dviswap.h"
#include "dvifour.h"
#include "vlistout.h"
#include "hlistout.h"
#include <iostream>

void shipout(halfword p)
{
	if (eqtb[5297].int_ > 0)
	{
		printnl(338); //
		println();
		print(828); //Completed box being shipped out
	}
	if (termoffset > maxprintline-9)
		println();
	else 
		if (termoffset > 0 || fileoffset > 0)
		printchar(' ');
	printchar('[');
	int j = 9;
	while (eqtb[5318+j].int_ == 0 && j > 0)
		j--;
	for (int k = 0; k <= j; k++)
	{
		printint(eqtb[5318+k].int_);
		if (k < j)
			printchar('.');
	}
	std::cout << std::flush;
	if (eqtb[5297].int_ > 0)
	{
		printchar(']');
		begindiagnostic();
		showbox(p);
		enddiagnostic(true);
	}
	if (mem[p+3].int_ > 1073741823 || mem[p+2].int_ > 1073741823 || mem[p+3].int_+mem[p+2].int_+eqtb[5849].int_ > 1073741823 || mem[p+1].int_+eqtb[5848].int_ > 1073741823)
	{
		if (interaction == 3)
			printnl(262); //! 
		print(832); //Huge page cannot be shipped out
		helpptr = 2;
		helpline[1] = 833; //The page just created is more than 18 feet tall or
		helpline[0] = 834; //more than 18 feet wide, so I suspect something went wrong.
		error();
		if (eqtb[5297].int_ <= 0)
		{
			begindiagnostic;
			printnl(835);
			showbox(p);
			enddiagnostic(true);
		}
		if (eqtb[5297].int_ <= 0)
		printchar(']');
		deadcycles = 0;
		std::cout << std::flush;
		flushnodelist(p);
		return;
	}
	if (mem[p+3].int_+mem[p+2].int_+eqtb[5849].int_ > maxv)
		maxv = mem[p+3].int_+mem[p+2].int_+eqtb[5849].int_;
	if (mem[p+1].int_+eqtb[5848].int_ > maxh)
		maxh = mem[p+1].int_+eqtb[5848].int_;
	dvih = 0;
	dviv = 0;
	curh = eqtb[5848].int_;
	dvif = 0;
	if (outputfilename == 0)
	{
		if (jobname == 0)
			openlogfile();
		packjobname(793); //.dvi
		while (!bopenout(dvifile))
			promptfilename(794, 793); //file name for output//.dvi
		outputfilename = bmakenamestring(dvifile);
	}
	if (totalpages == 0)
	{
		dvibuf[dviptr++] = 247;
		if (dviptr == dvilimit)
			dviswap();
		dvibuf[dviptr++] = 2;
		if (dviptr == dvilimit)
			dviswap();
		dvifour(25400000);
		dvifour(473628672);
		preparemag();
		dvifour(eqtb[5280].int_);
		oldsetting = selector;
		selector = 21;
		print(826); // TeX output 
		printint(eqtb[5286].int_);
		printchar('.');
		printtwo(eqtb[5285].int_);
		printchar('.');
		printtwo(eqtb[5284].int_);
		printchar(':');
		printtwo(eqtb[5283].int_/60);
		printtwo(eqtb[5283].int_%60);
		selector = oldsetting;
		dvibuf[dviptr++] = poolptr-strstart[strptr];
		if (dviptr == dvilimit)
			dviswap();
		for (auto s = strstart[strptr]; s < poolptr; s++)
		{
			dvibuf[dviptr++] = strpool[s];
			if (dviptr == dvilimit)
				dviswap();
		}
		poolptr = strstart[strptr];
	}
	auto pageloc = dvioffset+dviptr;
	dvibuf[dviptr++] = 139;
	if (dviptr == dvilimit)
		dviswap();
	for (auto k = 0; k < 10; k++)
		dvifour(eqtb[5318+k].int_);
	dvifour(lastbop);
	lastbop = pageloc;
	curv = mem[p+3].int_+eqtb[5849].int_;
	tempptr = p;
	if (type(p) == 1)
		vlistout();
	else
		hlistout();
	dvibuf[dviptr++] = 140;
	if (dviptr == dvilimit)
		dviswap();
	totalpages++;
	curs = -1;
	if (eqtb[5297].int_ <= 0)
		printchar(']');
	deadcycles = 0;
	std::cout << std::flush;
	flushnodelist(p);
}
