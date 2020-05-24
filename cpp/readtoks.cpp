#include "readtoks.h"
#include "beginfilereading.h"
#include "getavail.h"
#include "terminput.h"
#include "print.h"
#include "printchar.h"
#include "println.h"
#include "sprintcs.h"
#include "print.h"
#include "fatalerror.h"
#include "inputln.h"
#include "aclose.h"
#include "runaway.h"
#include "printnl.h"
#include "printesc.h"
#include "gettoken.h"
#include "error.h"
#include "endfilereading.h"
#include "texte.h"

void readtoks(int n, halfword r)
{
	scannerstatus = 2;
	warningindex = r;
	defref = getavail();
	info(defref) = 0;
	auto p = defref;
	auto q = getavail();
	link(p) = q;
	info(q) = 0x0E'00; //cmd=end_match/comment/stop ?
	p = q;
	smallnumber m;
	if (n < 0 || n > 15)
		m = 16;
	else
		m = n;
	auto s = alignstate;
	alignstate = 1000000;
	do
	{
		beginfilereading();
		curinput.namefield = m+1;
		if (readopen[m] == 2)
			if (interaction > nonstop_mode)
				if (n < 0)
				{
					print("");
					terminput();
				}
				else
				{
					println();
					sprintcs(r);
					printchar('=');
					terminput;
					n = -1;
				}
		else
			fatalerror("*** (cannot \read from terminal in nonstop modes)");

		else 
			if (readopen[m] == 1)
				if (inputln(readfile[m], false))
					readopen[m] = 0;
				else
				{
					aclose(readfile[m]);
					readopen[m] = 2;
				}

			else
				if (!inputln(readfile[m], true))
				{
					aclose(readfile[m]);
					readopen[m] = 2;
					if (alignstate != 1000000)
					{
						runaway();
						printnl("! ");
						print("File ended within ");
						printesc("read");
						helpptr = 1;
						helpline[0] = txt("This \\read has unbalanced braces.");
						alignstate = 1000000;
						error();
					}
				}
		curinput.limitfield = last;
		if (int_par(end_line_char_code) < 0 || int_par(end_line_char_code) > 255)
			curinput.limitfield--;
		else
			buffer[curinput.limitfield] = int_par(end_line_char_code);
		First = curinput.limitfield+1;
		curinput.locfield = curinput.startfield;
		curinput.statefield = 33;
		while (true)
		{
			gettoken();
			if (curtok == 0)
				break;
			if (alignstate < 1000000)
			{
				do
					gettoken();
				while (curtok);
				alignstate = 1000000;
				break;
			}
			auto q = getavail();
			link(p) = q;
			info(q) = curtok;
			p = q;
		}
		endfilereading();
	} while (alignstate != 1000000);
	curval = defref;
	scannerstatus = 0;
	alignstate = s;
}
