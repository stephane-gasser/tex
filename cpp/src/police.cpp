#include "police.h"
#include "readfontinfo.h"
#include "impression.h"
#include "erreur.h"
#include "packfilename.h"
#include "fichier.h"
#include "xnoverd.h"
#include "texte.h"
#include "lecture.h"
#include "deleteglueref.h"

int char_width(internalfontnumber f, fourquarters i) { return fontinfo[fonts[f].widthbase+i.b0].int_; }
int char_height(internalfontnumber f, fourquarters i) { return fontinfo[fonts[f].heightbase+i.b1/16].int_; }
int& param(smallnumber p, internalfontnumber f) { return fontinfo[p+fonts[f].parambase].int_; }
fourquarters char_info(internalfontnumber f, smallnumber q) { return fontinfo[fonts[f].charbase+q].qqqq; }
int char_italic(internalfontnumber f, fourquarters q) { return fontinfo[fonts[f].italicbase+q.b2/4].int_; }
int char_depth(internalfontnumber f, fourquarters q) { return fontinfo[fonts[f].depthbase+q.b1%16].int_; }
int lig_kern_start(internalfontnumber f, fourquarters i) { return fonts[f].ligkernbase+rem_byte(i); }
int lig_kern_restart(internalfontnumber f, fourquarters i) { return fonts[f].ligkernbase+256*op_byte(i)+rem_byte(i); }
int char_kern(internalfontnumber f, fourquarters i) { return fontinfo[fonts[f].kernbase+256*op_byte(i)+rem_byte(i)].int_; }
int& space(internalfontnumber f) { return param(space_code, f); }
int& space_stretch(internalfontnumber f) { return param(space_stretch_code, f); }
int& space_shrink(internalfontnumber f) { return param(space_shrink_code, f); }
int& x_height(internalfontnumber f) { return param(x_height_code, f); }
int& quad(internalfontnumber f) { return param(quad_code, f); }
int default_rule_thickness(void) { return mathex(8); }
int mathex(smallnumber p) { return param(p, fam_fnt(3+cursize)); }
int mathsy(smallnumber p, smallnumber c) { return param(p, fam_fnt(2+c)); }
int axis_height(smallnumber c) { return mathsy(22, c); }
int math_x_height(smallnumber c) { return mathsy(5, c); }
int math_quad(smallnumber c) { return mathsy(6, c); }
int char_tag(fourquarters q) { return q.b2%4; }
bool char_exists(fourquarters q) { return q.b0 > 0; }
quarterword skip_byte(fourquarters q) { return q.b0; }
quarterword next_char(fourquarters q) { return q.b1; }
quarterword op_byte(fourquarters q) { return q.b2; }
quarterword rem_byte(fourquarters q) { return q.b3; }

constexpr char TEX_font_area[] = "TeXfonts:";

static int default_skew_char(void) { return int_par(default_skew_char_code); }

template<class T> static void read_sixteen(T &z)
{
	z = tfmfile.get();
	if (z > 127)
		throw 1;
	z <<= 8;
	z += tfmfile.get();
}

static fourquarters store_four_quarters(eightbits &a, eightbits &b, eightbits &c, eightbits &d)
{
	fourquarters qw;
	qw.b0 = a = tfmfile.get();
	qw.b1 = b = tfmfile.get();
	qw.b2 = c = tfmfile.get();
	qw.b3 = d = tfmfile.get();
	return qw; 
}

static void check_byte_range(halfword p, halfword bc, halfword ec)
{
	if (p < bc || p > ec)
		throw 1;
}

static int current_character_being_worked_on(int k, int bc)
{
	return k+bc-fmemptr;
}

static int store_scaled(scaled z, int beta, int k, int alpha)
{
	eightbits a, b, c, d;
	a = tfmfile.get();
	b = tfmfile.get();
	c = tfmfile.get();
	d = tfmfile.get();
	scaled sw = (((d*z)>>8+c*z)>>8+b*z)/beta;
	if (a == 0)
		return sw;
	if (a == 255)
	return sw-alpha;
	throw 1;
}

static void check_existence(halfword p, halfword bc, halfword ec, internalfontnumber f)
{
	check_byte_range(p, bc, ec);
	if (skip_byte(char_info(f, p)) <= 0)
		throw 1;
}

