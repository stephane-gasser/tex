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
	if (boxcontext < 1073741824)
	{
		if (curbox)
		{
			mem[curbox+4].int_ = boxcontext;
			if (abs(curlist.modefield) == 1)
			{
				appendtovlist(curbox);
				if (adjusttail)
				{
					if (29995 != adjusttail)
					{
						link(curlist.tailfield) = link(29995);
						curlist.tailfield = adjusttail;
					}
					adjusttail = 0;
				}
				if (curlist.modefield > 0)
					buildpage();
			}
			else
			{
				if (abs(curlist.modefield) == 102)
					curlist.auxfield.hh.lh = 1000;
				else
				{
					p = newnoad();
					link(p+1) = 2;
					info(p+1) = curbox;
					curbox = p;
				}
				link(curlist.tailfield) = curbox;
				curlist.tailfield = curbox;
			}
		}
	}
	else 
		if (boxcontext < 1073742336)
			if (boxcontext < 1073742080)
				eqdefine(-1073738146+boxcontext, 119, curbox);
			else
				geqdefine(-1073738402+boxcontext, 119, curbox);
		else 
			if (curbox)
				if (boxcontext > 1073742336)
				{
					do
						getxtoken();
					while (curcmd == 10 || curcmd == 0);
					if ((curcmd == 26 && abs(curlist.modefield) != 1) || (curcmd == 27 && abs(curlist.modefield) == 1))
					{
						appendglue();
						subtype(curlist.tailfield) = boxcontext-1073742237;
						link(curlist.tailfield+1) = curbox;
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
