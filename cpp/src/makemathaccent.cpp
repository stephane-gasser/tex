#include "makemathaccent.h"
#include "boite.h"
#include "fetch.h"
#include "half.h"
#include "noeud.h"
#include "police.h"

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
		auto w = x->width;
		auto h = x->height;
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
				auto xx = newnoad();
				mem[nucleus(xx)] = mem[nucleus(q)];
				mem[supscr(xx)] = mem[supscr(q)];
				mem[subscr(xx)] = mem[subscr(q)];
				mem[supscr(xx)].hh = twohalves{0, 0};
				mem[subscr(xx)].hh = twohalves{0, 0};
				math_type(nucleus(q)) = sub_mlist;
				info(nucleus(q)) = xx;
				x = cleanbox(nucleus(q), curstyle);
				delta += x->height-h;
				h = x->height;
			}
		auto y = charbox(ft, c);
		y->shift_amount = s+half(w-y->width);
		y->width = 0;
		auto p = new KernNode(-delta);
		p->link = x;
		y->link = p;
		y = vpack(y, 0, additional);
		y->width = x->width;
		if (y->height < h)
		{
			p = new KernNode(h-y->height);
			p->link = y->list_ptr;
			y->list_ptr = p;
			y->height = h;
		}
		info(nucleus(q)) = y->num;
		math_type(nucleus(q)) = sub_box;
	}
}
