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
	auto [ft, curc] = fetch(accent_chr(q));
	if (char_exists(ft.char_info(curc)))
	{
		auto c = curc;
		scaled s = 0;
		if (math_type(nucleus(q)) == math_char)
		{
			std::tie(ft, curc) = fetch(nucleus(q));
			if (char_tag(ft.char_info(curc)) == lig_tag)
			{
				int a = ft.lig_kern_start(ft.char_info(curc));
				if (skip_byte(Font::infos(a)) > stop_flag)
					a = ft.lig_kern_start(Font::infos(a));
				while (true)
				{
					if (next_char(Font::infos(a)) == ft.skewchar)
					{
						if (op_byte(Font::infos(a)) >= kern_flag)
							if (skip_byte(Font::infos(a)) <= stop_flag)
								s = ft.char_kern(Font::infos(a));
						break;
					}
					if (skip_byte(Font::infos(a)) >= stop_flag)
						break;
					a += skip_byte(Font::infos(a))+1;
				}
			}
		}
		auto x = cleanbox(nucleus(q), cramped_style(curstyle));
		scaled w = width(x);
		scaled h = height(x);
		while (true)
		{
			if (char_tag(ft.char_info(c)) != list_tag)
				break;
			halfword y = rem_byte(ft.char_info(c));
			if (skip_byte(ft.char_info(y)) <= 0)
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
		auto p = new KernNode(-delta);
		p->link->num = x;
		link(y) = p->num;
		y = vpack(y, 0, additional);
		width(y) = width(x);
		if (height(y) < h)
		{
			p = new KernNode(h-height(y));
			p->link->num = list_ptr(y);
			list_ptr(y) = p->num;
			height(y) = h;
		}
		info(nucleus(q)) = y;
		math_type(nucleus(q)) = sub_box;
	}
}
