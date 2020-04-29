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
	logfile << "This is TeX, Version 3.14159265";
	slowprint(formatident);
	print(799); //  
	printint(eqtb[5284].int_);
	printchar(' ');
	char months[] = "JANFEBMARAPRMAYJUNJULAUGSEPOCTNOVDEC";
	for (int k = 3*eqtb[5285].int_-2; k<= 3*eqtb[5285].int_; k++)
		logfile << months[k];
	printchar(' ');
	printint(eqtb[5286].int_);
	printchar(' ');
	printtwo(eqtb[5283].int_/60);
	printchar(':');
	printtwo(eqtb[5283].int_%60);
	inputstack[inputptr] = curinput;
	printnl(797); //**
	int l = inputstack[0].limitfield;
	if (buffer[l] == eqtb[5311].int_)
		l--;
	for (int k = 1; k <= l; k++)
		print(buffer[k]);
	println();
	selector = oldsetting+2;
}
