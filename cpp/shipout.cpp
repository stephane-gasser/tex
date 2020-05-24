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
#include "texte.h"

void shipout(halfword p)
{
	if (int_par(tracing_output_code))
	{
		printnl("");
		println();
		print("Completed box being shipped out");
	}
	if (termoffset > maxprintline-9)
		println();
	else 
		if (termoffset > 0 || fileoffset > 0)
		printchar(' ');
	printchar('[');
	int j = 9;
	while (count(j) == 0 && j > 0)
		j--;
	for (int k = 0; k <= j; k++)
	{
		printint(count(k));
		if (k < j)
			printchar('.');
	}
	std::cout << std::flush;
	if (int_par(tracing_output_code) > 0)
	{
		printchar(']');
		begindiagnostic();
		showbox(p);
		enddiagnostic(true);
	}
	if (height(p) > max_dimen || depth(p) > max_dimen 
	 || height(p)+depth(p)+dimen_par(v_offset_code) > max_dimen 
	 || width(p)+dimen_par(h_offset_code) > max_dimen)
	{
		printnl("! ");
		print("Huge page cannot be shipped out");
		helpptr = 2;
		helpline[1] = txt("The page just created is more than 18 feet tall or");
		helpline[0] = txt("more than 18 feet wide, so I suspect something went wrong.");
		error();
		if (int_par(tracing_output_code) <= 0)
		{
			begindiagnostic;
			printnl("The following box has been deleted:");
			showbox(p);
			enddiagnostic(true);
		}
		if (int_par(tracing_output_code) <= 0)
		printchar(']');
		deadcycles = 0;
		std::cout << std::flush;
		flushnodelist(p);
		return;
	}
	if (height(p)+depth(p)+dimen_par(v_offset_code) > maxv)
		maxv = height(p)+depth(p)+dimen_par(v_offset_code);
	if (width(p)+dimen_par(h_offset_code) > maxh)
		maxh = width(p)+dimen_par(h_offset_code);
	dvih = 0;
	dviv = 0;
	curh = dimen_par(h_offset_code);
	dvif = 0;
	if (outputfilename == 0)
	{
		if (jobname == 0)
			openlogfile();
		packjobname(".dvi");
		while (!bopenout(dvifile))
			promptfilename("file name for output", ".dvi");
		outputfilename = bmakenamestring(dvifile);
	}
	if (totalpages == 0)
	{
		dvibuf[dviptr++] = pre;
		if (dviptr == dvilimit)
			dviswap();
		dvibuf[dviptr++] = id_byte;
		if (dviptr == dvilimit)
			dviswap();
		dvifour(25400000);
		dvifour(473628672);
		preparemag();
		dvifour(int_par(mag_code));
		oldsetting = selector;
		selector = new_string;
		print(" TeX output ");
		printint(int_par(year_code));
		printchar('.');
		printtwo(int_par(month_code));
		printchar('.');
		printtwo(int_par(day_code));
		printchar(':');
		printtwo(int_par(time_code)/60);
		printtwo(int_par(time_code)%60);
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
	dvibuf[dviptr++] = bop;
	if (dviptr == dvilimit)
		dviswap();
	for (auto k = 0; k < 10; k++)
		dvifour(count(k));
	dvifour(lastbop);
	lastbop = pageloc;
	curv = height(p)+dimen_par(v_offset_code);
	tempptr = p;
	if (type(p) == vlist_node)
		vlistout();
	else
		hlistout();
	dvibuf[dviptr++] = eop;
	if (dviptr == dvilimit)
		dviswap();
	totalpages++;
	curs = -1;
	if (int_par(tracing_output_code) <= 0)
		printchar(']');
	deadcycles = 0;
	std::cout << std::flush;
	flushnodelist(p);
}
