#include "vardelimiter.h"
#include "noeud.h"
#include "boite.h"
#include "police.h"
#include "half.h"

static quarterword ext_top(fourquarters q) { return q.b0; } //!< |top| piece in a recipe
static quarterword ext_mid(fourquarters q) { return q.b1; } //!< |mid| pie1ce in a recipe
static quarterword ext_bot(fourquarters q) { return q.b2; } //!< |bot| piece in a recipe
static quarterword ext_rep(fourquarters q) { return q.b3; } //!< |rep| piece in a recipe
static int null_delimiter_space(void) { return dimen_par(null_delimiter_space_code); }

static void stackintobox(BoxNode *b, const Font &ft, quarterword c)
{
	auto p = charbox(ft, c);
	p->link = b->list_ptr;
	b->list_ptr = p;
	b->height = p->height;
}

BoxNode *vardelimiter(halfword d, smallnumber s, scaled v)
{
	internalfontnumber f = null_font;
	scaled w = 0;
	bool largeattempt = false;
	smallnumber z = small_fam(d);
	quarterword x = small_char(d);
	bool label40 = false;
	fourquarters q;
	while (true)
	{
		if (z || x)
		{
			z += s+16;
			do
			{
				z -= 16;
				g = fam_fnt(z);
				if (g != null_font)
				{
					auto y = x;
					auto &ft = fonts[g];
					if (y >= ft.bc && y <= ft.ec)
					{
						bool label22;
						do 
						{
							label22 = false;
							q = ft.char_info(y);
							if (char_exists(q))
							{
								if (ft.char_tag(y) == ext_tag)
								{
									f = g;
									c = y;
									label40 = true;
									break;
								}
								scaled u = ft.char_height(y)+ft.char_depth(y);
								if (u > w)
								{
									f = g;
									c = y;
									w = u;
									if (u >= v)
									{
										label40 = true;
										break;
									}
								}
								if (ft.char_tag(y) == list_tag)
								{
									y = rem_byte(q);
									label22 = true;
								}
							}
						} while (label22);
						if (label40)
							break;
					}
				}
			} while (z >= 16);
		}
		if (!largeattempt && !label40)
		{
			largeattempt = true;
			z = large_fam(d);
			x = large_char(d);
		}
	}
	BoxNode *b;
	if (auto &ft = fonts[f]; f != null_font)
		if (char_tag(q) == ext_tag)
		{
			b = new BoxNode;
			b->type = vlist_node;
			fourquarters r = Font::infos(ft.extenbase+rem_byte(q));
			c = ext_rep(r);
			auto u = ft.heightplusdepth(c);
			w = 0;
			//q = ft.char_info(c);
			b->width = ft.char_width(c)+ft.char_italic(c);
			c = ext_bot(r);
			if (c)
				w += ft.heightplusdepth(c);
			c = ext_mid(r);
			if (c)
				w += ft.heightplusdepth(c);
			c = ext_top(r);
			if (c)
				w += ft.heightplusdepth(c);
			int n = 0;
			if (u > 0)
				while (w < v)
				{
					w += u;
					n++;
					if (ext_mid(r))
						w += u;
				}
			c = ext_bot(r);
			if (c)
				stackintobox(b, ft, c);
			c = ext_rep(r);
			for (int m = 1; m <= n; m++)
				stackintobox(b, ft, c);
			c = ext_mid(r);
			if (c)
			{
				stackintobox(b, ft, c);
				c = ext_rep(r);
				for (int m = 1; m <= n; m++)
					stackintobox(b, ft, c);
			}
			c = ext_top(r);
			if (c)
				stackintobox(b, ft, c);
			b->depth = w-b->height;
		}
		else
			b = charbox(ft, c);
	else
	{
		b = new BoxNode;
		b->width = null_delimiter_space();
	}
	b->shift_amount = half(b->height-b->depth)-axis_height(s);
	return b;
}
