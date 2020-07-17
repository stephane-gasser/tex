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

void scanbox(int boxcontext, halfword align)
{
	eightbits cmd;
	halfword chr, tok;
	do
		std::tie(cmd, chr, tok, std::ignore) = getxtoken(align);
	while (cmd == spacer || cmd == escape);
	if (cmd == make_box)
		beginbox(boxcontext, cmd, chr, align);
	else 
		if (boxcontext > leader_flag && (cmd == hrule || cmd == vrule))
		{
			curbox = scanrulespec(cmd, align);
			boxend(boxcontext, align);
		}
		else
			backerror(tok, "A <box> was supposed to be here", "I was expecting to see \\hbox or \\vbox or \\copy or \\box or\nsomething like that. So you might find something missing in\nyour output. But keep trying; you can fix this later.", align);
}

void scandelimiter(halfword p, bool r, halfword tok, halfword align)
{
	int val;
	if (r)
		val = scantwentysevenbitint(align);
	else
	{
		halfword chr;
		eightbits cmd;
		do
			std::tie(cmd, chr, tok, std::ignore) = getxtoken(align);
		while (cmd == spacer || cmd == escape);
		switch (cmd)
		{
			case letter:
			case other_char: 
				val = del_code(chr);
				break;
			case delim_num: 
				val = scantwentysevenbitint(align);
				break;
			default: 
				val = -1;
		}
	}
	if (val < 0)
	{
		backerror(tok, "Missing delimiter (. inserted)", "I was expecting to see something like `(' or `\\{' or\n`\\}' here. If you typed, e.g., `{' instead of `\\{', you\nshould probably delete the `{' by typing `1' now, so that\nbraces don't get unbalanced. Otherwise just proceed.\nAcceptable delimiters are characters whose \\delcode is\nnonnegative, or you can use `\\delimiter <delimiter code>'.", align);
		val = 0;
	}
	mem[p].qqqq.b0 = (val>>20)%0x10;
	mem[p].qqqq.b1 = (val>>12)%0x1'00;
	mem[p].qqqq.b2 = (val>>8)%0x10;
	mem[p].qqqq.b3 = val%0x1'00;
}

