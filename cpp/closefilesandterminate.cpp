#include "closefilesandterminate.h"
#include "aclose.h"
#include "dviswap.h"
#include "printnl.h"
#include "dvifour.h"
#include "preparemag.h"
#include "dvifontdef.h"
#include "writedvi.h"
#include "slowprint.h"
#include "print.h"
#include "printint.h"
#include "printchar.h"
#include "bclose.h"

void closefilesandterminate(void)
{
	int k; 
	for (k = 0; k <= 15; k++)
		if (writeopen[k])
			aclose(writefile[k]);
	while (curs > -1)
	{
		if (curs > 0)
		{
			dvibuf[dviptr++] = pop;
			if (dviptr == dvilimit)
				dviswap();
		}
		else
		{
			dvibuf[dviptr++] = eop;
			if (dviptr == dvilimit)
				dviswap();
			totalpages++;
		}
		curs--;
	}
	if (totalpages == 0)
		printnl("No pages of output.");
	else
	{
		dvibuf[dviptr++] = post;
		if (dviptr == dvilimit)
			dviswap();
		dvifour(lastbop);
		lastbop = dvioffset+dviptr-5;
		dvifour(25400000);
		dvifour(473628672);
		preparemag();
		dvifour(int_par(mag_code));
		dvifour(maxv);
		dvifour(maxh);
		dvibuf[dviptr++] = maxpush/0x1'00;
		if (dviptr == dvilimit)
			dviswap();
		dvibuf[dviptr++] = maxpush%0x1'00;
		if (dviptr == dvilimit)
			dviswap();
		dvibuf[dviptr++] = (totalpages/0x1'00)%0x1'00;
		if (dviptr == dvilimit)
			dviswap();
		dvibuf[dviptr++] = totalpages%0x1'00;
		if (dviptr == dvilimit)
			dviswap();
		for (;fontptr > 0; fontptr--)
			if (fontused[fontptr])
				dvifontdef(fontptr);
		dvibuf[dviptr++] = post_post;
		if (dviptr == dvilimit)
			dviswap();
		dvifour(lastbop);
		dvibuf[dviptr++] = id_byte;
		if (dviptr == dvilimit)
			dviswap();
		for (k = 4+(dvibufsize-dviptr)%4; k > 0; k--)
		{
			dvibuf[dviptr++] = 223;
			if (dviptr == dvilimit)
				dviswap();
		}
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
