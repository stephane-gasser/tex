#include "lecture.h"
#include "getnext.h"
#include "expand.h"
#include "pushmath.h"
#include "flushlist.h"
#include "noeud.h"
#include "beginbox.h"
#include "boxend.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"
#include "deleteglueref.h"
#include "backinput.h"
#include "getavail.h"
#include "rounddecimals.h"
#include "findfontdimen.h"
#include "impression.h"
#include "xnoverd.h"
#include "multandadd.h"
#include "erreur.h"
#include "preparemag.h"
#include "xnoverd.h"
#include "texte.h"
#include "beginname.h"
#include "morename.h"
#include "endname.h"
#include "pushinput.h"
#include "popinput.h"
#include "pauseforinstructions.h"
#include "geqdefine.h"
#include "eqdefine.h"
#include "macrocall.h"
#include "fichier.h"
#include "terminput.h"
#include "beginfilereading.h"
#include "endfilereading.h"
#include "inputln.h"
#include "runaway.h"
#include "openlogfile.h"

void scanbox(int boxcontext)
{
	do
		getxtoken();
	while (curcmd == spacer || curcmd == escape);
	if (curcmd == make_box)
		beginbox(boxcontext);
	else 
		if (boxcontext > leader_flag && (curcmd == hrule || curcmd == vrule))
		{
			curbox = scanrulespec();
			boxend(boxcontext);
		}
		else
			backerror("A <box> was supposed to be here", "I was expecting to see \\hbox or \\vbox or \\copy or \\box or\nsomething like that. So you might find something missing in\nyour output. But keep trying; you can fix this later.");
}

