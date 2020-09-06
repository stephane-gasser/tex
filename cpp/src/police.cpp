#include "police.h"
#include "equivalent.h"
#include "impression.h"
#include "erreur.h"
#include "fichier.h"
#include "calcul.h"
#include "lecture.h"
#include "cesure.h"
#include "deleteglueref.h"

fourquarters& Font::infos(int k) { return Font::info[k].qqqq; }
quarterword Font::skip_byte(int k) { return infos(k).b0; }
quarterword Font::next_char(int k) { return infos(k).b1; }
quarterword Font::op_byte(int k) { return infos(k).b2; }
quarterword Font::rem_byte(int k) { return infos(k).b3; }

fourquarters Font::char_info(smallnumber q) const { return infos(charbase+q); }
int Font::char_width(smallnumber q) const { return info[widthbase+char_info(q).b0].int_; }
int Font::char_height(smallnumber q) const { return info[heightbase+char_info(q).b1/16].int_; }
int Font::char_depth(smallnumber q) const { return info[depthbase+char_info(q).b1%16].int_; }
scaled Font::heightplusdepth(quarterword c) const { return char_height(c)+char_depth(c); }
int Font::char_italic(smallnumber q) const { return info[italicbase+char_info(q).b2/4].int_; }
int Font::lig_kern_start(fourquarters i) const { return ligkernbase+::rem_byte(i); }
int Font::lig_kern_restart(fourquarters i) const { return ligkernbase+256*::op_byte(i)+::rem_byte(i); }
int Font::char_kern(fourquarters i) const { return info[kernbase+256*::op_byte(i)+::rem_byte(i)].int_; }
int& Font::param(smallnumber p) const { return info[parambase+p].int_; }
int& Font::slant(void) const { return param(slant_code); }
int& Font::extra_space(void) const { return param(extra_space_code); }
int& Font::space(void) const { return param(space_code); }
int& Font::space_stretch(void) const { return param(space_stretch_code); }
int& Font::space_shrink(void) const { return param(space_shrink_code); }
int& Font::x_height(void) const { return param(x_height_code); }
int& Font::quad(void) const { return param(quad_code); }
int Font::char_tag(smallnumber q) { return char_info(q).b2%4; }
bool Font::char_exists(smallnumber q) { return char_info(q).b0 > 0; }

Font& cur_font(void) { return fonts[curFontNum()]; }
int curFontNum(void) { return eqtb_local[cur_font_loc-local_base].int_; }  // index : Font*
int char_tag(fourquarters q) { return q.b2%4; }
bool char_exists(fourquarters q) { return q.b0 > 0; }
quarterword skip_byte(fourquarters q) { return q.b0; }
quarterword next_char(fourquarters q) { return q.b1; }
quarterword op_byte(fourquarters q) { return q.b2; }
quarterword rem_byte(fourquarters q) { return q.b3; }

constexpr char TEX_font_area[] = "TeXfonts:";

static bytefile tfmfile;

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
	return k+bc-Font::info.size()-1;
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

static void check_existence(halfword p, halfword bc, halfword ec, const Font &ft)
{
	check_byte_range(p, bc, ec);
	if (skip_byte(ft.char_info(p)) <= 0)
		throw 1;
}

