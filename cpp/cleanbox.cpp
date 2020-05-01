#include "cleanbox.h"
#include "newnoad.h"
#include "newnullbox.h"
#include "mlisttohlist.h"
#include "hpack.h"
#include "xovern.h"
#include "freenode.h"

halfword cleanbox(halfword p, smallnumber s)
{
	halfword q;
	do
	{
		switch (link(p))
		{
			case 1:
				curmlist = newnoad();
				mem[curmlist+1] = mem[p];
				break;
			case 2:
				q = info(p);
				continue;
				break;
			case 3: 
				curmlist = info(p);
				break;
			default:
				q = newnullbox();
				continue;
		}
		auto savestyle = curstyle;
		curstyle = s;
		mlistpenalties = false;
		mlisttohlist();
		q = link(temp_head);
		curstyle = savestyle;
		if (curstyle < 4)
			cursize = 0;
		else
			cursize = 16*((curstyle-2)/2);
		curmu = xovern(fontinfo[6+parambase[fam_fnt(2+cursize)]].int_, 18);
		break;
	} while (false);
	halfword x;
	if (q >= himemmin || q == 0)
		x = hpack(q, 0, 1);
	else 
		if (link(q) == 0 && type(q) <= 1 && mem[q+4].int_ == 0)
			x = q;
		else
			x = hpack(q, 0, 1);
	q = link(x+5);
	if (q >= himemmin)
	{
		auto r = link(q);
		if (r && link(r) == 0 && r < himemmin && type(r) == 11)
		{
			freenode(r, 2);
			link(q) = 0;
		}
	}
	return x;
}
