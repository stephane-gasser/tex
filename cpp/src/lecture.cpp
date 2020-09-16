#include "lecture.h"
#include "boite.h"
#include "chaine.h"
#include "getnext.h"
#include "police.h"
#include "expand.h"
#include "pushmath.h"
#include "noeud.h"
#include "deleteglueref.h"
#include "alignement.h"
#include "backinput.h"
#include "impression.h"
#include "calcul.h"
#include "erreur.h"
#include "preparemag.h"
#include "pushinput.h"
#include "popinput.h"
#include "equivalent.h"
#include "macrocall.h" 
#include "fichier.h"
#include "runaway.h"
#include "sauvegarde.h"
#include "buildpage.h"
#include <tuple>

[[nodiscard]] static std::tuple<int, int, AnyNode*> scansomethinginternal(smallnumber level, bool negative, Token t)
{
	// lev/level : tok_val/dimen_val/glue_val/ident_val/int_val/mu_val
	int val, lev;
	AnyNode *gl;
	auto m = t.chr;
	switch (t.cmd)
	{
		case def_code:
			lev = int_val;
			if (m == math_code_base)
				val = math_code(scancharnum());
			else 
				if (m < math_code_base)
					val = eqtb_local[m+scancharnum()-local_base].int_;
				else
					val = eqtb_int[m+scancharnum()-int_base].int_;
			break;
		case toks_register:
		case assign_toks:
			if (level != tok_val)
			{
				backerror(t, "Missing number, treated as zero", "A number should have been here; I inserted `0'.\n(If you can't figure out why I needed to see a number,\nlook up `weird error' in the index to The TeXbook.)");
				val = 0;
				lev = dimen_val;
				break;
			}
			if (t.cmd == toks_register)
				m = toks_base+scaneightbitint();
			gl = eqtb_local[m-local_base].index;
			lev = tok_val;
			break;
		case def_family:
		case set_font:
		case def_font:
			if (level != tok_val)
			{
				backerror(t, "Missing number, treated as zero", "A number should have been here; I inserted `0'.\n(If you can't figure out why I needed to see a number,\nlook up `weird error' in the index to The TeXbook.)");
				val = 0;
				lev = dimen_val;
				break;
			}
			backinput(t);
			val = scanfontident()+frozen_null_font;
			lev = ident_val;
			break;
		case assign_int:
			val = eqtb_int[m-int_base].int_;
			lev = int_val;
			break;
		case assign_dimen:
			val = eqtb_dimen[m-dimen_base].int_;
			lev = dimen_val;
			break;
		case assign_glue:
			gl = dynamic_cast<GlueSpec*>(eqtb_glue[m-glue_base].index); 
			lev = glue_val;
			break;
		case assign_mu_glue:
			gl = dynamic_cast<GlueSpec*>(eqtb_glue[m-glue_base].index);
			lev = mu_val;
			break;
		case set_aux:
			if (abs(mode) != m)
			{
				error("Improper "+cmdchr(t), "You can refer to \\spacefactor only in horizontal mode;\nyou can refer to \\prevdepth only in vertical mode; and\nneither of these is meaningful inside \\write. So\nI'm forgetting what you said and using zero instead.");
				val = 0;
				lev = level == tok_val ? int_val : dimen_val;
				break;
			}
			if (m == vmode)
			{
				val = prev_depth;
				lev = dimen_val;
				break;
			}
			val = space_factor;
			lev = int_val;
			break;
		case set_prev_graf:
			val = 0;
			if (mode)
			{
				nest.back() = curlist;
				int p;
				for (p = nest.size()-1; abs(nest[p].modefield) != vmode; p--);
				val = nest[p].pgfield;
			}
			lev = int_val;
			break;
		case set_page_int:
			val =  m == 0 ? deadcycles : insertpenalties;
			lev = int_val;
			break;
		case set_page_dimen:
			if (pagecontents == 0 && !outputactive)
				val = m == 0 ? max_dimen : 0;
			else
				val = pagesofar[m];
			lev = dimen_val;
			break;
		case set_shape:
			val = 0;
			if (par_shape_ptr())
				val = par_shape_ptr()->values.size()/2;
			lev = int_val;
			break;
		case set_box_dimen:
			val = scaneightbitint();
			val = 0;
			if (box(val))
				switch (m)
				{
					case width_offset:
						val = box(val)->width;
						break;
					case height_offset:
						val = box(val)->height;
						break;
					case depth_offset:
						val = box(val)->depth;
				}
			lev = dimen_val;
		break;
		case char_given:
		case math_given:
			val = t.chr;
			lev = int_val;
			break;
		case assign_font_dimen:
			val = findfontdimen(false);
			Font::info.back().int_ = 0;
			val = Font::info[val].int_;
			lev = dimen_val;
			break;
		case assign_font_int:
			val = m == 0 ? fonts[scanfontident()].hyphenchar: fonts[scanfontident()].skewchar;
			lev = int_val;
			break;
		case register_:
			switch (m)
			{
				case int_val: 
					val = count(scaneightbitint());
					break;
				case dimen_val: 
					val = dimen(scaneightbitint());
					break;
				case glue_val: 
					gl = skip(scaneightbitint());
					break;
				case mu_val: 
					gl = mu_skip(scaneightbitint());
			}
			lev = m;
			break;
		case last_item:
			if (t.chr > glue_val)
			{
				val = t.chr == input_line_no_code ? line : lastbadness;
				lev = int_val;
				break;
			}
			if (t.chr == glue_val)
			{
				gl = zero_glue;
				lev = glue_val;
			}
			else
			{
				val = 0;
				lev = t.chr;
			}
			if (tail->type != char_node && mode)
				switch (t.chr)
				{
					case int_val:
						if (tail->type == penalty_node)
							val = dynamic_cast<PenaltyNode*>(tail)->penalty;
						break;
					case dimen_val: 
						if (tail->type == kern_node)
							val = dynamic_cast<KernNode*>(tail)->width;
						break;
					case glue_val: 
						if (tail->type == glue_node)
						{
							auto Tail = dynamic_cast<GlueNode*>(tail);
							gl = Tail->glue_ptr;
							if (Tail->subtype == mu_glue)
								lev = mu_val;
						}
				}
			else 
				if (mode == vmode && tail == head)
					switch (t.chr)
					{
						case int_val: 
							val = lastpenalty;
							break;
						case dimen_val: 
							val = lastkern;
							break;
						case glue_val: 
							if (lastglue)
								gl = lastglue;
					}
			break;
		default:
			error("You can't use `"+cmdchr(t)+"' after "+esc("the"), "I'm forgetting what you said and using zero instead.");
			val = 0;
			lev = level == tok_val ? int_val : dimen_val;
	}
	while (lev > level)
	{
		if (lev == glue_val)
			val = dynamic_cast<GlueSpec*>(gl)->width;
		else 
			if (lev == mu_val)
				error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.");
		lev--;
	}
	if (negative)
		if (lev >= glue_val)
		{
			auto G = new GlueSpec(dynamic_cast<GlueSpec*>(gl));
			G->width = -G->width;
			G->stretch = -G->stretch;
			G->shrink = -G->shrink;
			gl = G;
		}
		else
			val = -val;
	else 
		if (lev >= glue_val && lev <= mu_val)
			dynamic_cast<GlueSpec*>(gl)->glue_ref_count++;
	return {val, lev, gl};
}