void scandelimiter(halfword p, bool r)
{
	int val;
	if (r)
		val = scantwentysevenbitint();
	else
	{
		do
			getxtoken();
		while (curcmd == spacer || curcmd == escape);
		switch (curcmd)
		{
			case letter:
			case other_char: 
				val = del_code(curchr);
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
		backerror("Missing delimiter (. inserted)", "I was expecting to see something like `(' or `\\{' or\n`\\}' here. If you typed, e.g., `{' instead of `\\{', you\nshould probably delete the `{' by typing `1' now, so that\nbraces don't get unbalanced. Otherwise just proceed.\nAcceptable delimiters are characters whose \\delcode is\nnonnegative, or you can use `\\delimiter <delimiter code>'.");
		val = 0;
	}
	mem[p].qqqq.b0 = (val>>20)%0x10;
	mem[p].qqqq.b1 = (val>>12)%0x1'00;
	mem[p].qqqq.b2 = (val>>8)%0x10;
	mem[p].qqqq.b3 = val%0x1'00;
}

[[nodiscard]] int scandimen(bool mu, bool inf, bool shortcut)
{
	int val, lev;
	int f = 0;
	aritherror = false;
	curorder = 0;
	bool negative = false;
	while (true) // label 89
	{
		if (!shortcut)
		{
			negative = false;
			do
			{
				do
					getxtoken();
				while (curcmd == spacer);
				if (curtok == other_token+'-')
				{
					negative = !negative;
					curtok = other_token+'+';
				}
			} while (curtok == other_token+'+');
			if (curcmd >= min_internal && curcmd <= max_internal)
				if (mu)
				{
					std::tie(val, lev) = scansomethinginternal(mu_val, false);
					if (lev >= glue_val)
					{
						auto v = width(val);
						deleteglueref(val);
						val = v;
					}
					if (lev == mu_val)
						break;
					if (lev != int_val)
						error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.");
				}
				else
				{
					std::tie(val, lev) = scansomethinginternal(dimen_val, false);
					if (lev == dimen_val)
						break;
				}
			else
			{
				backinput();
				if (curtok == continental_point_token)
					curtok = point_token; 
				if (curtok != point_token)
					val = scanint();
				else
				{
					radix = 10;
					val = 0;
				}
				if (curtok == continental_point_token) 
					curtok = point_token; 
				if (radix == 10 && curtok == point_token) 
				{
					int k = 0;
					halfword p = 0;
					gettoken();
					while (true)
					{
						getxtoken();
						if (curtok > zero_token+9 || curtok < zero_token)
							break;
						if (k < 17)
						{
							auto q = getavail();
							link(q) = p;
							info(q) = curtok-zero_token;
							p = q;
							k++;
						}
					}
					for (int kk = k; k > 0; k--)
					{
						dig[kk-1] = info(p);
						auto q = p;
						p = link(p);
						free_avail(q);
					}
					f = rounddecimals(k);
					if (curcmd != spacer)
						backinput();
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
				getxtoken();
				if (curcmd != spacer)
					backinput();
				break;
			}
		auto saveval = val;
		do
			getxtoken();
		while (curcmd == spacer);
		if (curcmd < min_internal || curcmd > max_internal)
			backinput();
		else
		{
			if (mu)
			{
				std::tie(val, lev) = scansomethinginternal(3, false);
				if (lev >= 2)
				{
					auto v = width(val);
					deleteglueref(val);
					val = v;
				}
				if (lev != 3)
					error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.");
			}
			else
				std::tie(val, lev) = scansomethinginternal(1, false);
			auto v = val;
			val = nx_plus_y(saveval, v, xnoverd(v, f, 0x1'00'00));
			break;
		}
		if (!mu)
		{
			if (scankeyword("em"))
			{
				auto v = quad(cur_font());
				getxtoken();
				if (curcmd != spacer)
					backinput();
			}
			else 
				if (scankeyword("ex"))
				{
					auto v = x_height(cur_font());
					getxtoken();
					if (curcmd != spacer)
						backinput();
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
			getxtoken();
			if (curcmd != spacer)
				backinput();
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
			getxtoken();
			if (curcmd != spacer)
				backinput();
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
										getxtoken();
										if (curcmd != spacer)
											backinput();
										break;
									}
									else
									{
										error("Illegal unit of measure (pt inserted)", "Dimensions can be in units of em, ex, in, pt, pc,\ncm, mm, dd, cc, bp, or sp; but yours is a new one!\nI'll assume that you meant to say pt, for printer's points.\nDimension too large\nI can't work with sizes bigger than about 19 feet.\nContinue and I'll use the largest value I can.");
										if (val >= 0x40'00)
											aritherror = true;
										else
											val = val*unity+f;
										getxtoken();
										if (curcmd != spacer)
											backinput();
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
		getxtoken();
		if (curcmd != spacer)
			backinput();
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


void scanfilename(void)
{
	nameinprogress = true;
	beginname();
	do
		getxtoken();
	while (curcmd == spacer);
	while (true)
	{
		if (curcmd > other_char || curchr > 255)
		{
			backinput();
			break;
		}
		if (!morename(curchr))
			break;
		getxtoken();
	}
	endname();
	nameinprogress = false;
}

[[nodiscard]] int scanfontident(void)
{
	do
		getxtoken();
	while (curcmd == spacer);
	if (curcmd == def_font)
		return cur_font();
	if (curcmd == set_font)
		return curchr;
	if (curcmd == def_family)
		return equiv(curchr+scanfourbitint());
	backerror("Missing font identifier", "I was looking for a control sequence whose\ncurrent meaning has been defined by \\font.");
	return null_font;
}

[[nodiscard]] int scanglue(smallnumber level)
{
	bool mu = level == 3;
	bool negative = false;
	do
	{
		do
			getxtoken();
		while (curcmd == spacer);
		if (curtok == other_token+'-')
		{
			negative = !negative;
			curtok = other_token+'+';
		}
	} while (curtok != other_token+'+');
	int val, lev;
	if (curcmd >= min_internal && curcmd <= max_internal)
	{
		std::tie(val, lev) = scansomethinginternal(level, negative);
		if (lev >= 2)
		{
			if (lev != level)
				error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.");
			return val;
		}
		if (lev == 0)
			val = scandimen(mu, false, true);
		else 
			if (level == 3)
				error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.");
	}
	else
	{
		backinput();
		val = scandimen(mu, false, false);
		if (negative)
			val = -val;
	}
	auto q = newspec(zero_glue);
	width(q) = val;
	if (scankeyword("plus"))
	{
		stretch(q) = scandimen(mu, true, false);
		type(q) = curorder;
	}
	if (scankeyword("minus"))
	{
		shrink(q) = scandimen(mu, true, false);
		subtype(q) = curorder;
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
	radix = 0;
	bool OKsofar = true; // has an error message been issued?
	bool negative = false; // should the answer be negated?
	do
	{
		do
			getxtoken();
		while (curcmd == spacer);
		if (curtok == other_token+'-')
		{
			negative = !negative;
			curtok = other_token+'+';
		}
	} while (curtok == other_token+'+');
	if (curtok == alpha_token)
	{
		gettoken();
		if (curtok < cs_token_flag)
		{
			val = curchr;
			if (curcmd == right_brace)
				alignstate++;
			if (curcmd == left_brace)
				alignstate--;
		}
		else 
			val = curtok-cs_token_flag-(curtok < cs_token_flag+single_base ? active_base : single_base);
		if (val > 0xFF)
		{
			backerror("Improper alphabetic constant", "A one-character control sequence belongs after a ` mark.\nSo I'm essentially inserting \\0 here.");
			val = '0';
		}
		else
		{
			getxtoken();
			if (curcmd != spacer)
				backinput();
		}
	}
	else 
		if (curcmd >= min_internal && curcmd <= max_internal)
			std::tie(val, lev) = scansomethinginternal(0, false);
		else
		{
			radix = 10;
			auto m = 214748364; //0xC'CC'CC'CC
			if (curtok == octal_token) //other_char+'\''
			{
				radix = 8;
				m = 0x10'00'00'00;
				getxtoken();
			}
			else 
				if (curtok == hex_token) //other_char+'\"'
				{
					radix = 16;
					m = 0x8'00'00'00;
					getxtoken();
				};
			bool vacuous = true;
			val = 0;
			while (true)
			{
				int d; //the digit just scanned
				if (curtok < zero_token+radix && curtok >= zero_token && curtok <= zero_token+9)
					d = curtok-zero_token;
				else 
					if (radix == 16)
						if (curtok <= A_token+5 && curtok >= A_token)
							d = curtok-A_token+10;
						else 
							if (curtok <= other_A_token+5 && curtok >= other_A_token)
								d = curtok-other_A_token+10;
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
				getxtoken();
			}
			if (vacuous)
				backerror("Missing number, treated as zero", "A number should have been here; I inserted `0'.\n(If you can't figure out why I needed to see a number,\nlook up `weird error' in the index to The TeXbook.)");
			else 
				if (curcmd != spacer)
					backinput();
		}
	if (negative)
		val = -val;
	return val;
}

bool scankeyword(const std::string &t)
{
	halfword p = backup_head;
	link(p) = 0;
	for (size_t k = 0; k < t.size();)
	{
		getxtoken();
		if (curcs == 0 && (curchr == t[k] || curchr == t[k]-'a'+'A'))
		{
			auto q = getavail();
			link(p) = q;
			info(q) = curtok;
			p = q;
			k++;
		}
		else 
			if (curcmd != spacer || p != backup_head)
			{
				backinput();
				if (p != backup_head)
					back_list(link(backup_head));
				return false;
			}
	}
	flushlist(link(backup_head));
	return true;
}

void scanleftbrace(void)
{
	do  
		getxtoken();
	while (curcmd == spacer || curcmd == escape);
	if (curcmd != left_brace)
	{
		backerror("Missing { inserted", "A left brace was mandatory here, so I've put one in.\nYou might want to delete and/or insert some corrections\nso that I will find a matching right brace soon.\n(If you're confused by all this, try typing `I}' now.)");
		curtok = left_brace_token+'{';
		curcmd = left_brace;
		curchr = '{'; 
		alignstate++;
	}
}

void scanmath(halfword p)
{
	do
		getxtoken();
	while (curcmd == spacer || curcmd == escape);
	bool label21;
	do
	{
		label21 = false;
		int c;
		switch (curcmd)
		{
			case letter:
			case other_char:
			case char_given:
				c = math_code(curchr);
				if (c == 0x80'00)
				{
					curcs = curchr+1;
					curcmd = eq_type(curcs);
					curchr = equiv(curcs);
					xtoken();
					backinput();
					do
						getxtoken();
					while (curcmd == spacer || curcmd == escape);
					label21 = true;
					continue;
				}
				break;
			case char_num:
				curchr = scancharnum();
				curcmd = char_given;
				label21 = true;
				continue;
			case math_char_num:
				c = scanfifteenbitint();
				break;
			case math_given: 
				c = curchr;
				break;
			case delim_num:
				c = scantwentysevenbitint()>>12;
				break;
			default:
				backinput();
				scanleftbrace();
				savestack[saveptr++].int_ = p;
				pushmath(math_group);
				return;
		}
	} while (label21);
	math_type(p) = math_char;
	character(p) = c%0x1'00;
	if (c >= var_code && fam_in_range())
		fam(p) = cur_fam();
	else
		fam(p) = (c>>8)%0x10;
}

void scanoptionalequals(void)
{
	do
		getxtoken();
	while (curcmd == spacer);
	if (curtok != 3133) // other_char + '='
		backinput();
}

constexpr int default_rule = 26214; //0.4\thinspace pt

halfword scanrulespec(void)
{
	auto q = newrule();
	if (curcmd == vrule)
		width(q) = default_rule;
	else
	{
		height(q) = default_rule;
		depth(q) = 0;
	}
	while (true)
	{
		if (scankeyword("width"))
		{
			width(q) = scan_normal_dimen();
			continue;
		}
		if (scankeyword("height"))
		{
			height(q) = scan_normal_dimen();
			continue;
		}
		if (scankeyword("depth"))
		{
			depth(q) = scan_normal_dimen();
			continue;
		}
		break;
	}
	return q;
}

//! |mem| location of math glue spec
static halfword& mu_skip(halfword p) { return equiv(mu_skip_base+p); }

[[nodiscard]] std::tuple<int, int> scansomethinginternal(smallnumber level, bool negative)
{
	int val, lev;
	halfword m = curchr;
	switch (curcmd)
	{
		case def_code:
			lev = int_val;
			if (m == math_code_base)
				val = math_code(scancharnum());
			else 
				if (m < math_code_base)
					val = equiv(m+scancharnum());
				else
					val = eqtb[m+scancharnum()].int_;
			break;
		case toks_register:
		case assign_toks:
		case def_family:
		case set_font:
		case def_font:
			if (level != tok_val)
			{
				backerror("Missing number, treated as zero", "A number should have been here; I inserted `0'.\n(If you can't figure out why I needed to see a number,\nlook up `weird error' in the index to The TeXbook.)");
				val = 0;
				lev = dimen_val;
			}
			else 
				if (curcmd <= assign_toks)
				{
					if (curcmd < assign_toks)
						m = toks_base+scaneightbitint();
					val = equiv(m);
					lev = tok_val;
				}
				else
				{
					backinput();
					val = scanfontident()+frozen_null_font;
					lev = ident_val;
				}
			break;
		case assign_int:
			val = eqtb[m].int_;
			lev = int_val;
			break;
		case assign_dimen:
			val = eqtb[m].int_;
			lev = dimen_val;
			break;
		case assign_glue:
			val = equiv(m);
			lev = glue_val;
			break;
		case assign_mu_glue:
			val = equiv(m);
			lev = mu_val;
			break;
		case set_aux:
			if (abs(mode) != m)
			{
				error("Improper "+cmdchr(set_aux, m), "You can refer to \\spacefactor only in horizontal mode;\nyou can refer to \\prevdepth only in vertical mode; and\nneither of these is meaningful inside \\write. So\nI'm forgetting what you said and using zero instead.");
				val = 0;
				lev = level == tok_val ? int_val : dimen_val;
			}
			else
				if (m == vmode)
				{
					val = prev_depth;
					lev = dimen_val;
				}
				else
				{
					val = space_factor;
					lev = int_val;
				}
			break;
		case set_prev_graf:
			val = 0;
			if (mode)
			{
				nest[nestptr] = curlist;
				auto p = nestptr;
				while (abs(nest[p].modefield) != vmode)
					p--;
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
				val = info(par_shape_ptr());
			lev = int_val;
			break;
		case set_box_dimen:
			val = scaneightbitint();
			if (box(val) == 0)
				val = 0;
			else
				val = mem[box(val)+m].int_;
			lev = dimen_val;
		break;
		case char_given:
		case math_given:
			val = curchr;
			lev = int_val;
			break;
		case assign_font_dimen:
			val = findfontdimen(false);
			fontinfo[fmemptr].int_ = 0;
			val = fontinfo[val].int_;
			lev = dimen_val;
			break;
		case assign_font_int:
			val = (m == 0 ? hyphenchar: skewchar)[scanfontident()];
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
					val = skip(scaneightbitint());
					break;
				case mu_val: 
					val = mu_skip(scaneightbitint());
			}
			lev = m;
			break;
		case last_item:
			if (curchr > glue_val)
			{
				val = curchr == input_line_no_code ? line : lastbadness;
				lev = int_val;
			}
			else
			{
				if (curchr == glue_val)
				{
					val = zero_glue;
					lev = glue_val;
				}
				else
				{
					val = 0;
					lev = curchr;
				}
				if (!is_char_node(tail) && mode)
					switch (curchr)
					{
						case int_val: 
							if (type(tail) == penalty_node)
								val = penalty(tail);
							break;
						case dimen_val: 
							if (type(tail) == kern_node)
								val = width(tail);
							break;
						case glue_val: 
							if (type(tail) == glue_node)
							{
								val = glue_ptr(tail);
								if (subtype(tail) == mu_glue)
									lev = mu_val;
							}
					}
				else 
					if (mode == vmode && tail == head)
						switch (curchr)
						{
							case int_val: 
								val = lastpenalty;
								break;
							case dimen_val: 
								val = lastkern;
								break;
							case glue_val: 
								if (lastglue != empty_flag)
									val = lastglue;
						}
			}
			break;
		default:
			error("You can't use `"+cmdchr(curcmd, curchr)+"' after "+esc("the"), "I'm forgetting what you said and using zero instead.");
			val = 0;
			lev = level == tok_val ? int_val : dimen_val;
	}
	while (lev > level)
	{
		if (lev == glue_val)
			val = width(val);
		else 
			if (lev == mu_val)
				error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.");
		lev--;
	}
	if (negative)
		if (lev >= glue_val)
		{
			val = newspec(val);
			width(val) = -width(val);
			stretch(val) = -stretch(val);
			shrink(val) = -shrink(val);
		}
		else
			val = -val;
	else 
		if (lev >= glue_val && lev <= mu_val)
			add_glue_ref(val);
	return {val, lev};
}

void scanspec(groupcode c, bool threecodes)
{
	int s;
	if (threecodes)
		s = savestack[saveptr+0].int_;
	int speccode;
	int val;
	if (scankeyword("to"))
	{
		speccode = exactly;
		val = scan_normal_dimen();
	}
	else 
		if (scankeyword("spread"))
		{
			speccode = additional;
			val = scan_normal_dimen();
		}
		else
		{
			speccode = additional;
			val = 0;
		}
	if (threecodes)
		savestack[saveptr++].int_ = s;
	savestack[saveptr].int_ = speccode;
	savestack[saveptr].int_ = val;
	saveptr += 2;
	newsavelevel(c);
	scanleftbrace();
}

halfword scantoks(bool macrodef, bool xpand)
{
	scannerstatus = macrodef ? defining : absorbing;
	warningindex = curcs;
	defref = getavail();
	token_ref_count(defref) = 0;
	auto p = defref;
	halfword hashbrace = 0;
	halfword t = zero_token;
	bool l40 = false;
	if (macrodef)
	{
		while (true)
		{
			gettoken();
			if (curtok < right_brace_limit)
			{
				store_new_token(p, end_match_token);
				if (curcmd == right_brace)
				{
					error("Missing { inserted", "Where was the left brace? You said something like `\\def\\a}',\nwhich I'm going to interpret as `\\def\\a{}'.");
					alignstate++;
					l40 = true;
					break;
				}
				break;
			}
			if (curcmd == mac_param)
			{
				auto s = match_token+curchr;
				gettoken();
				if (curcmd == left_brace)
				{
					hashbrace = curtok;
					store_new_token(p, curtok);
					store_new_token(p, end_match_token);
					break;
				}
				if (t == zero_token+9)
					error("You already have nine parameters", "I'm going to ignore the # sign you just used.");
				else
				{
					t++;
					if (curtok != t)
						backerror("Parameters must be numbered consecutively", "I've inserted the digit you should have used after the #.\nType `1' to delete what you did use.");
					curtok = s;
				}
			}
			store_new_token(p, curtok);
		}
	}
	else
		scanleftbrace();
	halfword unbalance;
	if (!l40)
		unbalance = 1;
	while (!l40)
	{
		if (xpand)
		{
			while (true)
			{
				getnext();
				if (curcmd <= max_command)
					break;
				if (curcmd != the)
					expand();
				else
				{
					auto q = thetoks();
					if (link(temp_head))
					{
						link(p) = link(temp_head);
						p = q;
					}
				}
			};
			xtoken();
		}
		else
			gettoken();
		if (curtok < right_brace_limit) 
			if (curcmd < right_brace)
				unbalance++;
			else
			{
				unbalance--;
				if (unbalance == 0)
					break;
			}
		else 
			if (curcmd == mac_param)
				if (macrodef)
				{
					auto s = curtok;
					if (xpand)
						getxtoken();
					else
						gettoken();
					if (curcmd != mac_param)
						if (curtok <= zero_token || curtok > t) 
						{
							backerror("Illegal parameter number in definition of "+scs(warningindex), "You meant to type ## instead of #, right?\nOr maybe a } was forgotten somewhere earlier, and things\nare all screwed up? I'm going to assume that you meant ##.");
							curtok = s;
						}
						else
							curtok = out_param_token-'0'+curchr;
				}
		store_new_token(p, curtok);
	}
	scannerstatus = 0;
	if (hashbrace)
		store_new_token(p, hashbrace);
	return p;
}

//! backs up a simple token list
void back_list(halfword p) { begintokenlist(p, backed_up); }

//! inserts a simple token list
void ins_list(halfword p) { begintokenlist(p, inserted); }

void begintokenlist(halfword p, quarterword t)
{
	push_input();
	state = token_list;
	start = p;
	index = t;
	if (t >= macro) //the token list starts with a reference count
	{
		add_token_ref(p);
		if (t == macro)
			param_start = paramptr;
		else
		{
			loc = link(p);
			if (tracing_macros() > 1)
			{
				switch (t)
				{
					case mark_text: 
						diagnostic("\r"+esc("mark")+"->"+tokenshow(p));
						break;
					case write_text: 
						diagnostic("\r"+esc("write")+"->"+tokenshow(p));
						break;
					default: 
						diagnostic("\r"+cmdchr(assign_toks, t-output_text+output_routine_loc)+"->"+tokenshow(p));
				}
			}
		}
	}
	else
		loc = p;
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
			flushlist(start);
			break;
		case macro:
			deletetokenref(start);
			for (;paramptr > param_start; paramptr--)
				flushlist(paramstack[paramptr]);
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
			deletetokenref(start);
	}
	pop_input();
	check_interrupt();
}

void deletetokenref(halfword p)
{
	if (info(p) == 0)
		flushlist(p);
	else
		info(p)--;
}

static halfword makeCurtok(void)
{
	if (curcs == 0)
		return (curcmd<<8)+curchr;
	else
		return cs_token_flag+curcs;
}

void gettoken(void)
{
	nonewcontrolsequence = false;
	getnext();
	nonewcontrolsequence = true;
	curtok = makeCurtok();
}

void getxtoken(void)
{
	while (true)
	{
		getnext();
		if (curcmd <= max_command)
			break;
		if (curcmd >= call)
			if (curcmd < end_template)
				macrocall();
			else
			{
				curcs = frozen_endv;
				curcmd = ignore;
				break;
			}
		else
		expand();
	}
	curtok = makeCurtok();
}

void xtoken(void)
{
	while (curcmd > max_command)
	{
		expand();
		getnext();
	}
	curtok = makeCurtok();
}

void getpreambletoken(void)
{
	while (true)
	{
		gettoken();
		while (curchr == span_code && curcmd == tab_mark)
		{
			gettoken();
			if (curcmd > max_command)
			{
				expand();
				gettoken();
			}
		}
		if (curcmd == endv)
			fatalerror("(interwoven alignment preambles are not allowed)");
		if (curcmd != assign_glue || curchr != glue_base+tab_skip_code)
			break;
		scanoptionalequals();
		(global_defs() > 0 ? geqdefine : eqdefine)(glue_base+tab_skip_code, glue_ref, scanglue(glue_val));
	}
}

void getrtoken(void)
{
	while (true)
	{
		do
			gettoken();
		while (curtok == space_token);
		if (curcs == 0 || curcs > frozen_control_sequence)
		{
			inserror("Missing control sequence inserted", "Please don't say `\\def cs{...}', say `\\def\\cs{...}'.\nI've inserted an inaccessible control sequence so that your\ndefinition will be completed without mixing me up too badly.\nYou can recover graciously from this error, if you're\ncareful; see exercise 27.2 in The TeXbook.");
			if (curcs == 0)
				backinput();
			curtok = frozen_protection+cs_token_flag;
			continue;
		}
		break;
	}
}

void insthetoks(void)
{
	link(garbage) = thetoks();
	ins_list(link(temp_head));
}

[[nodiscard]] int readtoks(int n, halfword r)
{
	scannerstatus = defining;
	warningindex = r;
	defref = getavail();
	token_ref_count(defref) = 0;
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
		loc = start;
		state = new_line;
		while (true)
		{
			gettoken();
			if (curtok == 0)
				break;
			if (alignstate < 1000000)
			{
				do
					gettoken();
				while (curtok);
				alignstate = 1000000;
				break;
			}
			auto q = getavail();
			link(p) = q;
			info(q) = curtok;
			p = q;
		}
		endfilereading();
	} while (alignstate != 1000000);
	scannerstatus = 0;
	alignstate = s;
	return defref;
}

static halfword strtoks(void)
{
	halfword p = temp_head;
	link(p) = 0;
	for (auto c: strings.back())
	{
		halfword t = c;
		if (t == ' ')
			t = space_token;
		else
			t += other_token;
		fast_store_new_token(p, t);
	}
	return p;
}

void convtoks(void)
{
	auto c = curchr;
	smallnumber savescannerstatus;
	switch (c)
	{
		case number_code:
		case roman_numeral_code: 
		case font_name_code: 
			break;
		case string_code:
		case meaning_code:
			savescannerstatus = scannerstatus;
			scannerstatus = 0;
			gettoken();
			scannerstatus = savescannerstatus;
			break;
		case job_name_code: 
			if (jobname == "")
				openlogfile();
	}
	int val;
	switch (c)
	{
		case number_code: 
			strings.push_back(std::to_string(scanint()));
			break;
		case roman_numeral_code: 
			strings.push_back(romanint(scanint()));
			break;
		case string_code: 
			strings.push_back(curcs ? scs(curcs) : std::string(1, curchr));
			break;
		case meaning_code: 
			strings.push_back(meaning());
			break;
		case font_name_code:
			val = scanfontident();
			strings.push_back(fontname[val]+(fontsize[val] != fontdsize[val] ? " at "+asScaled(fontsize[val])+"pt" : ""));
			break;
		case job_name_code: 
			strings.push_back(jobname);
	}
	link(garbage) = strtoks();
	ins_list(link(temp_head));
}

halfword thetoks(void)
{
	getxtoken();
	auto [val, lev] = scansomethinginternal(tok_val, false);
	if (lev >= ident_val)
	{
		halfword p = temp_head;
		link(p) = 0;
		if (lev == ident_val)
			store_new_token(p, cs_token_flag+val);
		else 
			if (val)
			{
				auto r = link(val);
				while (r)
				{
					fast_store_new_token(p, info(r));
					r = link(r);
				}
			}
		return p;
	}
	switch (lev)
	{
		case int_val: 
			strings.push_back(std::to_string(val));
			break;
		case dimen_val:
			strings.push_back(asScaled(val)+"pt");
			break;
		case glue_val:
			strings.push_back(asSpec(val, "pt"));
			deleteglueref(val);
			break;
		case mu_val:
			strings.push_back(asSpec(val, "mu"));
			deleteglueref(val);
	}
	return strtoks();
}

