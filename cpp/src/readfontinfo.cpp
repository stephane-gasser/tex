#include "readfontinfo.h"
#include "impression.h"
#include "erreur.h"
#include "packfilename.h"
#include "fichier.h"
#include "xnoverd.h"
#include "texte.h"

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
		charbase[f] = fmemptr-bc;
		widthbase[f] = charbase[f]+ec+1;
		heightbase[f] = widthbase[f]+nw;
		depthbase[f] = heightbase[f]+nh;
		italicbase[f] = depthbase[f]+nd;
		ligkernbase[f] = italicbase[f]+ni;
		kernbase[f] = ligkernbase[f]+nl-0x80'00;
		extenbase[f] = kernbase[f]+0x80'00+nk;
		parambase[f] = extenbase[f]+ne;
		if (lh < 2)
			throw 1;
		eightbits a, b, c, d;
		fontcheck[f] = store_four_quarters(a, b, c, d);
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
		fontdsize[f] = z;
		if (s != -1000)
			if (s >= 0)
				z = s;
			else
				z = xnoverd(z, -s, 1000);
		fontsize[f] = z;
		for (int k = fmemptr; k < widthbase[f]; k++)
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
		for (int k = widthbase[f]; k < ligkernbase[f]; k++)
			fontinfo[k].int_ = store_scaled(z, beta, k, alpha);
		if (fontinfo[widthbase[f]].int_ || fontinfo[heightbase[f]].int_ || fontinfo[depthbase[f]].int_ || fontinfo[italicbase[f]].int_)
			throw 1;
		int bchlabel = 0x7F'FF;
		bchar = 256;
		if (nl > 0)
		{
			for (int k = ligkernbase[f]; k < kernbase[f]+0x80'00; k++)
			{
				fontinfo[k].qqqq = store_four_quarters(a, b, c, d);
				if (a > 128)
				{
					if (0x1'00*c+d >= nl)
						throw 1;
					if (a == 255 && k == ligkernbase[f])
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
					if (a < 128 && k-ligkernbase[f]+a+1 >= nl)
						throw 1;
				}
			}
			if (a == 255)
				bchlabel = c<<8+d;
		}
		for (int k = kernbase[f]+0x80'00; k < extenbase[f]; k++)
			fontinfo[k].int_ = store_scaled(z, beta, k, alpha);
		for (int k = extenbase[f]; k < parambase[f]-1; k++)
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
			fontparams[f] = np;
		else
			fontparams[f] = 7;
		hyphenchar[f] = default_hyphen_char();
		skewchar[f] = default_skew_char();
		if (bchlabel < nl)
			bcharlabel[f] = bchlabel+ligkernbase[f];
		else
			bcharlabel[f] = 0;
		fontbchar[f] = bchar;
		fontfalsebchar[f] = bchar;
		if (bchar <= ec && bchar >= bc && skip_byte(char_info(f, bchar)) > 0)
			fontfalsebchar[f] = non_char;
		fontname[f] = nom;
		fontarea[f] = aire;
		fontbc[f] = bc;
		fontec[f] = ec;
		fontglue[f] = 0;
		parambase[f]--;
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
