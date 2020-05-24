#include "scankeyword.h"
#include "getxtoken.h"
#include "getavail.h"
#include "backinput.h"
#include "begintokenlist.h"
#include "flushlist.h"
#include "texte.h"

bool scankeyword(strnumber s)
{
	halfword p = backup_head;
	link(p) = 0;
	auto k = strstart[s];
	while (k < strstart[s+1])
	{
		getxtoken();
		if (curcs == 0 && (curchr == strpool[k] || curchr == strpool[k]-'a'+'A'))
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
					begintokenlist(link(backup_head), 3);
				return false;
			}
	}
	flushlist(link(backup_head));
	return true;
}

bool scankeyword(const std::string &t)
{
	halfword p = backup_head;
	link(p) = 0;
	strnumber s = txt(t);
	auto k = strstart[s];
	while (k < strstart[s+1])
	{
		getxtoken();
		if (curcs == 0 && (curchr == strpool[k] || curchr == strpool[k]-'a'+'A'))
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
					begintokenlist(link(backup_head), 3);
				return false;
			}
	}
	flushlist(link(backup_head));
	return true;
}
