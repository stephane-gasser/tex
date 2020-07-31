#include "cleanbox.h"
#include "noeud.h"
#include "mlisttohlist.h"
#include "hpack.h"
#include "xovern.h"
#include "police.h"

halfword cleanbox(halfword p, smallnumber s)
{
	LinkedNode *q;
	do
	{
		switch (link(p))
		{
			case 1:
				curmlist = newnoad();
				mem[nucleus(curmlist)] = mem[p];
				break;
			case 2:
				q->num = info(p);
				continue;
				break;
			case 3: 
				curmlist = info(p);
				break;
			default:
				q->num = newnullbox();
				continue;
		}
		auto savestyle = curstyle;
		curstyle = s;
		mlistpenalties = false;
		mlisttohlist();
		q = temp_head->link;
		curstyle = savestyle;
		if (curstyle < 4)
			cursize = 0;
		else
			cursize = 16*((curstyle-2)/2);
		curmu = xovern(math_quad(cursize), 18);
		break;
	} while (false);
	LinkedNode *x;
	if (q->is_char_node() || q == nullptr)
		x->num = hpack(q->num, 0, additional);
	else 
		if (q->link == nullptr && q->type <= vlist_node && shift_amount(q->num) == 0)
			x = q;
		else
			x->num = hpack(q->num, 0, additional);
	q->num = list_ptr(x->num);
	if (q->is_char_node())
	{
		auto r = q->link;
		if (r && r->link == nullptr && !r->is_char_node() && r->type == kern_node)
		{
			freenode(r->num, 2);
			q->link = 0;
		}
	}
	return x->num;
}
