#include "rebox.h"
#include "hpack.h"
#include "noeud.h"
#include "police.h"

BoxNode* rebox(BoxNode *b, scaled w)
{
	if (b->width != w && b->list_ptr)
	{
		if (b->type == vlist_node)
			b->num = hpack(b->num, 0, additional);
		auto p = b->list_ptr;
		if (p->is_char_node() && p->link == nullptr)
		{
			auto P = dynamic_cast<CharNode*>(p);
			scaled v = P->font.char_width(P->character);
			if (v != b->width)
				p->link = new KernNode(b->width-v);
		}
		delete b;
		auto g = new GlueNode(ss_glue);
		g->link = p;
		while (p->link)
			p = p->link;
		p->link = new GlueNode(ss_glue);
		b->num = hpack(g->num, w, exactly);
		return b;
	}
	b->width = w;
	return b;
}

