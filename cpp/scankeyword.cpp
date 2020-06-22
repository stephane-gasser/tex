#include "scankeyword.h"
#include "getxtoken.h"
#include "getavail.h"
#include "backinput.h"
#include "begintokenlist.h"
#include "flushlist.h"
#include "texte.h"

bool scankeyword(const std::string &t)
{
	halfword p = backup_head;
	link(p) = 0;
	for (size_t k = 0; k < t.size();)
	{
		getxtoken();
		if (curcs == 0 && (curchr == t[k] || curchr == t[k]-'a'+'A'))
		{
			auto q = getavail();
			link(p) = q;
			info(q) = curtok;
			p = q;
			k++;
		}
		else 
			if (curcmd != spacer || p != backup_head)
			{
				backinput();
				if (p != backup_head)
					back_list(link(backup_head));
				return false;
			}
	}
	flushlist(link(backup_head));
	return true;
}