Token getXTokenSkipSpace(void)
{
	Token t;
	do
		t = getxtoken();
	while (t.cmd == spacer);
	return t;
}

Token getXTokenSkipSpaceAndEscape(void)
{
	Token t;
	do
		t = getxtoken();
	while (t.cmd == spacer || t.cmd == escape);
	return t;
}

void scanbox(int boxcontext)
{
	auto t = getXTokenSkipSpaceAndEscape();
	if (t.cmd == make_box)
		beginbox(boxcontext, t);
	else 
		if (boxcontext > leader_flag && (t.cmd == hrule || t.cmd == vrule))
		{
			curbox = dynamic_cast<BoxNode*>(scanrulespec(t));
			boxend(boxcontext);
		}
		else
			backerror(t, "A <box> was supposed to be here", "I was expecting to see \\hbox or \\vbox or \\copy or \\box or\nsomething like that. So you might find something missing in\nyour output. But keep trying; you can fix this later.");
}

void scandelimiter(Delimiter &p, bool r, Token t)
{
	int val;
	if (r)
		val = scantwentysevenbitint();
	else
	{
		t = getXTokenSkipSpaceAndEscape();
		switch (t.cmd)
		{
			case letter:
			case other_char: 
				val = del_code(t.chr);
				break;
			case delim_num: 
				val = scantwentysevenbitint();
				break;
			default: 
				val = -1;
		}
	}
	if (val < 0)
	{
		backerror(t, "Missing delimiter (. inserted)", "I was expecting to see something like `(' or `\\{' or\n`\\}' here. If you typed, e.g., `{' instead of `\\{', you\nshould probably delete the `{' by typing `1' now, so that\nbraces don't get unbalanced. Otherwise just proceed.\nAcceptable delimiters are characters whose \\delcode is\nnonnegative, or you can use `\\delimiter <delimiter code>'.");
		val = 0;
	}
	p.small_fam = (val>>20)%(1<<4);
	p.small_char = (val>>12)%(1<<8);
	p.large_fam = (val>>8)%(1<<4);
	p.large_char = val%(1<<8);
}

static char dig[23]; // of 0..15

static scaled rounddecimals(smallnumber k)
{
	int a = 0;
	while (k > 0)
	{
		k--;
		a = (a+dig[k]*two)/10;
	}
	return (a+1)/2;
}

