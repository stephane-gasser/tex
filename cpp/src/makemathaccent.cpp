#include "makemathaccent.h"
#include "boite.h"
#include "fetch.h"
#include "half.h"
#include "noeud.h"
#include "police.h"

void makemathaccent(halfword q)
{
	AccentNoad *Q;
	Q->num = q;
	auto [ft, curc] = fetch(Q->accent_chr);
	if (char_exists(ft.char_info(curc)))
	{
		auto c = curc;
		scaled s = 0;
		Noad *Q;
		Q->num = q;
		if (Q->nucleus.math_type == math_char)
		{
			std::tie(ft, curc) = fetch(Q->nucleus);
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
		if (Q->supscr.math_type || Q->subscr.math_type)
			if (Q->nucleus.math_type == math_char)
			{
				flushnodelist(x);
				auto n = new Noad;
				n->nucleus = Q->nucleus;
				n->supscr = Q->supscr;
				n->subscr = Q->subscr;
				Q->subscr.math_type = 0;
				// fam/character = 0
				Q->supscr.math_type = 0;
				// fam/character = 0
				//mem[supscr(q)].hh = twohalves{0, 0};
				//mem[subscr(q)].hh = twohalves{0, 0};
				Q->nucleus.math_type = sub_mlist;
				Q->nucleus.info = n;
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
		Q->nucleus.math_type = sub_box;
		Q->nucleus.info = y;
	}
}
