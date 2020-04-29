#include "makemathaccent.h"
#include "cleanbox.h"
#include "fetch.h"
#include "flushnodelist.h"
#include "charbox.h"
#include "half.h"
#include "newkern.h"
#include "newnoad.h"
#include "vpackage.h"

void makemathaccent(halfword q)
{
	fetch(q+4);
	if (curi.b0 > 0)
	{
		auto i = curi;
		auto c = curc;
		auto f = curf;
		scaled s = 0;
		if (link(q+1) == 1)
		{
			fetch(q+1);
			if (curi.b2%4 == 1)
			{
				int a = ligkernbase[curf]+curi.b3;
				curi = fontinfo[a].qqqq;
				if (curi.b0 > 128)
				{
					a = ligkernbase[curf]+256*curi.b2+curi.b3+32768-256*128;
					curi = fontinfo[a].qqqq;
				}
				while (true)
				{
					if (curi.b1-0 == skewchar[curf])
					{
						if (curi.b2 >= 128)
							if (curi.b0 <= 128)
								s = fontinfo[kernbase[curf]+256 * curi.b2+curi.b3].int_;
						break;
					}
					if (curi.b0 >= 128)
						break;
					a += curi.b0+1;
					curi = fontinfo[a].qqqq;
				}
			}
		}
		auto x = cleanbox(q+1, 2*(curstyle/2)+1);
		scaled w = mem[x+1].int_;
		scaled h = mem[x+3].int_;
		while (true)
		{
			if (i.b2%4 != 2)
				break;
			halfword y = i.b3;
			i = fontinfo[charbase[f]+y].qqqq;
			if (i.b0 <= 0)
				break;
			if (fontinfo[widthbase[f]+i.b0].int_ > w)
				break;
			c = y;
		}
		scaled delta;
		if (h < fontinfo[5+parambase[f]].int_)
			delta = h;
		else
			delta = fontinfo[5+parambase[f]].int_;
		if (link(q+2) || link(q+3))
			if (link(q+1) == 1)
			{
				flushnodelist(x);
				x = newnoad();
				mem[x+1] = mem[q+1];
				mem[x+2] = mem[q+2];
				mem[x+3] = mem[q+3];
				mem[q+2].hh = emptyfield;
				mem[q+3].hh = emptyfield;
				link(q+1) = 3;
				info(q+1) = x;
				x = cleanbox(q+1, curstyle);
				delta += mem[x+3].int_-h;
				h = mem[x+3].int_;
			}
		auto y = charbox(f, c);
		mem[y+4].int_ = s+half(w-mem[y+1].int_);
		mem[y+1].int_ = 0;
		auto p = newkern(-delta);
		link(p) = x;
		link(y) = p;
		y = vpackage(y, 0, 1, 1073741823);
		mem[y+1].int_ = mem[x+1].int_;
		if (mem[y+3].int_ < h)
		{
			p = newkern(h-mem[y+3].int_);
			link(p) = link(y+5);
			link(y+5) = p;
			mem[y+3].int_ = h;
		}
		info(q+1) = y;
		link(q+1) = 2;
	}
}
