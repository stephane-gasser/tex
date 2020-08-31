#include "shipout.h"
#include "impression.h"
#include "erreur.h"
#include "fichier.h"
#include "preparemag.h"
#include "bmakenamestring.h"
#include "noeud.h"
#include "openlogfile.h"
#include "packjobname.h"
#include "promptfilename.h"
#include "dvi.h"
#include "vlistout.h"
#include "hlistout.h"
#include <iostream>
#include "equivalent.h"

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

void shipout(BoxNode *p)
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
		diagnostic(showbox(p)+"\n");
	}
	if (p->height > max_dimen || p->depth > max_dimen 
	 || p->height+p->depth+v_offset() > max_dimen 
	 || p->width+h_offset() > max_dimen)
	{
		error("Huge page cannot be shipped out", "The page just created is more than 18 feet tall or\nmore than 18 feet wide, so I suspect something went wrong.");
		if (tracing_output() <= 0)
		{
			diagnostic("\rThe following box has been deleted:"+showbox(p)+"\n");
			print("]");
		}
		deadcycles = 0;
		std::cout << std::flush;
		flushnodelist(p);
		return;
	}
	if (p->height+p->depth+v_offset() > maxv)
		maxv = p->height+p->depth+v_offset();
	if (p->width+h_offset() > maxh)
		maxh = p->width+h_offset();
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
		dvi_out(cur_length());
		for (char c: " TeX output "+std::to_string(year())+"."+twoDigits(month())+"."+twoDigits(day())+":"+twoDigits(time()/60)+twoDigits(time()%60))
			dvi_out(c);
	}
	auto pageloc = dvioffset+dviptr;
	dvi_out(bop);
	for (auto k = 0; k < 10; k++)
		dvifour(count(k));
	dvifour(lastbop);
	lastbop = pageloc;
	curv = p->height+v_offset();
	if (p->type == vlist_node)
		vlistout(p);
	else
		hlistout(p);
	dvi_out(eop);
	totalpages++;
	curs = -1;
	if (tracing_output() <= 0)
		print("]");
	deadcycles = 0;
	std::cout << std::flush;
	flushnodelist(p);
}
