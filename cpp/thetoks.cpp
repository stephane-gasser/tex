#include "thetoks.h"
#include "getxtoken.h"
#include "scansomethinginternal.h"
#include "getavail.h"
#include "printint.h"
#include "printscaled.h"
#include "print.h"
#include "printspec.h"
#include "deleteglueref.h"
#include "strtoks.h"

halfword thetoks(void)
{
	getxtoken();
	scansomethinginternal(5, false);
	if (curvallevel >= 4)
	{
		halfword p = temp_head;
		link(p) = 0;
		if (curvallevel == 4)
		{
			auto q = getavail();
			link(p) = q;
			info(q) = cs_token_flag+curval;
			p = q;
		}
		else 
			if (curval)
			{
				auto r = link(curval);
				while (r)
				{
					auto q = avail;
					if (q == 0)
						q = getavail();
					else
					{
						avail = link(q);
						link(q) = 0;
					}
					link(p) = q;
					info(q) = info(r);
					p = q;
					r = link(r);
				}
			}
		return p;
	}
	oldsetting = selector;
	selector = new_string;
	auto b = poolptr;
	switch (curvallevel)
	{
		case 0: 
			printint(curval);
			break;
		case 1:
			printscaled(curval);
			print(397); //pt
			break;
		case 2:
			printspec(curval, 397); //pt
			deleteglueref(curval);
			break;
		case 3:
			printspec(curval, 337); //mu
			deleteglueref(curval);
	}
	selector = oldsetting;
	return strtoks(b);
}
