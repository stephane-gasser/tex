#include "openlogfile.h"
#include "packjobname.h"
#include "fichier.h"
#include "promptfilename.h"
#include "amakenamestring.h"
#include "impression.h"
#include "texte.h"

void openlogfile(void)
{
	auto oldsetting = selector;
	if (jobname == "") 
		jobname = "texput";
	packjobname(".log");
	while (!aopenout(logfile))
	{
		selector = term_only;
		promptfilename(" transcript file name", ".log");
	}
	logname = amakenamestring(logfile);
	selector = log_only;
	logopened = true;
	logfile << banner;
	slowprint(formatident);
	print("  "+std::to_string(day())+" ");
	char months[] = "JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC";
	for (int k = 3*month()-2; k<= 3*month(); k++)
		logfile << months[k];
	print(" "+std::to_string(year())+" ");
	printtwo(time()/60);
	print(":");
	printtwo(time()%60);
	inputstack[inputptr] = curinput;
	printnl("**");
	int l = inputstack[0].limitfield;
	if (buffer[l] == end_line_char())
		l--;
	print(std::string(buffer+1, buffer+l+1));
	println();
	selector = oldsetting+2;
}
