#include "readtoks.h"
#include "beginfilereading.h"
#include "getavail.h"
#include "terminput.h"
#include "print.h"
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

void readtoks(int n, halfword r)
{
	scannerstatus = 2;
	warningindex = r;
	defref = getavail();
	info(defref) = 0;
	auto p = defref;
	auto q = getavail();
	link(p) = q;
	info(q) = 3584;
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
			if (interaction > 1)
				if (n < 0)
				{
					print(338); //
					terminput();
				}
				else
				{
					println();
					sprintcs(r);
					print('=');
					terminput;
					n = -1;
				}
		else
			fatalerror(753); //*** (cannot \read from terminal in nonstop modes)

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
						if (interaction == 3)
						printnl(262); //! 
						print(754); //File ended within 
						printesc(534); //read
						helpptr = 1;
						helpline[0] = 755; //This \read has unbalanced braces.
						alignstate = 1000000;
						error();
					}
				}
		curinput.limitfield = last;
		if (eqtb[5311].int_ < 0 || eqtb[5311].int_ > 255)
			curinput.limitfield--;
		else
			buffer[curinput.limitfield] = eqtb[5311].int_;
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
