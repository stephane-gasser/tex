#include "vardelimiter.h"
#include "noeud.h"
#include "heightplusdepth.h"
#include "stackintobox.h"
#include "charbox.h"
#include "half.h"

static quarterword ext_top(fourquarters q) { return q.b0; } //!< |top| piece in a recipe
static quarterword ext_mid(fourquarters q) { return q.b1; } //!< |mid| pie1ce in a recipe
static quarterword ext_bot(fourquarters q) { return q.b2; } //!< |bot| piece in a recipe
static quarterword ext_rep(fourquarters q) { return q.b3; } //!< |rep| piece in a recipe

static int null_delimiter_space(void) { return dimen_par(null_delimiter_space_code); }

halfword vardelimiter(halfword d, smallnumber s, scaled v)
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
					if (y >= fontbc[g] && y <= fontec[g])
					{
						bool label22;
						do 
						{
							label22 = false;
							q = char_info(g, y);
							if (char_exists(q))
							{
								if (char_tag(q) == ext_tag)
								{
									f = g;
									c = y;
									label40 = true;
									break;
								}
								scaled u = char_height(g, q)+char_depth(g, q);
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
								if (char_tag(q) == list_tag)
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
	halfword b;
	if (f != null_font)
		if (char_tag(q) == ext_tag)
		{
			b = newnullbox();
			type(b) = vlist_node;
			fourquarters r = fontinfo[extenbase[f]+rem_byte(q)].qqqq;
			c = ext_rep(r);
			auto u = heightplusdepth(f, c);
			w = 0;
			q = char_info(f, c);
			width(b) = char_width(f, q)+char_italic(f, q);
			c = ext_bot(r);
			if (c)
				w += heightplusdepth(f, c);
			c = ext_mid(r);
			if (c)
				w += heightplusdepth(f, c);
			c = ext_top(r);
			if (c)
				w += heightplusdepth(f, c);
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
				stackintobox(b, f, c);
			c = ext_rep(r);
			for (int m = 1; m <= n; m++)
				stackintobox(b, f, c);
			c = ext_mid(r);
			if (c)
			{
				stackintobox(b, f, c);
				c = ext_rep(r);
				for (int m = 1; m <= n; m++)
					stackintobox(b, f, c);
			}
			c = ext_top(r);
			if (c)
				stackintobox(b, f, c);
			depth(b) = w-height(b);
		}
		else
			b = charbox(f, c);
	else
	{
		b = newnullbox();
		width(b) = null_delimiter_space();
	}
	shift_amount(b) = half(height(b)-depth(b))-axis_height(s);
	return b;
}
