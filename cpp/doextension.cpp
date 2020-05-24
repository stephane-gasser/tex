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
#include "texte.h"

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
			open_name(tail) = txt(curname);
			open_area(tail) = txt(curarea);
			open_ext(tail) = txt(curext);
			break;
		case 1:
			k = curcs;
			newwritewhatsit(2);
			curcs = k;
			p = scantoks(false, false);
			link(tail+1) = defref;
			break;
		case 2:
			newwritewhatsit(2);
			link(tail+1) = 0;
			break;
		case 3:
			newwhatsit(3, 2);
			info(tail+1) = 0;
			p = scantoks(false, true);
			link(tail+1) = defref;
			break;
		case 4:
			getxtoken();
			if (curcmd == extension && curchr <= 2)
			{
				p = tail;
				doextension();
				outwhat(tail);
				flushnodelist(tail);
				tail = p;
				link(p) = 0;
			}
			else
				backinput();
			break;
		case 5:
			if (abs(mode) != hmode)
				reportillegalcase();
			else
			{
				newwhatsit(4, 2);
				scanint();
				if (curval <= 0)
					clang = 0;
				else 
					if (curval > 255)
						clang = 0;
					else
						clang = curval;
				link(tail+1) = clang;
				type(tail+1) = normmin(int_par(left_hyphen_min_code));
				subtype(tail+1) = normmin(int_par(right_hyphen_min_code));
			}
			break;
		default: 
			confusion("ext1");
	}
}
