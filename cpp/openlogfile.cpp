#include "openlogfile.h"
#include "packjobname.h"
#include "aopenout.h"
#include "promptfilename.h"
#include "amakenamestring.h"
#include "slowprint.h"
#include "print.h"
#include "printint.h"
#include "printchar.h"
#include "printtwo.h"
#include "printnl.h"
#include "println.h"
#include "texte.h"

void openlogfile(void)
{
	auto oldsetting = selector;
	if (jobname == 0)
		jobname = txt("texput");
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
	print("  ");
	printint(int_par(day_code));
	printchar(' ');
	char months[] = "JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC";
	for (int k = 3*int_par(month_code)-2; k<= 3*int_par(month_code); k++)
		logfile << months[k];
	printchar(' ');
	printint(int_par(year_code));
	printchar(' ');
	printtwo(int_par(time_code)/60);
	printchar(':');
	printtwo(int_par(time_code)%60);
	inputstack[inputptr] = curinput;
	printnl("**");
	int l = inputstack[0].limitfield;
	if (buffer[l] == int_par(end_line_char_code))
		l--;
	for (int k = 1; k <= l; k++)
		printchar(buffer[k]);
	println();
	selector = oldsetting+2;
}
