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

void openlogfile(void)
{
	auto oldsetting = selector;
	if (jobname == 0)
		jobname = 795; //texput
	packjobname(796); //.log
	while (!aopenout(logfile))
	{
		selector = 17;
		promptfilename(798, 796); // transcript file name//.log
	}
	logname = amakenamestring(logfile);
	selector = 18;
	logopened = true;
	logfile << banner;
	slowprint(formatident);
	print(799); //  
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
	printnl(797); //**
	int l = inputstack[0].limitfield;
	if (buffer[l] == int_par(end_line_char_code))
		l--;
	for (int k = 1; k <= l; k++)
		print(buffer[k]);
	println();
	selector = oldsetting+2;
}
