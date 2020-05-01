#include "doextension.h"
#include "newwritewhatsit.h"
#include "scanoptionalequals.h"
#include "scanfilename.h"
#include "scantoks.h"
#include "newwhatsit.h"
#include "getxtoken.h"
#include "outwhat.h"
#include "flushnodelist.h"
#include "backinput.h"
#include "scanint.h"
#include "reportillegalcase.h"
#include "normmin.h"
#include "confusion.h"

void doextension(void)
{
	int i, j, k;
	halfword p, q, r;
	switch (curchr)
	{
		case 0:
			newwritewhatsit(3);
			scanoptionalequals();
			scanfilename();
			link(curlist.tailfield+1) = curname;
			info(curlist.tailfield+2) = curarea;
			link(curlist.tailfield+2) = curext;
			break;
		case 1:
			k = curcs;
			newwritewhatsit(2);
			curcs = k;
			p = scantoks(false, false);
			link(curlist.tailfield+1) = defref;
			break;
		case 2:
			newwritewhatsit(2);
			link(curlist.tailfield+1) = 0;
			break;
		case 3:
			newwhatsit(3, 2);
			info(curlist.tailfield+1) = 0;
			p = scantoks(false, true);
			link(curlist.tailfield+1) = defref;
			break;
		case 4:
			getxtoken();
			if (curcmd == 59 && curchr <= 2)
			{
				p = curlist.tailfield;
				doextension();
				outwhat(curlist.tailfield);
				flushnodelist(curlist.tailfield);
				curlist.tailfield = p;
				link(p) = 0;
			}
			else
				backinput();
			break;
		case 5:
			if (abs(curlist.modefield) != 102)
				reportillegalcase();
			else
			{
				newwhatsit(4, 2);
				scanint();
				if (curval <= 0)
					curlist.auxfield.hh.rh = 0;
				else 
					if (curval > 255)
						curlist.auxfield.hh.rh = 0;
					else
						curlist.auxfield.hh.rh = curval;
				link(curlist.tailfield+1) = curlist.auxfield.hh.rh;
				type(curlist.tailfield+1) = normmin(int_par(left_hyphen_min_code));
				subtype(curlist.tailfield+1) = normmin(int_par(right_hyphen_min_code));
			}
			break;
		default: 
			confusion(1290); //ext1
	}
}
