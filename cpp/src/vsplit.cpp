#include "vsplit.h"
#include "impression.h"
#include "erreur.h"
#include "vertbreak.h"
#include "lecture.h"
#include "prunepagetop.h"
#include "noeud.h"
#include "boite.h"

BoxNode* vsplit(eightbits n, scaled h)
{
	auto v = box[n];
	if (split_first_mark)
	{
		deletetokenref(split_first_mark);
		split_first_mark = nullptr;
		deletetokenref(split_bot_mark);
		split_bot_mark = nullptr;
	}
	if (v == nullptr)
		return 0;
	if (v->type != vlist_node)
	{
		error(esc("vsplit")+" needs a "+esc("vbox"), "The box you are trying to split is an \\hbox.\nI can't split such a box, so I'll leave it alone.");
		return 0;
	}
	LinkedNode *q;
	q->num = vertbreak(v->list_ptr->num, h, split_max_depth());
	auto p = v->list_ptr;
	if (p == q)
		v->list_ptr = nullptr;
	else
		while (true)
		{
			if (p->type == mark_node) //4
			{
				auto P = dynamic_cast<MarkNode*>(p);
				if (split_first_mark == nullptr)
				{
					split_bot_mark = split_first_mark = P->mark_ptr;
					P->mark_ptr->token_ref_count += 2;
				}
				else
				{
					deletetokenref(split_bot_mark);
					split_bot_mark = P->mark_ptr;
					P->mark_ptr->token_ref_count++;
				}
			}
			if (p->link == q)
			{
				p->link = nullptr;
				break;
			}
			next(p);
		}
	q = prunepagetop(q);
	p = v->list_ptr;
	delete v;
	box[n] = q == nullptr ? nullptr : vpack(q, 0, additional);
	return vpackage(p, h, exactly, split_max_depth());
}
