#include "closefilesandterminate.h"
#include "impression.h"
#include "dvi.h"
#include "preparemag.h"
#include "fichier.h"
#include "police.h"

void closefilesandterminate(void)
{
	for (int k = 0; k <= 15; k++)
		if (writeopen[k])
			aclose(writefile[k]);
	while (curs > -1)
	{
		if (curs > 0)
			dvi_out(pop);
		else
		{
			dvi_out(eop);
			totalpages++;
		}
		curs--;
	}
	if (totalpages == 0)
		printnl("No pages of output.");
	else
	{
		dvi_out(post);
		dvifour(lastbop);
		lastbop = dvioffset+dviptr-5;
		dvifour(25400000);
		dvifour(473628672);
		preparemag();
		dvifour(mag());
		dvifour(maxv);
		dvifour(maxh);
		dvi_out(maxpush>>8);
		dvi_out(maxpush%(1<<8));
		dvi_out((totalpages>>8)%(1<<8));
		dvi_out(totalpages%(1<<8));
		for (; fonts.size(); fonts.pop_back())
			if (fonts.back().used)
				dvifontdef(fonts.size()+1);
		dvi_out(post_post);
		dvifour(lastbop);
		dvi_out(id_byte);
		for (int k = 4+(dvibufsize-dviptr)%4; k > 0; k--)
			dvi_out(223);
		if (dvilimit == halfbuf)
			writedvi(halfbuf, dvibufsize);
		if (dviptr > 0)
			writedvi(0, dviptr);
		printnl("Output written on "+outputfilename+"// ("+std::to_string(totalpages)+" page"+(totalpages == 1 ? "" : "s")+", "+std::to_string(dvioffset+dviptr)+" bytes).");
		bclose(dvifile);
	}
	if (logopened)
	{
		logfile << "\n";
		aclose(logfile);
		selector -= 2;
		if (selector == term_only)
			printnl("Transcript written on "+logname+".");
	}
}
