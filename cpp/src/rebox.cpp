#include "rebox.h"
#include "hpack.h"
#include "noeud.h"

halfword rebox(halfword b, scaled w)
{
	if (width(b) != w && list_ptr(b))
	{
		if (type(b) == vlist_node)
			b = hpack(b, 0, additional);
		halfword p = list_ptr(b);
		if (is_char_node(p) && link(p) == 0)
		{
			internalfontnumber f = type(p);
			scaled v = char_width(f, char_info(f, subtype(p)));
			if (v != width(b))
				link(p) = newkern(width(b)-v);
		}
		freenode(b, box_node_size);
		b = newglue(ss_glue);
		link(b) = p;
		while (link(p))
			p = link(p);
		link(p) = newglue(ss_glue);
		return hpack(b, w, exactly);
	}
	width(b) = w;
	return b;
}

