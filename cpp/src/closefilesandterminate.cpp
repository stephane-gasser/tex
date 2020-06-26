#include "closefilesandterminate.h"
#include "impression.h"
#include "dvifour.h"
#include "preparemag.h"
#include "dvifontdef.h"
#include "writedvi.h"
#include "dviswap.h"
#include "fichier.h"

void closefilesandterminate(void)
{
	int k; 
	for (k = 0; k <= 15; k++)
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
		dvi_out(maxpush/0x1'00);
		dvi_out(maxpush%0x1'00);
		dvi_out((totalpages/0x1'00)%0x1'00);
		dvi_out(totalpages%0x1'00);
		for (;fontptr > 0; fontptr--)
			if (fontused[fontptr])
				dvifontdef(fontptr);
		dvi_out(post_post);
		dvifour(lastbop);
		dvi_out(id_byte);
		for (k = 4+(dvibufsize-dviptr)%4; k > 0; k--)
			dvi_out(223);
		if (dvilimit == halfbuf)
			writedvi(halfbuf, dvibufsize-1);
		if (dviptr > 0)
			writedvi(0, dviptr-1);
		printnl("Output written on ");
		slowprint(outputfilename);
		print("// (");
		printint(totalpages);
		print(" page");
		if (totalpages != 1)
			printchar('s');
		print(", "); 
		printint(dvioffset+dviptr);
		print(" bytes).");
		bclose(dvifile);
	}
	if (logopened)
	{
		logfile << "\n";
		aclose(logfile);
		selector -= 2;
		if (selector == term_only)
		{
			printnl("Transcript written on ");
			slowprint(logname);
			printchar('.');
		}
	}
}
