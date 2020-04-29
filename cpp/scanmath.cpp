#include "scanmath.h"
#include "getxtoken.h"
#include "xtoken.h"
#include "backinput.h"
#include "scancharnum.h"
#include "scanfifteenbitint.h"
#include "scantwentysevenbitint.h"
#include "backinput.h"
#include "scanleftbrace.h"
#include "pushmath.h"

void scanmath(halfword p)
{
	do
		getxtoken();
	while (curcmd == 10 || curcmd == 0);
	bool label21;
	do
	{
		label21 = false;
		int c;
		switch (curcmd)
		{
			case 11:
			case 12:
			case 68:
				c = eqtb[5007+curchr].hh.rh;
				if (c == 32768)
				{
					curcs = curchr+1;
					curcmd = eqtb[curcs].hh.b0;
					curchr = eqtb[curcs].hh.rh;
					xtoken();
					backinput();
					do
						getxtoken();
					while (curcmd == 10 || curcmd == 0);
					label21 = true;
					continue;
				}
				break;
			case 16:
				scancharnum();
				curchr = curval;
				curcmd = 68;
				label21 = true;
				continue;
			case 17:
				scanfifteenbitint();
				c = curval;
				break;
			case 69: 
				c = curchr;
				break;
			case 15:
				scantwentysevenbitint();
				c = curval/4096;
				break;
			default:
				backinput();
				scanleftbrace();
				savestack[saveptr++].int_ = p;
				pushmath(9);
				return;
		}
	} while (label21);
	link(p) = 1;
	subtype(p) = c%256;
	if (c >= 28672 && eqtb[5307].int_ >= 0 && eqtb[5307].int_ < 16)
		type(p) = eqtb[5307].int_;
	else
		type(p) = (c/256)%16;
}