internalfontnumber readfontinfo(halfword u, const std::string &nom, const std::string &aire, scaled s)
{
	bool fileopened = false;
	try
	{
		if (!bopenin(tfmfile, packfilename(nom, aire == "" ? TEX_font_area : aire, ".tfm")))
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
		if (fonts.size()-1 == fontmax || Font::info.size()-1+lf > fontmemsize)
			throw 0;
		Font ft;
		ft.charbase = Font::info.size()-1-bc;
		ft.widthbase = ft.charbase+ec+1;
		ft.heightbase = ft.widthbase+nw;
		ft.depthbase = ft.heightbase+nh;
		ft.italicbase = ft.depthbase+nd;
		ft.ligkernbase = ft.italicbase+ni;
		ft.kernbase = ft.ligkernbase+nl-0x80'00;
		ft.extenbase = ft.kernbase+0x80'00+nk;
		ft.parambase = ft.extenbase+ne;
		if (lh < 2)
			throw 1;
		eightbits a, b, c, d;
		ft.check = store_four_quarters(a, b, c, d);
		scaled z;
		read_sixteen(z);
		z = (z<<8)+tfmfile.get();
		z = (z<<4)+(tfmfile.get()>>4);
		if (z < unity)
			throw 1;
		while (lh > 2)
		{
			store_four_quarters(a, b, c, d);
			lh--;
		}
		ft.dsize = z;
		if (s != -1000)
			if (s >= 0)
				z = s;
			else
				z = xnoverd(z, -s, 1000);
		ft.size = z;
		for (int k = Font::info.size()-1; k < ft.widthbase; k++)
		{
			Font::infos(k) = store_four_quarters(a, b, c, d);
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
						auto qw = ft.char_info(d);
						if (qw.b2%4 != 2)
							break;
						d = qw.b3;
						if (d == current_character_being_worked_on(k, bc))
							throw 1;
					}
			}
		}
		int alpha = 16;
		while (z >= 1<<23)
		{
			z /= 2;
			alpha *= 2;
		}
		int beta = (1<<8)/alpha;
		alpha *= z;
		for (int k = ft.widthbase; k < ft.ligkernbase; k++)
			Font::info[k].int_ = store_scaled(z, beta, k, alpha);
		if (Font::info[ft.widthbase].int_ || Font::info[ft.heightbase].int_ || Font::info[ft.depthbase].int_ || Font::info[ft.italicbase].int_)
			throw 1;
		int bchlabel = 0x7F'FF;
		bchar = 256;
		if (nl > 0)
		{
			for (int k = ft.ligkernbase; k < ft.kernbase+0x80'00; k++)
			{
				Font::infos(k) = store_four_quarters(a, b, c, d);
				if (a > 128)
				{
					if (0x1'00*c+d >= nl)
						throw 1;
					if (a == 255 && k == ft.ligkernbase)
						bchar = b;
				}
				else
				{
					if (b != bchar)
						check_existence(b, bc, ec, ft);
					if (c < 128)
						check_existence(d, bc, ec, ft);
					else 
						if ((c-0x80)<<8+d >= nk)
							throw 1;
					if (a < 128 && k-ft.ligkernbase+a+1 >= nl)
						throw 1;
				}
			}
			if (a == 255)
				bchlabel = c<<8+d;
		}
		for (int k = ft.kernbase+0x80'00; k < ft.extenbase; k++)
			Font::info[k].int_ = store_scaled(z, beta, k, alpha);
		for (int k = ft.extenbase; k < ft.parambase-1; k++)
		{
			Font::infos(k) = store_four_quarters(a, b, c, d);
			if (a)
				check_existence(a, bc, ec, ft);
			if (b)
				check_existence(b, bc, ec, ft);
			if (c)
				check_existence(c, bc, ec, ft);
			check_existence(d, bc, ec, ft);
		}
		for (int k = 1; k <= np; k++)
			if (k == 1)
			{
				scaled sw = tfmfile.get();
				if (sw >= 1<<8)
					sw -= 1<<8;
				sw = sw<<8+tfmfile.get();
				sw = sw<<8+tfmfile.get();
				ft.param(0) = sw<<4+tfmfile.get()>>4;
			}
			else
				ft.param(k-1) = store_scaled(z, beta, k, alpha);
		if (tfmfile.eof())
			throw 1;
		for (int k = np+1; k <= 7; k++)
			ft.param(k-1) = 0;
		if (np >= 7)
			ft.params = np;
		else
			ft.params = 7;
		ft.hyphenchar = default_hyphen_char();
		ft.skewchar = default_skew_char();
		if (bchlabel < nl)
			ft.bcharlabel = bchlabel+ft.ligkernbase;
		else
			ft.bcharlabel = 0;
		ft.bchar = bchar;
		ft.falsebchar = bchar;
		if (bchar <= ec && bchar >= bc && skip_byte(ft.char_info(bchar)) > 0)
			ft.falsebchar = non_char;
		ft.name = nom;
		ft.area = aire;
		ft.bc = bc;
		ft.ec = ec;
		ft.glue = nullptr;
		ft.parambase--;
		Font::info.resize(Font::info.size()+lf);
		fonts.push_back(ft);
		if (fileopened)
			bclose(tfmfile);
		return fonts.size()-1;
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
	auto &ft = fonts[scanfontident()];
	int val = Font::info.size()-1;
	if (n > 0)
	{
		if (writing && n <= 4 && n >= 2 && ft.glue)
		{
			deleteglueref(ft.glue);
			ft.glue = nullptr;
		}
		if (n > ft.params)
		{
			int f; //ft
			if (f == fonts.size()-1)
			{
				for (; ft.params <= n; ft.params++)
				{
					memoryword fi;
					fi.int_ = 0;
					Font::info.push_back(fi);
					ft.params++;
				}
				val = Font::info.size()-2;
			}
		}
		else
			val = n+ft.parambase;
	}
	if (val == Font::info.size()-1)
		error("Font "+esc(ft.name)+" has only "+std::to_string(ft.params)+" fontdimen parameters", "To increase the number of font parameters, you must\nuse \\fontdimen immediately after the \\font is loaded.");
	return val;
}
