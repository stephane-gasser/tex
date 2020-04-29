#include "scankeyword.h"
#include "getxtoken.h"
#include "getavail.h"
#include "backinput.h"
#include "begintokenlist.h"
#include "flushlist.h"

bool scankeyword(strnumber s)
{
	halfword p = 29987;
	link(p) = 0;
	auto k = strstart[s];
	while (k < strstart[s+1])
	{
		getxtoken();
		if (curcs == 0 && (curchr == strpool[k] || curchr == strpool[k]-32))
		{
			auto q = getavail();
			link(p) = q;
			info(q) = curtok;
			p = q;
			k++;
		}
		else 
			if (curcmd != 10 || p != 29987)
			{
				backinput();
				if (p != 29987)
					begintokenlist(link(29987), 3);
				return false;
			}
	}
	flushlist(link(29987));
	return true;
}
