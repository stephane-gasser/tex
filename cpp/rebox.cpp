#include "rebox.h"
#include "hpack.h"
#include "newkern.h"
#include "freenode.h"
#include "newglue.h"

halfword rebox(halfword b, scaled w)
{
	if (width(b) != w && list_ptr(b))
	{
		if (type(b) == vlist_node)
			b = hpack(b, 0, 1);
		halfword p = list_ptr(b);
		if (p >= himemmin && link(p) == 0)
		{
			internalfontnumber f = type(p);
			scaled v = char_width(f, char_info(f, subtype(p)));
			if (v != width(b))
				link(p) = newkern(width(b)-v);
		}
		freenode(b, 7);
		b = newglue(12);
		link(b) = p;
		while (link(p))
			p = link(p);
		link(p) = newglue(12);
		return hpack(b, w, 0);
	}
	width(b) = w;
	return b;
}

