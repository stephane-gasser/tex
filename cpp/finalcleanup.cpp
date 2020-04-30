#include "finalcleanup.h"
#include "openlogfile.h"
#include "endtokenlist.h"
#include "endfilereading.h"
#include "print.h"
#include "printesc.h"
#include "printnl.h"
#include "printint.h"
#include "printchar.h"
#include "printcmdchr.h"
#include "freenode.h"
#include "deletetokenref.h"
#include "deleteglueref.h"
#include "storefmtfile.h"

void finalcleanup(void)
{
	smallnumber c = curchr;
	if (jobname == 0)
		openlogfile();
	while (inputptr > 0)
		if (curinput.statefield == 0)
			endtokenlist();
		else
		endfilereading();
	while (openparens > 0)
	{
		print(1275); // )
		openparens--;
	}
	if (curlevel > 1)
	{
		printnl('(');
		printesc(1276); //end occurred 
		print(1277); //inside a group at level 
		printint(curlevel-1);
		printchar(')');
	}
	while (condptr)
	{
		printnl('(');
		printesc(1276); //end occurred 
		print(1278); //when 
		printcmdchr(105, curif);
		if (ifline)
		{
			print(1279); // on line 
			printint(ifline);
		}
		print(1280); // was incomplete)
		ifline = mem[condptr+1].int_;
		curif = subtype(condptr);
		tempptr = condptr;
		condptr = link(condptr);
		freenode(tempptr, 2);
	}
	if (history && (history == 1 || interaction < 3) && selector == 19)
	{
		selector = 17;
		printnl(1281); //(see the transcript file for additional information)
		selector = 19;
	}
	if (c == 1)
	{
		for (c = 0; c <= 4; c++)
		if (curmark[c])
			deletetokenref(curmark[c]);
		if (lastglue != 65535)
			deleteglueref(lastglue);
		storefmtfile();
		return;
	}
}
