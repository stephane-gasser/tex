#include "rebox.h"
#include "hpack.h"
#include "noeud.h"
#include "police.h"

halfword rebox(halfword b, scaled w)
{
	if (width(b) != w && list_ptr(b))
	{
		if (type(b) == vlist_node)
			b = hpack(b, 0, additional);
		LinkedNode *p;
		p->num = list_ptr(b);
		if (p->is_char_node() && p->link == nullptr)
		{
			scaled v = dynamic_cast<CharNode*>(p)->font.char_width(dynamic_cast<CharNode*>(p)->character);
			if (v != width(b))
				p->link = new KernNode(width(b)-v);
		}
		freenode(b, box_node_size);
		auto g = new GlueNode(ss_glue);
		b = g->num;
		link(b) = p->num;
		while (p->link)
			p = p->link;
		p->link = new GlueNode(ss_glue);
		return hpack(b, w, exactly);
	}
	width(b) = w;
	return b;
}

