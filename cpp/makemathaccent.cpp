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
	if (skip_byte(curi) > 0)
	{
		auto i = curi;
		auto c = curc;
		auto f = curf;
		scaled s = 0;
		if (link(q+1) == 1)
		{
			fetch(q+1);
			if (char_tag(curi) == lig_tag)
			{
				int a = lig_kern_start(curf, curi);
				curi = fontinfo[a].qqqq;
				if (skip_byte(curi) > stop_flag)
				{
					a = lig_kern_start(curf, curi);
					curi = fontinfo[a].qqqq;
				}
				while (true)
				{
					if (next_char(curi) == skewchar[curf])
					{
						if (op_byte(curi) >= kern_flag)
							if (skip_byte(curi) <= stop_flag)
								s = char_kern(curf, curi);
						break;
					}
					if (skip_byte(curi) >= stop_flag)
						break;
					a += skip_byte(curi)+1;
					curi = fontinfo[a].qqqq;
				}
			}
		}
		auto x = cleanbox(q+1, 2*(curstyle/2)+1);
		scaled w = width(x);
		scaled h = height(x);
		while (true)
		{
			if (char_tag(i) != list_tag)
				break;
			halfword y = rem_byte(i);
			i = char_info(f, y);
			if (skip_byte(i) <= 0)
				break;
			if (char_width(f, i) > w)
				break;
			c = y;
		}
		scaled delta = std::min(h,  param(x_height_code, f));
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
				delta += height(x)-h;
				h = height(x);
			}
		auto y = charbox(f, c);
		shift_amount(y) = s+half(w-width(y));
		width(y) = 0;
		auto p = newkern(-delta);
		link(p) = x;
		link(y) = p;
		y = vpackage(y, 0, 1, max_dimen);
		width(y) = width(x);
		if (height(y) < h)
		{
			p = newkern(h-height(y));
			link(p) = list_ptr(y);
			list_ptr(y) = p;
			height(y) = h;
		}
		info(nucleus(q)) = y;
		math_type(nucleus(q)) = sub_box;
	}
}