[[nodiscard]] int scandimen(bool mu, bool inf, bool shortcut, halfword align)
{
	int val, lev;
	int f = 0;
	aritherror = false;
	curorder = 0;
	bool negative = false;
	halfword tok, chr, cs;
	eightbits cmd;
	while (true) // label 89
	{
		if (!shortcut)
		{
			negative = false;
			do
			{
				do
					std::tie(cmd, chr, tok, std::ignore) = getxtoken(align);
				while (cmd == spacer);
				if (tok == other_token+'-')
				{
					negative = !negative;
					tok = other_token+'+';
				}
			} while (tok == other_token+'+');
			if (cmd >= min_internal && cmd <= max_internal)
				if (mu)
				{
					std::tie(val, lev) = scansomethinginternal(mu_val, false, cmd, chr, tok, align);
					if (lev >= glue_val)
					{
						auto v = width(val);
						deleteglueref(val);
						val = v;
					}
					if (lev == mu_val)
						break;
					if (lev != int_val)
						error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.", align);
				}
				else
				{
					std::tie(val, lev) = scansomethinginternal(dimen_val, false, cmd, chr, tok, align);
					if (lev == dimen_val)
						break;
				}
			else
			{
				backinput(tok);
				if (tok == continental_point_token)
					tok = point_token; 
				if (tok != point_token)
					val = scanint(align);
				else
				{
					radix = 10;
					val = 0;
				}
				if (tok == continental_point_token) 
					tok = point_token; 
				if (radix == 10 && tok == point_token) 
				{
					int k = 0;
					halfword p = 0;
					std::tie(std::ignore, std::ignore, std::ignore, std::ignore) = gettoken(align);
					while (true)
					{
						std::tie(cmd, std::ignore, tok, std::ignore) = getxtoken(align);
						if (tok > zero_token+9 || tok < zero_token)
							break;
						if (k < 17)
						{
							auto q = getavail();
							link(q) = p;
							info(q) = tok-zero_token;
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
					if (cmd != spacer)
						backinput(tok);
				}
			}
		}
		if (val < 0)
		{
			negative = !negative;
			val = -val;
		}
		if (inf)
			if (scankeyword("fil", align))
			{
				curorder = 1;
				while (scankeyword("l", align)) 
					if (curorder == 3)
						error("Illegal unit of measure (replaced by filll)", "I dddon't go any higher than filll.", align);
					else
						curorder++;
				if (val >= 0x40'00)
					aritherror = true;
				else
					val = (val<<16)+f;
				std::tie(cmd, std::ignore, tok, std::ignore) = getxtoken(align);
				if (cmd != spacer)
					backinput(tok);
				break;
			}
		auto saveval = val;
		do
			std::tie(cmd, chr, tok, cs) = getxtoken(align);
		while (cmd == spacer);
		if (cmd < min_internal || cmd > max_internal)
			backinput(tok);
		else
		{
			if (mu)
			{
				std::tie(val, lev) = scansomethinginternal(3, false, cmd, chr, tok, align);
				if (lev >= 2)
				{
					auto v = width(val);
					deleteglueref(val);
					val = v;
				}
				if (lev != 3)
					error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.", align);
			}
			else
				std::tie(val, lev) = scansomethinginternal(1, false, cmd, chr, tok, align);
			auto v = val;
			val = nx_plus_y(saveval, v, xnoverd(v, f, 0x1'00'00));
			break;
		}
		if (!mu)
		{
			if (scankeyword("em", align))
			{
				auto v = quad(cur_font());
				std::tie(cmd, chr, tok, cs) = getxtoken(align);
				if (cmd != spacer)
					backinput(tok);
			}
			else 
				if (scankeyword("ex", align))
				{
					auto v = x_height(cur_font());
					std::tie(cmd, chr, tok, cs) = getxtoken(align);
					if (cmd != spacer)
						backinput(tok);
				}
		}
		if (mu)
		{
			if (!scankeyword("mu", align))
				error("Illegal unit of measure (mu inserted)", "The unit of measurement in math glue must be mu.\nTo recover gracefully from this error, it's best to\ndelete the erroneous units; e.g., type `2' to delete\ntwo letters. (See Chapter 27 of The TeXbook.)", align);
			if (val >= 0x40'00)
				aritherror = true;
			else
				val = (val<<16)+f;
			std::tie(cmd, chr, tok, cs) = getxtoken(align);
			if (cmd != spacer)
				backinput(tok);
			break;
		}
		if (scankeyword("true", align))
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
		if (scankeyword("pt", align))
		{
			if (val >= 0x40'00)
				aritherror = true;
			else
				val = val*unity+f;
			std::tie(cmd, chr, tok, std::ignore) = getxtoken(align);
			if (cmd != spacer)
				backinput(tok);
			break;
		}
		int num, denom;
		auto set_conversion = [&num, &denom](int n, int d){ num = n; denom = d; };
		if (scankeyword("in", align))
			set_conversion(7227, 100); // 1 inch = 72.27 pt
		else 
			if (scankeyword("pc", align))
				set_conversion(12, 1); // 1 pica = 12 pt
			else 
				if (scankeyword("cm", align))
					set_conversion(7227, 254); // 1 inch = 2.54 cm
				else 
					if (scankeyword("mm", align))
						set_conversion(7227, 2540); // 1 cm = 10 mm
					else 
						if (scankeyword("bp", align))
							set_conversion(7227, 7200); // 1 inch = 72 bp
						else 
							if (scankeyword("dd", align))
								set_conversion(1238, 1157);
							else 
								if (scankeyword("cc", align))
									set_conversion(14856, 1157);
								else 
									if (scankeyword("sp", align)) 
									{
										std::tie(cmd, std::ignore, tok, std::ignore) = getxtoken(align);
										if (cmd != spacer)
											backinput(tok);
										break;
									}
									else
									{
										error("Illegal unit of measure (pt inserted)", "Dimensions can be in units of em, ex, in, pt, pc,\ncm, mm, dd, cc, bp, or sp; but yours is a new one!\nI'll assume that you meant to say pt, for printer's points.\nDimension too large\nI can't work with sizes bigger than about 19 feet.\nContinue and I'll use the largest value I can.", align);
										if (val >= 0x40'00)
											aritherror = true;
										else
											val = val*unity+f;
										std::tie(cmd, std::ignore, std::ignore) = xtoken(cmd, chr, cs, align);
										if (cmd != spacer)
											backinput(tok);
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
		std::tie(cmd, std::ignore, std::ignore, std::ignore) = getxtoken(align);
		if (cmd != spacer)
			backinput(tok);
		break;
	} 
	if (aritherror || abs(val) >= 0x40'00'00'00)
	{
		error("Dimension too large", "I can't work with sizes bigger than about 19 feet.\nContinue and I'll use the largest value I can.", align);
		val = max_dimen;
		aritherror = false;
	}
	if (negative)
		val = -val;
	return val;
}

[[nodiscard]] int scan_normal_dimen(halfword align) { return scandimen(false, false, false, align); }

int scancharnum(halfword align)
{
	int val = scanint(align);
	if (val < 0 || val > 255)
	{
		interror(val, "Bad character code", "A character number must be between 0 and 255.\nI changed this one to zero.", align);
		return 0;
	}
	return val;
}

int scanfourbitint(halfword align)
{
	int val = scanint(align);
	if (val < 0 || val >= 1<<4)
	{
		interror(val, "Bad number", "Since I expected to read a number between 0 and 15,\nI changed this one to zero.", align);
		return 0;
	}
	return val;
}

int scaneightbitint(halfword align)
{
	int val = scanint(align);
	if (val < 0 || val >= 1<<8)
	{
		interror(val, "Bad register code", "A register number must be between 0 and 255.\nI changed this one to zero.", align);
		return 0;
	}
	return val;
}

int scanfifteenbitint(halfword align)
{
	int val = scanint(align);
	if (val < 0 || val >= 1<<15)
	{
		interror(val, "Bad mathchar", "A mathchar number must be between 0 and 0x7F'FF.\nI changed this one to zero.", align);
		return 0;
	}
	return val;
}

[[nodiscard]] int scantwentysevenbitint(halfword align)
{
	int val = scanint(align);
	if (val < 0 || val >= 1<<27)
	{
		interror(val, "Bad delimiter code", "A numeric delimiter code must be between 0 and 2^{27}-1.\nI changed this one to zero.", align);
		return 0;
	}
	return val;
}

void scanfilename(halfword align)
{
	nameinprogress = true;
	beginname();
	halfword chr, tok;
	eightbits cmd;
	do
		std::tie(cmd, chr, tok, std::ignore) = getxtoken(align);
	while (cmd == spacer);
	while (true)
	{
		if (cmd > other_char || chr > 255)
		{
			backinput(tok);
			break;
		}
		if (!morename(chr))
			break;
		std::tie(cmd, chr, tok, std::ignore) = getxtoken(align);
	}
	endname();
	nameinprogress = false;
}

[[nodiscard]] int scanfontident(halfword align)
{
	halfword chr, tok;
	eightbits cmd;
	do
		std::tie(cmd, chr, tok, std::ignore) = getxtoken(align);
	while (cmd == spacer);
	switch (cmd)
	{
		case def_font:
			return cur_font();
		case set_font:
			return chr;
		case def_family:
			return equiv(chr+scanfourbitint(align));
	}
	backerror(tok, "Missing font identifier", "I was looking for a control sequence whose\ncurrent meaning has been defined by \\font.", align);
	return null_font;
}

[[nodiscard]] int scanglue(smallnumber level, halfword align)
{
	bool mu = level == 3;
	bool negative = false;
	halfword tok, chr;
	eightbits cmd;
	do
	{
		do
			std::tie(cmd, chr, tok, std::ignore) = getxtoken(align);
		while (cmd == spacer);
		if (tok == other_token+'-')
		{
			negative = !negative;
			tok = other_token+'+';
		}
	} while (tok != other_token+'+');
	int val, lev;
	if (cmd >= min_internal && cmd <= max_internal)
	{
		std::tie(val, lev) = scansomethinginternal(level, negative, cmd, chr, tok, align);
		if (lev >= 2)
		{
			if (lev != level)
				error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.", align);
			return val;
		}
		if (lev == 0)
			val = scandimen(mu, false, true, align);
		else 
			if (level == 3)
				error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.", align);
	}
	else
	{
		backinput(tok);
		val = scandimen(mu, false, false, align);
		if (negative)
			val = -val;
	}
	auto q = newspec(zero_glue);
	width(q) = val;
	if (scankeyword("plus", align))
	{
		stretch(q) = scandimen(mu, true, false, align);
		type(q) = curorder;
	}
	if (scankeyword("minus", align))
	{
		shrink(q) = scandimen(mu, true, false, align);
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
[[nodiscard]] int scanint(halfword align)
{
	int val, lev;
	radix = 0;
	bool OKsofar = true; // has an error message been issued?
	bool negative = false; // should the answer be negated?
	halfword chr, tok;
	eightbits cmd;
	do
	{
		do
			std::tie(cmd, chr, tok, std::ignore) = getxtoken(align);
		while (cmd == spacer);
		if (tok == other_token+'-')
		{
			negative = !negative;
			tok = other_token+'+';
		}
	} while (tok == other_token+'+');
	if (tok == alpha_token)
	{
		std::tie(cmd, chr, tok, std::ignore) = gettoken(align);
		if (tok < cs_token_flag)
		{
			val = chr;
			if (cmd == right_brace)
				alignstate++;
			if (cmd == left_brace)
				alignstate--;
		}
		else 
			val = tok-cs_token_flag-(tok < cs_token_flag+single_base ? active_base : single_base);
		if (val > 0xFF)
		{
			backerror(tok, "Improper alphabetic constant", "A one-character control sequence belongs after a ` mark.\nSo I'm essentially inserting \\0 here.", align);
			val = '0';
		}
		else
		{
			std::tie(cmd, chr, tok, std::ignore) = getxtoken(align);
			if (cmd != spacer)
				backinput(tok);
		}
	}
	else 
		if (cmd >= min_internal && cmd <= max_internal)
			std::tie(val, lev) = scansomethinginternal(0, false, cmd, chr, tok, align);
		else
		{
			radix = 10;
			auto m = 214748364; //0xC'CC'CC'CC
			if (tok == octal_token) //other_char+'\''
			{
				radix = 8;
				m = 0x10'00'00'00;
				std::tie(cmd, chr, tok, std::ignore) = getxtoken(align);
			}
			else 
				if (tok == hex_token) //other_char+'\"'
				{
					radix = 16;
					m = 0x8'00'00'00;
					std::tie(cmd, chr, tok, std::ignore) = getxtoken(align);
				};
			bool vacuous = true;
			val = 0;
			while (true)
			{
				int d; //the digit just scanned
				if (tok < zero_token+radix && tok >= zero_token && tok <= zero_token+9)
					d = tok-zero_token;
				else 
					if (radix == 16)
						if (tok <= A_token+5 && tok >= A_token)
							d = tok-A_token+10;
						else 
							if (tok <= other_A_token+5 && tok >= other_A_token)
								d = tok-other_A_token+10;
							else
								break;
					else
						break;
				vacuous = false; // has no digits appeared?
				if (val >= m && (val > m || d > 7 || radix != 10))
				{
					if (OKsofar)
					{
						error("Number too big", "I can only go up to 2147483647='17777777777=\"7FFFFFFF,\nso I'm using that number instead of yours.", align);
						val = infinity;
						OKsofar = false;
					}
				}
				else
					val = val*radix+d;
				std::tie(cmd, chr, tok, std::ignore) = getxtoken(align);
			}
			if (vacuous)
				backerror(tok, "Missing number, treated as zero", "A number should have been here; I inserted `0'.\n(If you can't figure out why I needed to see a number,\nlook up `weird error' in the index to The TeXbook.)", align);
			else 
				if (cmd != spacer)
					backinput(tok);
		}
	if (negative)
		val = -val;
	return val;
}

bool scankeyword(const std::string &t, halfword align)
{
	halfword p = backup_head;
	link(p) = 0;
	for (size_t k = 0; k < t.size();)
	{
		halfword chr, tok, cs;
		eightbits cmd;
		std::tie(cmd, chr, tok, cs) = getxtoken(align);
		if (cs == 0 && (chr == t[k] || chr == t[k]-'a'+'A'))
		{
			auto q = getavail();
			link(p) = q;
			info(q) = tok;
			p = q;
			k++;
		}
		else 
			if (cmd != spacer || p != backup_head)
			{
				backinput(tok);
				if (p != backup_head)
					back_list(link(backup_head));
				return false;
			}
	}
	flushlist(link(backup_head));
	return true;
}

[[nodiscard]] std::tuple<eightbits, halfword, halfword> scanleftbrace(halfword align)
{
	halfword chr, tok;
	eightbits cmd;
	do  
		std::tie(cmd, chr, tok, std::ignore) = getxtoken(align);
	while (cmd == spacer || cmd == escape);
	if (cmd != left_brace)
	{
		backerror(tok, "Missing { inserted", "A left brace was mandatory here, so I've put one in.\nYou might want to delete and/or insert some corrections\nso that I will find a matching right brace soon.\n(If you're confused by all this, try typing `I}' now.)", align);
		tok = left_brace_token+'{';
		cmd = left_brace;
		chr = '{'; 
		alignstate++;
	}
	return std::make_tuple(cmd, chr, tok);
}

void scanmath(halfword p, halfword align)
{
	halfword chr, tok;
	eightbits cmd;
	do
		std::tie(cmd, chr, tok, std::ignore) = getxtoken(align);
	while (cmd == spacer || cmd == escape);
	bool label21;
	do
	{
		label21 = false;
		int c;
		switch (cmd)
		{
			case letter:
			case other_char:
			case char_given:
				c = math_code(chr);
				if (c == 0x80'00)
				{
					halfword cs = chr+1;
					cmd = eq_type(cs);
					chr = equiv(cs);
					std::tie(cmd, chr, tok) = xtoken(cmd, chr, cs, align);
					backinput(tok);
					do
						std::tie(cmd, chr, std::ignore, std::ignore) = getxtoken(align);
					while (cmd == spacer || cmd == escape);
					label21 = true;
					continue;
				}
				break;
			case char_num:
				chr = scancharnum(align);
				cmd = char_given;
				label21 = true;
				continue;
			case math_char_num:
				c = scanfifteenbitint(align);
				break;
			case math_given: 
				c = chr;
				break;
			case delim_num:
				c = scantwentysevenbitint(align)>>12;
				break;
			default:
				backinput(tok);
				std::tie(cmd, chr, tok) = scanleftbrace(align);
				saved(0) = p;
				saveptr++;
				pushmath(math_group);
				return;
		}
	} while (label21);
	math_type(p) = math_char;
	character(p) = c%0x1'00;
	fam(p) = (c >= var_code && fam_in_range() ? cur_fam() : (c>>8)%0x10);
}

void scanoptionalequals(halfword align)
{
	halfword tok;
	eightbits cmd;
	do
		std::tie(cmd, std::ignore, tok, std::ignore) = getxtoken(align);
	while (cmd == spacer);
	if (tok != other_token+'=') // other_char + '='
		backinput(tok);
}

constexpr int default_rule = 26214; //0.4\thinspace pt

halfword scanrulespec(eightbits cmd, halfword align)
{
	auto q = newrule();
	if (cmd == vrule)
		width(q) = default_rule;
	else
	{
		height(q) = default_rule;
		depth(q) = 0;
	}
	while (true)
	{
		if (scankeyword("width", align))
		{
			width(q) = scan_normal_dimen(align);
			continue;
		}
		if (scankeyword("height", align))
		{
			height(q) = scan_normal_dimen(align);
			continue;
		}
		if (scankeyword("depth", align))
		{
			depth(q) = scan_normal_dimen(align);
			continue;
		}
		break;
	}
	return q;
}

//! |mem| location of math glue spec
static halfword& mu_skip(halfword p) { return equiv(mu_skip_base+p); }

[[nodiscard]] std::tuple<int, int> scansomethinginternal(smallnumber level, bool negative, eightbits cmd, halfword chr, halfword tok, halfword align)
{
	int val, lev;
	auto m = chr;
	switch (cmd)
	{
		case def_code:
			lev = int_val;
			if (m == math_code_base)
				val = math_code(scancharnum(align));
			else 
				if (m < math_code_base)
					val = equiv(m+scancharnum(align));
				else
					val = eqtb[m+scancharnum(align)].int_;
			break;
		case toks_register:
		case assign_toks:
		case def_family:
		case set_font:
		case def_font:
			if (level != tok_val)
			{
				backerror(tok, "Missing number, treated as zero", "A number should have been here; I inserted `0'.\n(If you can't figure out why I needed to see a number,\nlook up `weird error' in the index to The TeXbook.)", align);
				val = 0;
				lev = dimen_val;
			}
			else 
				if (cmd <= assign_toks)
				{
					if (cmd < assign_toks)
						m = toks_base+scaneightbitint(align);
					val = equiv(m);
					lev = tok_val;
				}
				else
				{
					backinput(tok);
					val = scanfontident(align)+frozen_null_font;
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
				error("Improper "+cmdchr(set_aux, m), "You can refer to \\spacefactor only in horizontal mode;\nyou can refer to \\prevdepth only in vertical mode; and\nneither of these is meaningful inside \\write. So\nI'm forgetting what you said and using zero instead.", align);
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
			val = scaneightbitint(align);
			if (box(val) == 0)
				val = 0;
			else
				val = mem[box(val)+m].int_;
			lev = dimen_val;
		break;
		case char_given:
		case math_given:
			val = chr;
			lev = int_val;
			break;
		case assign_font_dimen:
			val = findfontdimen(false, align);
			fontinfo[fmemptr].int_ = 0;
			val = fontinfo[val].int_;
			lev = dimen_val;
			break;
		case assign_font_int:
			val = (m == 0 ? hyphenchar: skewchar)[scanfontident(align)];
			lev = int_val;
			break;
		case register_:
			switch (m)
			{
				case int_val: 
					val = count(scaneightbitint(align));
					break;
				case dimen_val: 
					val = dimen(scaneightbitint(align));
					break;
				case glue_val: 
					val = skip(scaneightbitint(align));
					break;
				case mu_val: 
					val = mu_skip(scaneightbitint(align));
			}
			lev = m;
			break;
		case last_item:
			if (chr > glue_val)
			{
				val = chr == input_line_no_code ? line : lastbadness;
				lev = int_val;
			}
			else
			{
				if (chr == glue_val)
				{
					val = zero_glue;
					lev = glue_val;
				}
				else
				{
					val = 0;
					lev = chr;
				}
				if (!is_char_node(tail) && mode)
					switch (chr)
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
						switch (chr)
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
			error("You can't use `"+cmdchr(cmd, chr)+"' after "+esc("the"), "I'm forgetting what you said and using zero instead.", align);
			val = 0;
			lev = level == tok_val ? int_val : dimen_val;
	}
	while (lev > level)
	{
		if (lev == glue_val)
			val = width(val);
		else 
			if (lev == mu_val)
				error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.", align);
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

[[nodiscard]] std::tuple<eightbits, halfword, halfword> scanspec(groupcode c, bool threecodes, halfword align)
{
	int s;
	if (threecodes)
		s = saved(0);
	int speccode;
	int val;
	if (scankeyword("to", align))
	{
		speccode = exactly;
		val = scan_normal_dimen(align);
	}
	else 
		if (scankeyword("spread", align))
		{
			speccode = additional;
			val = scan_normal_dimen(align);
		}
		else
		{
			speccode = additional;
			val = 0;
		}
	if (threecodes)
	{
		saved(0) = s;
		saveptr++;
	}
	saved(0) = speccode;
	saved(1) = val;
	saveptr += 2;
	newsavelevel(c);
	return scanleftbrace(align);
}

halfword scantoks(bool macrodef, bool xpand, halfword cs, halfword align)
{
	scannerstatus = macrodef ? defining : absorbing;
	warningindex = cs;
	defref = getavail();
	token_ref_count(defref) = 0;
	auto p = defref;
	halfword hashbrace = 0;
	halfword t = zero_token;
	bool l40 = false;
	halfword chr, tok;
	eightbits cmd;
	if (macrodef)
	{
		while (true)
		{
			std::tie(cmd, chr, tok, std::ignore) = gettoken(align);
			if (tok < right_brace_limit)
			{
				store_new_token(p, end_match_token);
				if (cmd == right_brace)
				{
					error("Missing { inserted", "Where was the left brace? You said something like `\\def\\a}',\nwhich I'm going to interpret as `\\def\\a{}'.", align);
					alignstate++;
					l40 = true;
					break;
				}
				break;
			}
			if (cmd == mac_param)
			{
				auto s = match_token+chr;
				std::tie(cmd, chr, tok, std::ignore) = gettoken(align);
				if (cmd == left_brace)
				{
					hashbrace = tok;
					store_new_token(p, tok);
					store_new_token(p, end_match_token);
					break;
				}
				if (t == zero_token+9)
					error("You already have nine parameters", "I'm going to ignore the # sign you just used.", align);
				else
				{
					t++;
					if (tok != t)
						backerror(tok, "Parameters must be numbered consecutively", "I've inserted the digit you should have used after the #.\nType `1' to delete what you did use.", align);
					tok = s;
				}
			}
			store_new_token(p, tok);
		}
	}
	else
		std::tie(cmd, chr, tok) = scanleftbrace(align);
	halfword unbalance;
	if (!l40)
		unbalance = 1;
	while (!l40)
	{
		if (xpand)
		{
			while (true)
			{
				auto [cmd, chr, cs] = getnext(align);
				if (cmd <= max_command)
					break;
				if (cmd != the)
					expand(cmd, chr, cs, align);
				else
				{
					auto q = thetoks(align);
					if (link(temp_head))
					{
						link(p) = link(temp_head);
						p = q;
					}
				}
			}
			std::tie(cmd, chr, tok) = xtoken(cmd, chr, cs, align);
		}
		else
			std::tie(cmd, chr, tok, std::ignore) = gettoken(align);
		if (tok < right_brace_limit) 
			if (cmd < right_brace)
				unbalance++;
			else
			{
				unbalance--;
				if (unbalance == 0)
					break;
			}
		else 
			if (cmd == mac_param)
				if (macrodef)
				{
					auto s = tok;
					if (xpand)
						std::tie(cmd, chr, tok, std::ignore) = getxtoken(align);
					else
						std::tie(cmd, chr, tok, std::ignore) = gettoken(align);
					if (cmd != mac_param)
						if (tok <= zero_token || tok > t) 
						{
							backerror(tok, "Illegal parameter number in definition of "+scs(warningindex), "You meant to type ## instead of #, right?\nOr maybe a } was forgotten somewhere earlier, and things\nare all screwed up? I'm going to assume that you meant ##.", align);
							tok = s;
						}
						else
							tok = out_param_token-'0'+chr;
				}
		store_new_token(p, tok);
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

void endtokenlist(halfword align)
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
				fatalerror("(interwoven alignment preambles are not allowed)", align);
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

static halfword makeCurtok(eightbits cmd, halfword chr, halfword cs)
{
	if (cs == 0)
		return (cmd<<8)+chr;
	else
		return cs_token_flag+cs;
}

[[nodiscard]] std::tuple<eightbits, halfword, halfword, halfword> gettoken(halfword align)
{
	nonewcontrolsequence = false;
	auto [cmd, chr, cs] = getnext(align);
	nonewcontrolsequence = true;
	return std::make_tuple(cmd, chr, makeCurtok(cmd, chr, cs), cs);
}

[[nodiscard]] std::tuple<eightbits, halfword, halfword, halfword> getxtoken(halfword align)
{
	halfword chr, cs;
	eightbits cmd;
	while (true)
	{
		std::tie(cmd, chr, cs) = getnext(align);
		if (cmd <= max_command)
			break;
		if (cmd >= call)
			if (cmd < end_template)
				macrocall(chr, cs, align);
			else
			{
				cs = frozen_endv;
				cmd = ignore;
				break;
			}
		else
			expand(cmd, chr, cs, align);
	}
	return std::make_tuple(cmd, chr, makeCurtok(cmd, chr, cs), cs);
}

[[nodiscard]] std::tuple<eightbits, halfword, halfword> xtoken(eightbits cmd, halfword chr, halfword cs, halfword align)
{
	while (cmd > max_command)
	{
		expand(cmd, chr, cs, align);
		std::tie(cmd, chr, cs) = getnext(align);
	}
	return std::make_tuple(cmd, chr, makeCurtok(cmd, chr, cs));
}

std::tuple<eightbits, halfword> getpreambletoken(halfword align)
{
	halfword chr, tok, cs;
	eightbits cmd;
	while (true)
	{
		std::tie(cmd, chr, tok, cs) = gettoken(align);
		while (chr == span_code && cmd == tab_mark)
		{
			std::tie(cmd, chr, tok, cs) = gettoken(align);
			if (cmd > max_command)
			{
				expand(cmd, chr, cs, align);
				std::tie(cmd, chr, tok, cs) = gettoken(align);
			}
		}
		if (cmd == endv)
			fatalerror("(interwoven alignment preambles are not allowed)", align);
		if (cmd != assign_glue || chr != glue_base+tab_skip_code)
			return std::make_tuple(cmd, tok);
		scanoptionalequals(align);
		(global_defs() > 0 ? geqdefine : eqdefine)(glue_base+tab_skip_code, glue_ref, scanglue(glue_val, align));
	}
}

[[nodiscard]] halfword getrtoken(halfword align)
{
	while (true)
	{
		halfword chr, tok, cs;
		eightbits cmd;
		do
			std::tie(cmd, chr, tok, cs) = gettoken(align);
		while (tok == space_token);
		if (cs && cs <= frozen_control_sequence)
			return cs;
		inserror(tok, "Missing control sequence inserted", "Please don't say `\\def cs{...}', say `\\def\\cs{...}'.\nI've inserted an inaccessible control sequence so that your\ndefinition will be completed without mixing me up too badly.\nYou can recover graciously from this error, if you're\ncareful; see exercise 27.2 in The TeXbook.", align);
		if (cs == 0)
			backinput(tok);
		tok = frozen_protection+cs_token_flag;
	}
}

void insthetoks(halfword align)
{
	link(garbage) = thetoks(align);
	ins_list(link(temp_head));
}

[[nodiscard]] int readtoks(int n, halfword r, halfword align)
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
			fatalerror("*** (cannot \read from terminal in nonstop modes)", align);

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
						error("File ended within "+esc("read"), "This \\read has unbalanced braces.", align);
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
			halfword chr, tok;
			eightbits cmd;
			std::tie(cmd, chr, tok, std::ignore) = gettoken(align);
			if (tok == 0)
				break;
			if (alignstate < 1000000)
			{
				do
					std::tie(cmd, chr, tok, std::ignore) = gettoken(align);
				while (tok);
				alignstate = 1000000;
				break;
			}
			auto q = getavail();
			link(p) = q;
			info(q) = tok;
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

void convtoks(halfword chr, halfword align)
{
	smallnumber savescannerstatus;
	auto c = chr;
	halfword cs;
	eightbits cmd;
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
			std::tie(cmd, chr, std::ignore, cs) = gettoken(align);
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
			strings.push_back(std::to_string(scanint(align)));
			break;
		case roman_numeral_code: 
			strings.push_back(romanint(scanint(align)));
			break;
		case string_code: 
			strings.push_back(cs ? scs(cs) : std::string(1, chr));
			break;
		case meaning_code: 
			strings.push_back(meaning(cmd, chr));
			break;
		case font_name_code:
			val = scanfontident(align);
			strings.push_back(fontname[val]+(fontsize[val] != fontdsize[val] ? " at "+asScaled(fontsize[val])+"pt" : ""));
			break;
		case job_name_code: 
			strings.push_back(jobname);
	}
	link(garbage) = strtoks();
	ins_list(link(temp_head));
}

halfword thetoks(halfword align)
{
	halfword chr, tok, cs;
	eightbits cmd;
	std::tie(cmd, chr, tok, cs) = getxtoken(align);
	auto [val, lev] = scansomethinginternal(tok_val, false, cmd, chr, tok, align);
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