[[nodiscard]] int scandimen(bool mu, bool inf, bool shortcut)
{
	int val, lev;
	GlueSpec *gl;
	int f = 0;
	aritherror = false;
	curorder = 0;
	bool negative = false;
	Token t;
	while (true) // label 89
	{
		if (!shortcut)
		{
			negative = false;
			do
			{
				t = getXTokenSkipSpace();
				if (t.tok == other_token+'-')
				{
					negative = !negative;
					t.tok = other_token+'+';
				}
			} while (t.tok == other_token+'+');
			if (t.cmd >= min_internal && t.cmd <= max_internal)
				if (mu)
				{
					AnyNode *g;
					std::tie(val, lev, g) = scansomethinginternal(mu_val, false, t);
					gl = dynamic_cast<GlueSpec*>(g);
					if (lev >= glue_val)
					{
						auto v = gl->width;
						deleteglueref(gl);
						val = v;
					}
					if (lev == mu_val)
						break;
					if (lev != int_val)
						error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.");
				}
				else
				{
					AnyNode *g;
					std::tie(val, lev, g) = scansomethinginternal(dimen_val, false, t);
					gl = dynamic_cast<GlueSpec*>(g);
					if (lev == dimen_val)
						break;
				}
			else
			{
				backinput(t);
				if (t.tok == continental_point_token)
					t.tok = point_token; 
				if (t.tok != point_token)
					val = scanint();
				else
				{
					radix = 10;
					val = 0;
				}
				if (t.tok == continental_point_token) 
					t.tok = point_token; 
				if (radix == 10 && t.tok == point_token) 
				{
					t = gettoken();
					for (int k = 0; true; k++)
					{
						t = getxtoken();
						if (t.tok > zero_token+9 || t.tok < zero_token)
						{
							f = rounddecimals(k);
							break;
						}
						if (k < 17)
							dig[k] = t.tok-zero_token;
					}
					if (t.cmd != spacer)
						backinput(t);
				}
			}
		}
		if (val < 0)
		{
			negative = !negative;
			val = -val;
		}
		if (inf)
			if (scankeyword("fil"))
			{
				curorder = 1;
				while (scankeyword("l")) 
					if (curorder == 3)
						error("Illegal unit of measure (replaced by filll)", "I dddon't go any higher than filll.");
					else
						curorder++;
				if (val >= 0x40'00)
					aritherror = true;
				else
					val = (val<<16)+f;
				t = getxtoken();
				if (t.cmd != spacer)
					backinput(t);
				break;
			}
		auto saveval = val;
		t = getXTokenSkipSpace();
		if (t.cmd < min_internal || t.cmd > max_internal)
			backinput(t);
		else
		{
			if (mu)
			{
				AnyNode *g;
				std::tie(val, lev, g) = scansomethinginternal(mu_val, false, t);
				gl = dynamic_cast<GlueSpec*>(g);
				if (lev >= glue_val)
				{
					auto v = gl->width;
					deleteglueref(gl);
					val = v;
				}
				if (lev != mu_val)
					error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.");
			}
			else
			{
				AnyNode *g;
				std::tie(val, lev, g) = scansomethinginternal(dimen_val, false, t);
			}
			auto v = val;
			val = nx_plus_y(saveval, v, xnoverd(v, f, unity));
			break;
		}
		if (!mu)
		{
			if (scankeyword("em"))
			{
				auto v = cur_font().quad();
				t = getxtoken();
				if (t.cmd != spacer)
					backinput(t);
			}
			else 
				if (scankeyword("ex"))
				{
					auto v = cur_font().x_height();
					t = getxtoken();
					if (t.cmd != spacer)
						backinput(t);
				}
		}
		if (mu)
		{
			if (!scankeyword("mu"))
				error("Illegal unit of measure (mu inserted)", "The unit of measurement in math glue must be mu.\nTo recover gracefully from this error, it's best to\ndelete the erroneous units; e.g., type `2' to delete\ntwo letters. (See Chapter 27 of The TeXbook.)");
			if (val >= 0x40'00)
				aritherror = true;
			else
				val = (val<<16)+f;
			t = getxtoken();
			if (t.cmd != spacer)
				backinput(t);
			break;
		}
		if (scankeyword("true"))
		{
			preparemag();
			if (mag() != 1000)
			{
				val = xnoverd(val, 1000, mag());
				f = (1000*f+(remainder_<<16))/mag();
				val += f>>16;
				f %= 1<<16;
			}
		}
		if (scankeyword("pt"))
		{
			if (val >= 0x40'00)
				aritherror = true;
			else
				val = val*unity+f;
			t = getxtoken();
			if (t.cmd != spacer)
				backinput(t);
			break;
		}
		int num, denom;
		auto set_conversion = [&num, &denom](int n, int d){ num = n; denom = d; };
		if (scankeyword("in"))
			set_conversion(7227, 100); // 1 inch = 72.27 pt
		else 
			if (scankeyword("pc"))
				set_conversion(12, 1); // 1 pica = 12 pt
			else 
				if (scankeyword("cm"))
					set_conversion(7227, 254); // 1 inch = 2.54 cm
				else 
					if (scankeyword("mm"))
						set_conversion(7227, 2540); // 1 cm = 10 mm
					else 
						if (scankeyword("bp"))
							set_conversion(7227, 7200); // 1 inch = 72 bp
						else 
							if (scankeyword("dd"))
								set_conversion(1238, 1157);
							else 
								if (scankeyword("cc"))
									set_conversion(14856, 1157);
								else 
									if (scankeyword("sp")) 
									{
										t = getxtoken();
										if (t.cmd != spacer)
											backinput(t);
										break;
									}
									else
									{
										error("Illegal unit of measure (pt inserted)", "Dimensions can be in units of em, ex, in, pt, pc,\ncm, mm, dd, cc, bp, or sp; but yours is a new one!\nI'll assume that you meant to say pt, for printer's points.\nDimension too large\nI can't work with sizes bigger than about 19 feet.\nContinue and I'll use the largest value I can.");
										if (val >= 0x40'00)
											aritherror = true;
										else
											val = val*unity+f;
										t = xtoken(t);
										if (t.cmd != spacer)
											backinput(t);
										break;
									}
		val = xnoverd(val, num, denom);
		f = (num*f+remainder_<<16)/denom;
		val += f>>16;
		f %= 1<<16;
		if (val >= 0x40'00)
			aritherror = true;
		else
			val = val*unity+f;
		t = getxtoken();
		if (t.cmd != spacer)
			backinput(t);
		break;
	} 
	if (aritherror || abs(val) >= 0x40'00'00'00)
	{
		error("Dimension too large", "I can't work with sizes bigger than about 19 feet.\nContinue and I'll use the largest value I can.");
		val = max_dimen;
		aritherror = false;
	}
	if (negative)
		val = -val;
	return val;
}

[[nodiscard]] int scan_normal_dimen(void) { return scandimen(false, false, false); }

int scancharnum(void)
{
	int val = scanint();
	if (val < 0 || val > 255)
	{
		interror(val, "Bad character code", "A character number must be between 0 and 255.\nI changed this one to zero.");
		return 0;
	}
	return val;
}

int scanfourbitint(void)
{
	int val = scanint();
	if (val < 0 || val >= 1<<4)
	{
		interror(val, "Bad number", "Since I expected to read a number between 0 and 15,\nI changed this one to zero.");
		return 0;
	}
	return val;
}

int scaneightbitint(void)
{
	int val = scanint();
	if (val < 0 || val >= 1<<8)
	{
		interror(val, "Bad register code", "A register number must be between 0 and 255.\nI changed this one to zero.");
		return 0;
	}
	return val;
}

int scanfifteenbitint(void)
{
	int val = scanint();
	if (val < 0 || val >= 1<<15)
	{
		interror(val, "Bad mathchar", "A mathchar number must be between 0 and 0x7F'FF.\nI changed this one to zero.");
		return 0;
	}
	return val;
}

[[nodiscard]] int scantwentysevenbitint(void)
{
	int val = scanint();
	if (val < 0 || val >= 1<<27)
	{
		interror(val, "Bad delimiter code", "A numeric delimiter code must be between 0 and 2^{27}-1.\nI changed this one to zero.");
		return 0;
	}
	return val;
}


[[nodiscard]] int scanfontident(void)
{
	auto t = getXTokenSkipSpace();
	switch (t.cmd)
	{
		case def_font:
			return curFontNum();
		case set_font:
			return t.chr;
		case def_family:
			return eqtb_local[t.chr+scanfourbitint()-local_base].int_;
	}
	backerror(t, "Missing font identifier", "I was looking for a control sequence whose\ncurrent meaning has been defined by \\font.");
	return null_font;
}

[[nodiscard]] GlueSpec* scanglue(smallnumber level)
{
	bool mu = level == 3;
	bool negative = false;
	Token t;
	do
	{
		t = getXTokenSkipSpace();
		if (t.tok == other_token+'-')
		{
			negative = !negative;
			t.tok = other_token+'+';
		}
	} while (t.tok != other_token+'+');
	int val, lev;
	GlueSpec *gl;
	if (t.cmd >= min_internal && t.cmd <= max_internal)
	{
		AnyNode *g;
		std::tie(val, lev, g) = scansomethinginternal(level, negative, t);
		gl = dynamic_cast<GlueSpec*>(g);
		if (lev >= glue_val)
		{
			if (lev != level)
				error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.");
			return gl;
		}
		if (lev == int_val)
			val = scandimen(mu, false, true);
		else 
			if (level == mu_val)
				error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.");
	}
	else
	{
		backinput(t);
		val = scandimen(mu, false, false);
		if (negative)
			val = -val;
	}
	auto q = new GlueSpec(zero_glue);
	q->width = val;
	if (scankeyword("plus"))
	{
		q->stretch = scandimen(mu, true, false);
		q->stretch_order = curorder;
	}
	if (scankeyword("minus"))
	{
		q->shrink = scandimen(mu, true, false);
		q->shrink_order = curorder;
	}
	return q;
}

//! Sets \a curval to an integer.
//! The \a scan_int routine is used also to scan the integer part of a 
//! fraction; for example, the `3' in `3.14159' will be found by 
//! \a scan_int. The \a scan_dimen routine assumes that <em> cur_tok=point_token </em>
//! after the integer part of such a fraction has been scanned by \a scan_int, 
//! and that the decimal point has been backed up to be scanned again. 
[[nodiscard]] int scanint(void)
{
	int val, lev;
	GlueSpec *gl;
	radix = 0;
	bool OKsofar = true; // has an error message been issued?
	bool negative = false; // should the answer be negated?
	Token t;
	do
	{
		t = getXTokenSkipSpace();
		if (t.tok == other_token+'-')
		{
			negative = !negative;
			t.tok = other_token+'+';
		}
	} while (t.tok == other_token+'+');
	if (t.tok == alpha_token)
	{
		t = gettoken();
		if (t.tok < cs_token_flag)
		{
			val = t.chr;
			if (t.cmd == right_brace)
				alignstate++;
			if (t.cmd == left_brace)
				alignstate--;
		}
		else 
			val = t.tok-cs_token_flag-(t.tok < cs_token_flag+single_base ? active_base : single_base);
		if (val >= 1<<8)
		{
			backerror(t, "Improper alphabetic constant", "A one-character control sequence belongs after a ` mark.\nSo I'm essentially inserting \\0 here.");
			val = '0';
		}
		else
		{
			t = getxtoken();
			if (t.cmd != spacer)
				backinput(t);
		}
	}
	else 
		if (t.cmd >= min_internal && t.cmd <= max_internal)
		{
			AnyNode *g;
			std::tie(val, lev, g) = scansomethinginternal(int_val, false, t);
			gl = dynamic_cast<GlueSpec*>(g);
		}
		else
		{
			radix = 10;
			auto m = 214748364; //0xC'CC'CC'CC
			if (t.tok == octal_token) //other_char+'\''
			{
				radix = 8;
				m = 0x10'00'00'00;
				t = getxtoken();
			}
			else 
				if (t.tok == hex_token) //other_char+'\"'
				{
					radix = 16;
					m = 0x8'00'00'00;
					t = getxtoken();
				};
			bool vacuous = true;
			val = 0;
			while (true)
			{
				int d; //the digit just scanned
				if (t.tok < zero_token+radix && t.tok >= zero_token && t.tok <= zero_token+9)
					d = t.tok-zero_token;
				else 
					if (radix == 16)
						if (t.tok <= A_token+5 && t.tok >= A_token)
							d = t.tok-A_token+10;
						else 
							if (t.tok <= other_A_token+5 && t.tok >= other_A_token)
								d = t.tok-other_A_token+10;
							else
								break;
					else
						break;
				vacuous = false; // has no digits appeared?
				if (val >= m && (val > m || d > 7 || radix != 10))
				{
					if (OKsofar)
					{
						error("Number too big", "I can only go up to 2147483647='17777777777=\"7FFFFFFF,\nso I'm using that number instead of yours.");
						val = infinity;
						OKsofar = false;
					}
				}
				else
					val = val*radix+d;
				t = getxtoken();
			}
			if (vacuous)
				backerror(t, "Missing number, treated as zero", "A number should have been here; I inserted `0'.\n(If you can't figure out why I needed to see a number,\nlook up `weird error' in the index to The TeXbook.)");
			else 
				if (t.cmd != spacer)
					backinput(t);
		}
	if (negative)
		val = -val;
	return val;
}

bool scankeyword(const std::string &s)
{
	auto p = backup_head;
	p->link = nullptr;
	for (size_t k = 0; k < s.size();)
	{
		auto t = getxtoken();
		if (t.cs == 0 && (t.chr == s[k] || t.chr == s[k]-'a'+'A'))
		{
			auto q = new TokenNode(t.tok);
			p->link = q;
			p = q;
			k++;
		}
		else 
			if (t.cmd != spacer || p != backup_head)
			{
				backinput(t);
				if (p != backup_head)
					back_list(dynamic_cast<TokenNode*>(backup_head->link));
				return false;
			}
	}
	flushnodelist(backup_head->link);
	return true;
}

[[nodiscard]] Token scanleftbrace(void)
{
	auto t = getXTokenSkipSpaceAndEscape();
	if (t.cmd != left_brace)
	{
		backerror(t, "Missing { inserted", "A left brace was mandatory here, so I've put one in.\nYou might want to delete and/or insert some corrections\nso that I will find a matching right brace soon.\n(If you're confused by all this, try typing `I}' now.)");
		t.tok = left_brace_token+'{';
		t.cmd = left_brace;
		t.chr = '{'; 
		alignstate++;
	}
	return t;
}

void scanmath(NoadContent &p)
{
	auto t = getXTokenSkipSpaceAndEscape();
	bool another;
	int c;
	do
	{
		another = false;
		switch (t.cmd)
		{
			case letter:
			case other_char:
			case char_given:
				c = math_code(t.chr);
				if (c == 1<<15)
				{
					t.cs = t.chr+active_base;
					t.cmd = eqtb_active[t.chr].type;
					t.chr = eqtb_active[t.chr].int_;
					t = xtoken(t);
					backinput(t);
					t = getXTokenSkipSpaceAndEscape();
					another = true;
					continue;
				}
				break;
			case char_num:
				t.chr = scancharnum();
				t.cmd = char_given;
				another = true;
				continue;
			case math_char_num:
				c = scanfifteenbitint();
				break;
			case math_given: 
				c = t.chr;
				break;
			case delim_num:
				c = scantwentysevenbitint()>>12;
				break;
			default:
			{
				backinput(t);
				t = scanleftbrace();
				auto m = new MemoryNode;
				m->index = &p;
				savestack.push_back(m);
				pushmath(math_group);
				return;
			}
		}
	} while (another);
	p.math_type = math_char;
	p.character = c%(1<<8);
	p.fam = (c >= var_code && fam_in_range() ? cur_fam() : (c>>8)%(1<<4));
}

void scanoptionalequals(void)
{
	auto t = getXTokenSkipSpace();
	if (t.tok != other_token+'=') // other_char + '='
		backinput(t);
}

constexpr int default_rule = 26214; //0.4\thinspace pt

RuleNode *scanrulespec(Token t)
{
	auto q = new RuleNode;
	if (t.cmd == vrule)
		q->width = default_rule;
	else
	{
		q->height = default_rule;
		q->depth = 0;
	}
	while (true)
	{
		if (scankeyword("width"))
		{
			q->width = scan_normal_dimen();
			continue;
		}
		if (scankeyword("height"))
		{
			q->height = scan_normal_dimen();
			continue;
		}
		if (scankeyword("depth"))
		{
			q->depth = scan_normal_dimen();
			continue;
		}
		break;
	}
	return q;
}

[[nodiscard]] Token scanspec(groupcode c)
{
	int speccode;
	int val;
	if (scankeyword("to"))
	{
		speccode = exactly;
		val = scan_normal_dimen();
	}
	else
	{
		speccode = additional;
		val = scankeyword("spread") ? scan_normal_dimen() : 0;
	}
	auto m = new MemoryNode;
	m->int_ = speccode;
	savestack.push_back(m);
	m = new MemoryNode;
	m->int_ = val;
	savestack.push_back(m);
	newsavelevel(c);
	return scanleftbrace();
}

[[nodiscard]] Token scanspec(groupcode c, int s)
{
	auto m = new MemoryNode;
	m->int_ = s;
	savestack.push_back(m);
	return scanspec(c);
}

static void store_new_token(TokenNode* &p, halfword t)
{
	p->link = new TokenNode(t);
	next(p);
}

TokenNode* scantoks(bool macrodef, bool xpand, Token tk)
{
	scannerstatus = macrodef ? defining : absorbing;
	warningindex = tk.cs;
	defref = new TokenNode;
	defref->token_ref_count = 0;
	auto p = defref;
	halfword hashbrace = 0;
	halfword t = zero_token;
	halfword unbalance = 0;
	if (macrodef)
		while (true)
		{
			tk = gettoken();
			if (tk.tok < right_brace_limit)
			{
				store_new_token(p, end_match_token);
				if (tk.cmd == right_brace)
				{
					error("Missing { inserted", "Where was the left brace? You said something like `\\def\\a}',\nwhich I'm going to interpret as `\\def\\a{}'.");
					alignstate++;
					unbalance = 1;
				}
				break;
			}
			if (tk.cmd == mac_param)
			{
				auto s = match_token+tk.chr;
				tk = gettoken();
				if (tk.cmd == left_brace)
				{
					hashbrace = tk.tok;
					store_new_token(p, tk.tok);
					store_new_token(p, end_match_token);
					break;
				}
				if (t == zero_token+9)
					error("You already have nine parameters", "I'm going to ignore the # sign you just used.");
				else
				{
					t++;
					if (tk.tok != t)
						backerror(tk, "Parameters must be numbered consecutively", "I've inserted the digit you should have used after the #.\nType `1' to delete what you did use.");
					tk.tok = s;
				}
			}
			store_new_token(p, tk.tok);
		}
	else
		tk = scanleftbrace();
	while (unbalance)
	{
		if (xpand)
		{
			for (tk = getnext(); tk.cmd > max_command; tk = getnext())
			{
				if (tk.cmd != the)
					expand(tk);
				else
				{
					auto q = thetoks();
					if (temp_head->link)
					{
						p->link = temp_head->link;
						p = q;
					}
				}
			}
			tk = xtoken(tk);
		}
		else
			tk = gettoken();
		switch (tk.cmd)
		{
			case left_brace:
				unbalance++;
				break;
			case right_brace:
				unbalance--;
				break;
			case mac_param:
				if (macrodef)
				{
					auto s = tk.tok;
					tk = xpand ? getxtoken() : gettoken();
					if (tk.cmd != mac_param)
						if (tk.tok <= zero_token || tk.tok > t) 
						{
							backerror(tk, "Illegal parameter number in definition of "+scs(warningindex), "You meant to type ## instead of #, right?\nOr maybe a } was forgotten somewhere earlier, and things\nare all screwed up? I'm going to assume that you meant ##.");
							tk.tok = s;
						}
						else
							tk.tok = out_param_token-'0'+tk.chr;
				}
		}
		if (unbalance)
			store_new_token(p, tk.tok);
	}
	scannerstatus = normal;
	if (hashbrace)
		store_new_token(p, hashbrace);
	return p;
}

void back_list(TokenNode *p) { begintokenlist(p, backed_up); } //!< backs up a simple token list
void ins_list(TokenNode *p) { begintokenlist(p, inserted); } //!< inserts a simple token list

void begintokenlist(TokenNode *P, quarterword t)
{
	push_input();
	state = token_list;
	Start = P;
	index = t;
	if (t < macro)
	{
		Loc = P;
		return;
	}
	P->token_ref_count++; //the token list starts with a reference count
	if (t == macro)
	{
		param_start = paramstack.size();
		return;
	}
	Loc = dynamic_cast<TokenNode*>(P->link);
	if (tracing_macros() > 1)
		switch (t)
		{
			case mark_text: 
				diagnostic("\r"+esc("mark")+"->"+tokenshow(P));
				break;
			case write_text: 
				diagnostic("\r"+esc("write")+"->"+tokenshow(P));
				break;
			default:
				diagnostic("\r"+cmdchr(make_tok(assign_toks, t-output_text+output_routine_loc))+"->"+tokenshow(P));
		}
}

void endtokenlist(void)
{
	switch (token_type)
	{
		case parameter:
		case v_template:
			break;
		case u_template:
			if (alignstate > 500000)
				alignstate = 0;
			else
				fatalerror("(interwoven alignment preambles are not allowed)");
			break;
		case backed_up:
		case inserted:
			flushnodelist(Start);
			break;
		case macro:
			deletetokenref(Start);
			for (;paramstack.size() > param_start; paramstack.pop_back())
				flushnodelist(paramstack.back());
			break;
		case output_text:
		case every_par_text:
		case every_math_text:
		case every_display_text:
		case every_hbox_text:
		case every_vbox_text:
		case every_job_text:
		case every_cr_text:
		case mark_text:
		case write_text:
			deletetokenref(Start);
	}
	pop_input();
}

void deletetokenref(TokenNode *p)
{
	if (p->token_ref_count == 0)
		flushnodelist(p);
	else
		p->token_ref_count--;
}

[[nodiscard]] Token gettoken(void) { return make_tok(getnext(false)); }

[[nodiscard]] Token getxtoken(void)
{
	Token t;
	for (t = getnext(); t.cmd > max_command; t = getnext())
	{
		if (t.cmd >= call)
			if (t.cmd < end_template)
				macrocall(t);
			else
			{
				t.cs = frozen_endv;
				t.cmd = ignore;
				break;
			}
		else
			expand(t);
	}
	return make_tok(t);
}

[[nodiscard]] Token xtoken(Token t)
{
	while (t.cmd > max_command)
	{
		expand(t);
		t = getnext();
	}
	return make_tok(t);
}

Token getpreambletoken(void)
{
	while (true)
	{
		auto t = gettoken();
		while (t.chr == span_code && t.cmd == tab_mark)
		{
			t = gettoken();
			if (t.cmd > max_command)
			{
				expand(t);
				t = gettoken();
			}
		}
		switch (t.cmd)
		{
			case endv:
				fatalerror("(interwoven alignment preambles are not allowed)");
				break;
			case assign_glue:
				if (t.chr != glue_base+tab_skip_code)
					return t;
				break;
			default:
				return t;
		}
		scanoptionalequals();
		(global_defs() > 0 ? geqdefine_ : eqdefine_)(&eqtb_glue[tab_skip_code], glue_ref, scanglue(glue_val));
	}
}

[[nodiscard]] halfword getrtoken(void)
{
	while (true)
	{
		Token t;
		do
			t = gettoken();
		while (t.tok == space_token);
		if (t.cs && t.cs <= frozen_control_sequence)
			return t.cs;
		inserror(t, "Missing control sequence inserted", "Please don't say `\\def cs{...}', say `\\def\\cs{...}'.\nI've inserted an inaccessible control sequence so that your\ndefinition will be completed without mixing me up too badly.\nYou can recover graciously from this error, if you're\ncareful; see exercise 27.2 in The TeXbook.");
		if (t.cs == 0)
			backinput(t);
		t.tok = frozen_protection+cs_token_flag;
	}
}

void insthetoks(void)
{
	thetoks();
	ins_list(dynamic_cast<TokenNode*>(temp_head->link));
}

[[nodiscard]] TokenNode* readtoks(int n, halfword r)
{
	scannerstatus = defining;
	warningindex = r;
	defref = new TokenNode;
	defref->token_ref_count = 0;
	auto p = defref;
	store_new_token(p, end_match_token);
	smallnumber m = (n < 0 || n > 15) ? 16 : n;
	auto s = alignstate;
	alignstate = 1000000;
	do
	{
		beginfilereading();
		name = m+1;
		if (readopen[m] == closed)
			if (interaction > nonstop_mode)
				if (n < 0)
				{
					print("");
					terminput();
				}
				else
				{
					print("\n"+scs(r)+"=");
					terminput();
					n = -1;
				}
		else
			fatalerror("*** (cannot \read from terminal in nonstop modes)");

		else 
			if (readopen[m] == just_open)
				if (inputln(readfile[m], false))
					readopen[m] = normal;
				else
				{
					aclose(readfile[m]);
					readopen[m] = closed;
				}

			else
				if (!inputln(readfile[m], true))
				{
					aclose(readfile[m]);
					readopen[m] = closed;
					if (alignstate != 1000000)
					{
						runaway();
						error("File ended within "+esc("read"), "This \\read has unbalanced braces.");
						alignstate = 1000000;
					}
				}
		limit = last;
		if (end_line_char_inactive())
			limit--;
		else
			buffer[limit] = end_line_char();
		First = limit+1;
		Loc = Start;
		state = new_line;
		while (true)
		{
			Token t;
			t = gettoken();
			if (t.tok == 0)
				break;
			if (alignstate < 1000000)
			{
				do
					t = gettoken();
				while (t.tok);
				alignstate = 1000000;
				break;
			}
			auto q = new TokenNode(t.tok);
			p->link = q;
			p = q;
		}
		endfilereading();
	} while (alignstate != 1000000);
	scannerstatus = normal;
	alignstate = s;
	return defref;
}

static TokenNode* strtoks(const std::string &s)
{
	auto p = dynamic_cast<TokenNode*>(temp_head);
	p->link = nullptr;
	for (halfword t: s)
	{
		if (t == ' ')
			t = space_token;
		else
			t += other_token;
		store_new_token(p, t);
	}
	return p;
}

void convtoks(Token t)
{
	smallnumber savescannerstatus;
	int val;
	switch (t.chr)
	{
		case number_code:
			strtoks(std::to_string(scanint()));
			break;
		case roman_numeral_code: 
			strtoks(romanint(scanint()));
			break;
		case font_name_code: 
			val = scanfontident();
			strtoks(fonts[val].name+(fonts[val].size != fonts[val].dsize ? " at "+asScaled(fonts[val].size)+"pt" : ""));
			break;
		case string_code:
			strtoks(t.cs ? scs(t.cs) : std::string(1, t.chr));
			break;
		case meaning_code:
			savescannerstatus = scannerstatus;
			scannerstatus = normal;
			t = gettoken();
			scannerstatus = savescannerstatus;
			strtoks(meaning(t));
			break;
		case job_name_code: 
			if (jobname == "")
				openlogfile();
			strtoks(jobname);
	}
	ins_list(dynamic_cast<TokenNode*>(temp_head->link));
}

TokenNode* thetoks(void)
{
	auto t = getxtoken();
	auto [val, lev, gl] = scansomethinginternal(tok_val, false, t);
	switch (lev)
	{
		case ident_val:
		{
			auto p = dynamic_cast<TokenNode*>(temp_head);
			p->link = nullptr;
			store_new_token(p, cs_token_flag+val);
			return p;
		}
		case tok_val:
		{
			auto p = dynamic_cast<TokenNode*>(temp_head);
			p->link = nullptr;
			if (gl)
				for (auto r = dynamic_cast<TokenNode*>(dynamic_cast<TokenNode*>(gl)->link); r; next(r))
					store_new_token(p, r->token);
			return p;
		}
		case int_val: 
			return strtoks(std::to_string(val));
		case dimen_val:
			return strtoks(asScaled(val)+"pt");
		case glue_val:
		{
			deleteglueref(dynamic_cast<GlueSpec*>(gl));
			return strtoks(asSpec(dynamic_cast<GlueSpec*>(gl), "pt"));
		}
		default: // mu_val
		{
			deleteglueref(dynamic_cast<GlueSpec*>(gl));
			return strtoks(asSpec(dynamic_cast<GlueSpec*>(gl), "mu"));
		}
	}
}

