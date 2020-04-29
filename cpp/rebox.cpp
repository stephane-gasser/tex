#include "rebox.h"
#include "hpack.h"
#include "newkern.h"
#include "freenode.h"
#include "newglue.h"

halfword rebox(halfword b, scaled w)
{
	if (mem[b+1].int_ != w && link(b+5))
	{
		if (type(b) == 1)
			b = hpack(b, 0, 1);
		halfword p = link(b+5);
		if (p >= himemmin && link(p) == 0)
		{
			internalfontnumber f = type(p);
			scaled v = fontinfo[widthbase[f]+fontinfo[charbase[f]+subtype(p)].qqqq.b0].int_;
			if (v != mem[b+1].int_)
				link(p) = newkern(mem[b+1].int_-v);
		}
		freenode(b, 7);
		b = newglue(12);
		link(b) = p;
		while (link(p))
			p = link(p);
		link(p) = newglue(12);
		return hpack(b, w, 0);
	}
	mem[b+1].int_ = w;
	return b;
}

