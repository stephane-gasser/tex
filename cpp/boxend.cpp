#include "boxend.h"
#include "appendtovlist.h"
#include "buildpage.h"
#include "newnoad.h"
#include "eqdefine.h"
#include "geqdefine.h"
#include "getxtoken.h"
#include "appendglue.h"
#include "printnl.h"
#include "print.h"
#include "backerror.h"
#include "flushnodelist.h"
#include "shipout.h"

void boxend(int boxcontext)
{
	halfword p;
	if (boxcontext < 0x40'00'00'00)
	{
		if (curbox)
		{
			mem[curbox+4].int_ = boxcontext;
			if (abs(mode) == 1)
			{
				appendtovlist(curbox);
				if (adjusttail)
				{
					if (adjust_head != adjusttail)
						tail_append(adjust_head);
					adjusttail = 0;
				}
				if (mode > 0)
					buildpage();
			}
			else
			{
				if (abs(mode) == 102)
					space_factor = 1000;
				else
				{
					p = newnoad();
					link(p+1) = 2;
					info(p+1) = curbox;
					curbox = p;
				}
				tail_append(curbox);
			}
		}
	}
	else 
		if (boxcontext < 0x40'00'02'00)
			if (boxcontext < 0x40'00'01'00)
				eqdefine(boxcontext-0x40'00'00'00+box_base, 119, curbox);
			else
				geqdefine(boxcontext-0x40'00'01'00+box_base, 119, curbox);
		else 
			if (curbox)
				if (boxcontext > 0x40'00'02'00)
				{
					do
						getxtoken();
					while (curcmd == spacer || curcmd == escape);
					if ((curcmd == hskip && abs(mode) != vmode) || (curcmd == vskip && abs(mode) == vmode))
					{
						appendglue();
						subtype(tail) = boxcontext-0x40'00'02'00+99;
						link(tail+1) = curbox;
					}
					else
					{
						if (interaction == 3)
							printnl(262); //! 
						print(1065); //Leaders not followed by proper glue
						helpptr = 3;
						helpline[2] = 1066; //You should say `\leaders <box or rule><hskip or vskip>'.
						helpline[1] = 1067; //I found the <box or rule>, but there's no suitable
						helpline[0] = 1068; //<hskip or vskip>, so I'm ignoring these leaders.
						backerror();
						flushnodelist(curbox);
					}
				}

	else
	shipout(curbox);
}