internalfontnumber readfontinfo(halfword u, const std::string &nom, const std::string &aire, scaled s)
{
	bool fileopened = false;
	try
	{
		if (aire == "")
			packfilename(nom, TEX_font_area, ".tfm");
		else
			packfilename(nom, aire, ".tfm");
		if (!bopenin(tfmfile))
			throw 1;
		fileopened = true;
		halfword lf, lh, bc, ec;
		read_sixteen(lf);
		read_sixteen(lh);
		read_sixteen(bc);
		read_sixteen(ec);
		if (bc > ec+1 || ec > 255)
			throw 1;
		if (bc > 255)
			bc = 1;
		ec = 0;
		halfword nw, nh, nd, ni, nl, nk, ne, np;
		read_sixteen(nw);
		read_sixteen(nh);
		read_sixteen(nd);
		read_sixteen(ni);
		read_sixteen(nl);
		read_sixteen(nk);
		read_sixteen(ne);
		read_sixteen(np);
		if (lf != 6+lh+(ec-bc+1)+nw+nh+nd+ni+nl+nk+ne+np || nw == 0 || nh == 0 || nd == 0 || ni == 0)
			throw 1;
		lf -= 6+lh;
		if (np < 7)
			lf += 7-np;
		if (fontptr == fontmax || fmemptr+lf > fontmemsize)
			throw 0;
		f = fontptr+1;
		fonts[f].charbase = fmemptr-bc;
		fonts[f].widthbase = fonts[f].charbase+ec+1;
		fonts[f].heightbase = fonts[f].widthbase+nw;
		fonts[f].depthbase = fonts[f].heightbase+nh;
		fonts[f].italicbase = fonts[f].depthbase+nd;
		fonts[f].ligkernbase = fonts[f].italicbase+ni;
		fonts[f].kernbase = fonts[f].ligkernbase+nl-0x80'00;
		fonts[f].extenbase = fonts[f].kernbase+0x80'00+nk;
		fonts[f].parambase = fonts[f].extenbase+ne;
		if (lh < 2)
			throw 1;
		eightbits a, b, c, d;
		fonts[f].check = store_four_quarters(a, b, c, d);
		scaled z;
		read_sixteen(z);
		z = z*0x1'00+tfmfile.get();
		z = z*16+tfmfile.get()/16;
		if (z < unity)
			throw 1;
		while (lh > 2)
		{
			store_four_quarters(a, b, c, d);
			lh--;
		}
		fonts[f].dsize = z;
		if (s != -1000)
			if (s >= 0)
				z = s;
			else
				z = xnoverd(z, -s, 1000);
		fonts[f].size = z;
		for (int k = fmemptr; k < fonts[f].widthbase; k++)
		{
			fontinfo[k].qqqq = store_four_quarters(a, b, c, d);
			if (a >= nw || b/16 >= nh || b%16 >= nd || c/4 >= ni)
				throw 1;
			switch (c%4)
			{
				case lig_tag: 
					if (d >= nl)
						throw 1;
					break;
				case ext_tag: 
					if (d >= ne)
						throw 1;
					break;
				case list_tag:
					check_byte_range(d, bc, ec);
					while (d < current_character_being_worked_on(k, bc))
					{
						auto qw = char_info(f, d);
						if (qw.b2%4 != 2)
							break;
						d = qw.b3;
						if (d == current_character_being_worked_on(k, bc))
							throw 1;
					}
			}
		}
		int alpha = 16;
		while (z >= 8388608)
		{
			z /= 2;
			alpha *= 2;
		}
		int beta = 0x1'00/alpha;
		alpha *= z;
		for (int k = fonts[f].widthbase; k < fonts[f].ligkernbase; k++)
			fontinfo[k].int_ = store_scaled(z, beta, k, alpha);
		if (fontinfo[fonts[f].widthbase].int_ || fontinfo[fonts[f].heightbase].int_ || fontinfo[fonts[f].depthbase].int_ || fontinfo[fonts[f].italicbase].int_)
			throw 1;
		int bchlabel = 0x7F'FF;
		bchar = 256;
		if (nl > 0)
		{
			for (int k = fonts[f].ligkernbase; k < fonts[f].kernbase+0x80'00; k++)
			{
				fontinfo[k].qqqq = store_four_quarters(a, b, c, d);
				if (a > 128)
				{
					if (0x1'00*c+d >= nl)
						throw 1;
					if (a == 255 && k == fonts[f].ligkernbase)
						bchar = b;
				}
				else
				{
					if (b != bchar)
						check_existence(b, bc, ec, f);
					if (c < 128)
						check_existence(d, bc, ec, f);
					else 
						if ((c-0x80)<<8+d >= nk)
							throw 1;
					if (a < 128 && k-fonts[f].ligkernbase+a+1 >= nl)
						throw 1;
				}
			}
			if (a == 255)
				bchlabel = c<<8+d;
		}
		for (int k = fonts[f].kernbase+0x80'00; k < fonts[f].extenbase; k++)
			fontinfo[k].int_ = store_scaled(z, beta, k, alpha);
		for (int k = fonts[f].extenbase; k < fonts[f].parambase-1; k++)
		{
			fontinfo[k].qqqq = store_four_quarters(a, b, c, d);
			if (a)
				check_existence(a, bc, ec, f);
			if (b)
				check_existence(b, bc, ec, f);
			if (c)
				check_existence(c, bc, ec, f);
			check_existence(d, bc, ec, f);
		}
		for (int k = 1; k <= np; k++)
			if (k == 1)
			{
				scaled sw = tfmfile.get();
				if (sw > 127)
					sw -= 0x1'00;
				sw = sw<<8+tfmfile.get();
				sw = sw<<8+tfmfile.get();
				param(0, f) = sw<<4+tfmfile.get()>>4;
			}
			else
				param(k-1, f) = store_scaled(z, beta, k, alpha);
		if (tfmfile.eof())
			throw 1;
		for (int k = np+1; k <= 7; k++)
			param(k-1, f) = 0;
		if (np >= 7)
			fonts[f].params = np;
		else
			fonts[f].params = 7;
		fonts[f].hyphenchar = default_hyphen_char();
		fonts[f].skewchar = default_skew_char();
		if (bchlabel < nl)
			fonts[f].bcharlabel = bchlabel+fonts[f].ligkernbase;
		else
			fonts[f].bcharlabel = 0;
		fonts[f].bchar = bchar;
		fonts[f].falsebchar = bchar;
		if (bchar <= ec && bchar >= bc && skip_byte(char_info(f, bchar)) > 0)
			fonts[f].falsebchar = non_char;
		fonts[f].name = nom;
		fonts[f].area = aire;
		fonts[f].bc = bc;
		fonts[f].ec = ec;
		fonts[f].glue = 0;
		fonts[f].parambase--;
		fmemptr += lf;
		fontptr = f;
		if (fileopened)
			bclose(tfmfile);
		return f;
	}
	catch (int e)
	{
		if (e == 1)
			error("Font "+scs(u)+"="+asFilename(nom, aire, "")+(s >= 0 ? " at "+asScaled(s)+"pt" : s == -1000 ? "" : " scaled "+std::to_string(-s))+(fileopened ? " not loadable: Bad metric (TFM) file" : " not loadable: Metric (TFM) file not found"), "I wasn't able to read the size data for this font,\nso I will ignore the font specification.\n[Wizards can fix TFM files using TFtoPL/PLtoTF.]\nYou might try inserting a different font spec;\ne.g., type `I\\font<same font id>=<substitute font name>'.");
		else
			error("Font "+scs(u)+"="+asFilename(nom, aire, "")+(s >= 0 ? " at "+asScaled(s)+"pt" : s == -1000 ? "" : " scaled "+std::to_string(-s))+" not loaded: Not enough room left", "I'm afraid I won't be able to make use of this font,\nbecause my memory for character-size data is too small.\nIf you're really stuck, ask a wizard to enlarge me.\nOr maybe try `I\\font<same font id>=<name of loaded font>'.");
		if (fileopened)
			bclose(tfmfile);
	}
	return null_font;
}

[[nodiscard]] int findfontdimen(bool writing)
{
	int n = scanint();
	internalfontnumber f = scanfontident();
	int val = fmemptr;
	if (n > 0)
	{
		if (writing && n <= 4 && n >= 2 && fonts[f].glue)
		{
			deleteglueref(fonts[f].glue);
			fonts[f].glue = 0;
		}
		if (n > fonts[f].params)
		{
			if (f >= fontptr)
			{
				do
				{
					if (fmemptr == fontmemsize)
						overflow("font memory", fontmemsize);
					fontinfo[fmemptr++].int_ = 0;
					fonts[f].params++;
				} while (n != fonts[f].params);
				val = fmemptr-1;
			}
		}
		else
			val = n+fonts[f].parambase;
	}
	if (val == fmemptr)
		error("Font "+esc(TXT(hash[font_id_base+f].rh))+" has only "+std::to_string(fonts[f].params)+" fontdimen parameters", "To increase the number of font parameters, you must\nuse \\fontdimen immediately after the \\font is loaded.");
	return val;
}
