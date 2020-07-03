#include "shipout.h"
#include "impression.h"
#include "error.h"
#include "fichier.h"
#include "preparemag.h"
#include "bmakenamestring.h"
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

static int h_offset(void) { return dimen_par(h_offset_code); }
static int v_offset(void) { return dimen_par(v_offset_code); }
static int tracing_output(void) { return int_par(tracing_output_code); }

static void ensure_dvi_open(void)
{
	if (outputfilename == "")
	{
		if (jobname == "")
			openlogfile();
		packjobname(".dvi");
		while (!bopenout(dvifile))
			promptfilename("file name for output", ".dvi");
		outputfilename = bmakenamestring(dvifile); 
	}
}

void shipout(halfword p)
{
	if (tracing_output())
		printnl("\nCompleted box being shipped out"+std::string(termoffset > maxprintline-9 ? "\n" : termoffset > 0 || fileoffset > 0 ? " " : ""));
	print("[");
	int j = 9;
	while (count(j) == 0 && j > 0)
		j--;
	for (int k = 0; k <= j; k++)
	{
		print(std::to_string(count(k)));
		if (k < j)
			print(".");
	}
	std::cout << std::flush;
	if (tracing_output() > 0)
	{
		print("]");
		begindiagnostic();
		print(showbox(p));
		print(enddiagnostic(true));
	}
	if (height(p) > max_dimen || depth(p) > max_dimen 
	 || height(p)+depth(p)+v_offset() > max_dimen 
	 || width(p)+h_offset() > max_dimen)
	{
		print_err("Huge page cannot be shipped out");
		helpptr = 2;
		helpline[1] = txt("The page just created is more than 18 feet tall or");
		helpline[0] = txt("more than 18 feet wide, so I suspect something went wrong.");
		error();
		if (tracing_output() <= 0)
		{
			begindiagnostic();
			printnl("The following box has been deleted:"+showbox(p));
			print(enddiagnostic(true));
		}
		if (tracing_output() <= 0)
		print("]");
		deadcycles = 0;
		std::cout << std::flush;
		flushnodelist(p);
		return;
	}
	if (height(p)+depth(p)+v_offset() > maxv)
		maxv = height(p)+depth(p)+v_offset();
	if (width(p)+h_offset() > maxh)
		maxh = width(p)+h_offset();
	dvih = 0;
	dviv = 0;
	curh = h_offset();
	dvif = null_font;
	ensure_dvi_open();
	if (totalpages == 0)
	{
		dvi_out(pre);
		dvi_out(id_byte);
		dvifour(25400000);
		dvifour(473628672);
		preparemag();
		dvifour(mag());
		oldsetting = selector;
		selector = new_string;
		print(" TeX output "+std::to_string(year())+"."+twoDigits(month())+"."+twoDigits(day())+":"+twoDigits(time()/60)+twoDigits(time()%60));
		selector = oldsetting;
		dvi_out(cur_length());
		for (auto s = strstart[strptr]; s < poolptr; s++)
			dvi_out(strpool[s]);
		poolptr = strstart[strptr];
	}
	auto pageloc = dvioffset+dviptr;
	dvi_out(bop);
	for (auto k = 0; k < 10; k++)
		dvifour(count(k));
	dvifour(lastbop);
	lastbop = pageloc;
	curv = height(p)+v_offset();
	tempptr = p;
	if (type(p) == vlist_node)
		vlistout();
	else
		hlistout();
	dvi_out(eop);
	totalpages++;
	curs = -1;
	if (tracing_output() <= 0)
		print("]");
	deadcycles = 0;
	std::cout << std::flush;
	flushnodelist(p);
}
