#include "openlogfile.h"
#include "fichier.h"
#include "impression.h"
#include "equivalent.h"

void openlogfile(void)
{
	auto oldsetting = selector;
	if (jobname == "") 
		jobname = "texput";
	while (!aopenout(logfile, logname = packjobname(".log")))
	{
		selector = term_only;
		promptfilename(" transcript file name", ".log");
	}
	selector = log_only;
	logopened = true;
	logfile << banner;
	slowprint(formatident);
	print("  "+std::to_string(day())+" ");
	char months[] = "JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC";
	for (int k = 3*month()-2; k <= 3*month(); k++)
		logfile << months[k];
	print(" "+std::to_string(year())+" "+twoDigits(time()/60)+":"+twoDigits(time()%60));
	inputstack.back() = curinput;
	printnl("**");
	int l = inputstack[0].limitfield;
	if (buffer[l] == end_line_char())
		l--;
	print(std::string(buffer+1, buffer+l+1)+"\n");
	selector = oldsetting+2;
}
