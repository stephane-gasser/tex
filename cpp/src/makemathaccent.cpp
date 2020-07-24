#include "makemathaccent.h"
#include "cleanbox.h"
#include "fetch.h"
#include "charbox.h"
#include "half.h"
#include "noeud.h"
#include "police.h"
#include "vpackage.h"

void makemathaccent(halfword q)
{
	fetch(accent_chr(q));
	if (char_exists(curi))
	{
		auto i = curi;
		auto c = curc;
		auto &ft = fonts[curf];
		scaled s = 0;
		if (math_type(nucleus(q)) == math_char)
		{
			fetch(nucleus(q));
			if (char_tag(curi) == lig_tag)
			{
				int a = ft.lig_kern_start(curi);
				curi = fontinfo[a].qqqq;
				if (skip_byte(curi) > stop_flag)
				{
					a = ft.lig_kern_start(curi);
					curi = fontinfo[a].qqqq;
				}
				while (true)
				{
					if (next_char(curi) == ft.skewchar)
					{
						if (op_byte(curi) >= kern_flag)
							if (skip_byte(curi) <= stop_flag)
								s = ft.char_kern(curi);
						break;
					}
					if (skip_byte(curi) >= stop_flag)
						break;
					a += skip_byte(curi)+1;
					curi = fontinfo[a].qqqq;
				}
			}
		}
		auto x = cleanbox(nucleus(q), cramped_style(curstyle));
		scaled w = width(x);
		scaled h = height(x);
		while (true)
		{
			if (char_tag(i) != list_tag)
				break;
			halfword y = rem_byte(i);
			i = ft.char_info(y);
			if (skip_byte(i) <= 0)
				break;
			if (ft.char_width(y) > w)
				break;
			c = y;
		}
		scaled delta = std::min(h, ft.x_height());
		if (math_type(supscr(q)) || math_type(subscr(q)))
			if (math_type(nucleus(q)) == math_char)
			{
				flushnodelist(x);
				x = newnoad();
				mem[nucleus(x)] = mem[nucleus(q)];
				mem[supscr(x)] = mem[supscr(q)];
				mem[subscr(x)] = mem[subscr(q)];
				mem[supscr(x)].hh = twohalves{0, 0};
				mem[subscr(x)].hh = twohalves{0, 0};
				math_type(nucleus(q)) = sub_mlist;
				info(nucleus(q)) = x;
				x = cleanbox(nucleus(q), curstyle);
				delta += height(x)-h;
				h = height(x);
			}
		auto y = charbox(ft, c);
		shift_amount(y) = s+half(w-width(y));
		width(y) = 0;
		auto p = newkern(-delta);
		link(p) = x;
		link(y) = p;
		y = vpack(y, 0, additional);
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
