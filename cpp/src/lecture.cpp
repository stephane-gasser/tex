#include "lecture.h"
#include "boite.h"
#include "chaine.h"
#include "getnext.h"
#include "police.h"
#include "expand.h"
#include "pushmath.h"
#include "noeud.h"
#include "alignement.h"
#include "impression.h"
#include "calcul.h"
#include "erreur.h"
#include "preparemag.h"
#include "etat.h"
#include "equivalent.h"
#include "macrocall.h" 
#include "fichier.h"
#include "sauvegarde.h"
#include "buildpage.h"

void Scanner::somethingInternal(char status, smallnumber level, bool negative, Token t)
{
	// lev/level : tok_val/dimen_val/glue_val/ident_val/int_val/mu_val
	try
	{
		switch (t.cmd)
		{
			// int_val
			case def_code:
				lev = int_val;
				val = t.chr == math_code_base ? math_code(scanner.getUChar(status)) : t.chr < math_code_base ? eqtb_local[t.chr+scanner.getUChar(status)-local_base].int_ : eqtb_int[t.chr+scanner.getUChar(status)-int_base].int_;
				break;
			case assign_int:
				val = eqtb_int[t.chr-int_base].int_;
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
				val =  t.chr == 0 ? deadcycles : insertpenalties;
				lev = int_val;
				break;
			case set_shape:
				val = 0;
				if (par_shape_ptr())
					val = par_shape_ptr()->values.size()/2;
				lev = int_val;
				break;
			case char_given:
			case math_given:
				val = t.chr;
				lev = int_val;
				break;
			case assign_font_int:
				val = t.chr == 0 ? fonts[scanner.getFontIdent(status)].hyphenchar : fonts[scanner.getFontIdent(status)].skewchar;
				lev = int_val;
				break;
			// tok_val
			case toks_register:
			case assign_toks:
				if (level != tok_val)
					throw 1;
				if (t.cmd == toks_register)
					t.chr = toks_base+scanner.getUInt8(status);
				tk = dynamic_cast<TokenList*>(eqtb_local[t.chr-local_base].index);
				lev = tok_val;
				break;
			// ident_val
			case def_family:
			case set_font:
			case def_font:
				if (level != tok_val)
					throw 1;
				backinput(t);
				val = scanner.getFontIdent(status)+frozen_null_font;
				lev = ident_val;
				break;
			// dimen_val
			case assign_dimen:
				val = eqtb_dimen[t.chr-dimen_base].int_;
				lev = dimen_val;
				break;
			case set_page_dimen:
				if (pagecontents == 0 && !outputactive)
					val = t.chr == 0 ? max_dimen : 0;
				else
					val = pagesofar[t.chr];
				lev = dimen_val;
				break;
			case set_box_dimen:
				val = scanner.getUInt8(status);
				val = 0;
				if (box(val))
					switch (t.chr)
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
			case assign_font_dimen:
				val = findfontdimen(status, false);
				Font::info.back().int_ = 0;
				val = Font::info[val].int_;
				lev = dimen_val;
				break;
			// glue_val
			case assign_glue:
				gl = dynamic_cast<GlueSpec*>(eqtb_glue[t.chr-glue_base].index); 
				lev = glue_val;
				break;
			// mu_val
			case assign_mu_glue:
				gl = dynamic_cast<GlueSpec*>(eqtb_glue[t.chr-glue_base].index);
				lev = mu_val;
				break;
			// mixed
			case set_aux:
				if (abs(mode) != t.chr)
					throw 2;
				if (t.chr == vmode)
				{
					val = prev_depth;
					lev = dimen_val;
					break;
				}
				val = space_factor;
				lev = int_val;
				break;
			case register_:
				switch (t.chr)
				{
					case int_val: 
						val = count(scanner.getUInt8(status));
						break;
					case dimen_val: 
						val = dimen(scanner.getUInt8(status));
						break;
					case glue_val: 
						gl = skip(scanner.getUInt8(status));
						break;
					case mu_val: 
						gl = mu_skip(scanner.getUInt8(status));
				}
				lev = t.chr;
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
						case int_val: // \lastpenalty
							if (tail->type == penalty_node) 
								val = tail->getPenalty();
							break;
						case dimen_val: // \lastkern
							if (tail->type == kern_node) 
								val = tail->getWidth();
							break;
						case glue_val: // \lastskip
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
				throw 0;
		}
	}
	catch (int e)
	{
		switch (e)
		{
			case 1:
				backerror(t, "Missing number, treated as zero", "A number should have been here; I inserted `0'.\n(If you can't figure out why I needed to see a number,\nlook up `weird error' in the index to The TeXbook.)");
				lev = dimen_val;
				break;
			case 2:
				error("Improper "+t.cmdchr(), "You can refer to \\spacefactor only in horizontal mode;\nyou can refer to \\prevdepth only in vertical mode; and\nneither of these is meaningful inside \\write. So\nI'm forgetting what you said and using zero instead.");
				lev = level == tok_val ? int_val : dimen_val;
				break;
			default:
				error("You can't use `"+t.cmdchr()+"' after "+esc("the"), "I'm forgetting what you said and using zero instead.");
				lev = level == tok_val ? int_val : dimen_val;
		}
		val = 0;
	}
	while (lev > level)
	{
		if (lev == glue_val)
			val = gl->width;
		else 
			if (lev == mu_val)
				error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.");
		lev--;
	}
	if (negative)
		if (lev >= glue_val)
		{
			auto G = new GlueSpec(gl);
			G->width = -G->width;
			G->stretch = -G->stretch;
			G->shrink = -G->shrink;
			gl = G;
		}
		else
			val = -val;
	else 
		if (lev >= glue_val && lev <= mu_val)
			gl->glue_ref_count++;
}

void Scanner::getBox(char status, int boxcontext)
{
	auto t = getXSkipSpaceAndEscape(status);
	switch (t.cmd)
	{
		case make_box:
			beginbox(status, boxcontext, t);
			break;
		case hrule:
		case vrule:
			if (boxcontext > leader_flag)
			{
				boxend(status, boxcontext, new RuleNode(status, t));
				break;
			}
			[[fallthrough]];
		default:
			backerror(t, "A <box> was supposed to be here", "I was expecting to see \\hbox or \\vbox or \\copy or \\box or\nsomething like that. So you might find something missing in\nyour output. But keep trying; you can fix this later.");
	}
}

void Delimiter::scan(char status, bool r, Token t)
{
	int val = -1;
	if (r)
		val = scanner.getUInt27(status);
	else
	{
		t = scanner.getXSkipSpaceAndEscape(status);
		switch (t.cmd)
		{
			case letter:
			case other_char: 
				val = del_code(t.chr);
				break;
			case delim_num: 
				val = scanner.getUInt27(status);
		}
	}
	if (val < 0)
	{
		backerror(t, "Missing delimiter (. inserted)", "I was expecting to see something like `(' or `\\{' or\n`\\}' here. If you typed, e.g., `{' instead of `\\{', you\nshould probably delete the `{' by typing `1' now, so that\nbraces don't get unbalanced. Otherwise just proceed.\nAcceptable delimiters are characters whose \\delcode is\nnonnegative, or you can use `\\delimiter <delimiter code>'.");
		val = 0;
	}
	small_fam = (val>>20)%(1<<4);
	small_char = (val>>12)%(1<<8);
	large_fam = (val>>8)%(1<<4);
	large_char = val%(1<<8);
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

void calc(bool &aritherror, int &val, int f)
{
	if (val >= 1<<14)
		aritherror = true;
	else
		val = (val<<16)+f;
}

int Scanner::getDimen(char status, bool mu, bool inf, bool shortcut)
{
	int decimales = 0;
	aritherror = false;
	curorder = 0;
	bool negative = false;
	while (true)
	{
		Token t;
		if (!shortcut)
		{
			negative = false;
			do
			{
				t = getXSkipSpace(status);
				if (t.tok == other_token+'-')
					negative = !negative;
			} while (t.tok == other_token+'+' || t.tok == other_token+'-');
			if (t.cmd >= min_internal && t.cmd <= max_internal)
				if (mu)
				{
					somethingInternal(status, mu_val, false, t);
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
					somethingInternal(status, dimen_val, false, t);
					if (lev == dimen_val)
						break;
				}
			else
			{
				backinput(t);
				if (t.tok != point_token && t.tok != continental_point_token)
					val = getInt(status);
				else
				{
					radix = 10;
					val = 0;
				}
				if (radix == 10 && (t.tok == point_token || t.tok == continental_point_token)) 
				{
					t = get(status);
					for (int k = 0; true; k++)
					{
						t = getX(status);
						if (!between(zero_token, t.tok, zero_token+9))
						{
							decimales = rounddecimals(k);
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
			val *= -1;
		}
		if (inf)
			if (isKeyword(status, "fil"))
			{
				curorder = 1;
				while (isKeyword(status, "l")) 
					if (curorder == 3)
						error("Illegal unit of measure (replaced by filll)", "I dddon't go any higher than filll.");
					else
						curorder++;
				calc(aritherror, val, decimales);
				t = getX(status);
				if (t.cmd != spacer)
					backinput(t);
				break;
			}
		auto saveval = val;
		t = getXSkipSpace(status);
		if (t.cmd < min_internal || t.cmd > max_internal)
			backinput(t);
		else
		{
			if (mu)
			{
				somethingInternal(status, mu_val, false, t);
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
				somethingInternal(status, dimen_val, false, t);
			val = nx_plus_y(saveval, val, xnoverd(val, decimales, unity));
			break;
		}
		if (mu)
		{
			if (!isKeyword(status, "mu"))
				error("Illegal unit of measure (mu inserted)", "The unit of measurement in math glue must be mu.\nTo recover gracefully from this error, it's best to\ndelete the erroneous units; e.g., type `2' to delete\ntwo letters. (See Chapter 27 of The TeXbook.)");
			calc(aritherror, val, decimales);
			t = getX(status);
			if (t.cmd != spacer)
				backinput(t);
			break;
		}
		else
		{
			if (isKeyword(status, "em"))
			{
				//auto v = cur_font().quad(); ??????
				t = getX(status);
				if (t.cmd != spacer)
					backinput(t);
			}
			else 
				if (isKeyword(status, "ex"))
				{
					//auto v = cur_font().x_height(); ??????
					t = getX(status);
					if (t.cmd != spacer)
						backinput(t);
				}
		}
		if (isKeyword(status, "true"))
		{
			preparemag();
			if (mag() != 1000)
			{
				val = xnoverd(val, 1000, mag());
				decimales = (1000*decimales+(remainder_<<16))/mag();
				val += decimales>>16;
				decimales %= 1<<16;
			}
		}
		if (isKeyword(status, "pt"))
		{
			calc(aritherror, val, decimales);
			t = getX(status);
			if (t.cmd != spacer)
				backinput(t);
			break;
		}
		int num, denom;
		auto set_conversion = [&num, &denom](int n, int d){ num = n; denom = d; };
		if (isKeyword(status, "in"))
			set_conversion(7227, 100); // 1 inch = 72.27 pt
		else 
			if (isKeyword(status, "pc"))
				set_conversion(12, 1); // 1 pica = 12 pt
			else 
				if (isKeyword(status, "cm"))
					set_conversion(7227, 254); // 1 inch = 2.54 cm
				else 
					if (isKeyword(status, "mm"))
						set_conversion(7227, 2540); // 1 cm = 10 mm
					else 
						if (isKeyword(status, "bp"))
							set_conversion(7227, 7200); // 1 inch = 72 bp
						else 
							if (isKeyword(status, "dd"))
								set_conversion(1238, 1157);
							else 
								if (isKeyword(status, "cc"))
									set_conversion(14856, 1157);
								else 
									if (isKeyword(status, "sp"))
									{
										t = getX(status);
										if (t.cmd != spacer)
											backinput(t);
										break;
									}
									else
									{
										error("Illegal unit of measure (pt inserted)", "Dimensions can be in units of em, ex, in, pt, pc,\ncm, mm, dd, cc, bp, or sp; but yours is a new one!\nI'll assume that you meant to say pt, for printer's points.\nDimension too large\nI can't work with sizes bigger than about 19 feet.\nContinue and I'll use the largest value I can.");
										calc(aritherror, val, decimales);
										t = xpand(status, t);
										if (t.cmd != spacer)
											backinput(t);
										break;
									}
		val = xnoverd(val, num, denom);
		decimales = (num*decimales+remainder_<<16)/denom;
		val += decimales>>16;
		decimales %= 1<<16;
		calc(aritherror, val, decimales);
		t = getX(status);
		if (t.cmd != spacer)
			backinput(t);
		break;
	} 
	if (aritherror || abs(val) >= 1<<30)
	{
		error("Dimension too large", "I can't work with sizes bigger than about 19 feet.\nContinue and I'll use the largest value I can.");
		val = max_dimen;
		aritherror = false;
	}
	if (negative)
		val *= -1;
	return val;
}

int Scanner::getUChar(char status)
{
	int val = getInt(status);
	if (val < 0 || val > 255)
	{
		interror(val, "Bad character code", "A character number must be between 0 and 255.\nI changed this one to zero.");
		return 0;
	}
	return val;
}

int Scanner::getUInt4(char status)
{
	int val = getInt(status);
	if (val < 0 || val >= 1<<4)
	{
		interror(val, "Bad number", "Since I expected to read a number between 0 and 15,\nI changed this one to zero.");
		return 0;
	}
	return val;
}

int Scanner::getUInt8(char status)
{
	int val = getInt(status);
	if (val < 0 || val >= 1<<8)
	{
		interror(val, "Bad register code", "A register number must be between 0 and 255.\nI changed this one to zero.");
		return 0;
	}
	return val;
}

int Scanner::getUInt15(char status)
{
	int val = getInt(status);
	if (val < 0 || val >= 1<<15)
	{
		interror(val, "Bad mathchar", "A mathchar number must be between 0 and 0x7F'FF.\nI changed this one to zero.");
		return 0;
	}
	return val;
}

[[nodiscard]] int Scanner::getUInt27(char status)
{
	int val = getInt(status);
	if (val < 0 || val >= 1<<27)
	{
		interror(val, "Bad delimiter code", "A numeric delimiter code must be between 0 and 2^{27}-1.\nI changed this one to zero.");
		return 0;
	}
	return val;
}


int Scanner::getFontIdent(char status)
{
	auto t = getXSkipSpace(status);
	switch (t.cmd)
	{
		case def_font:
			return curFontNum();
		case set_font:
			return t.chr;
		case def_family:
			return eqtb_local[t.chr+getUInt4(status)-local_base].int_;
	}
	backerror(t, "Missing font identifier", "I was looking for a control sequence whose\ncurrent meaning has been defined by \\font.");
	return null_font;
}

GlueSpec* Scanner::getGlue(char status, smallnumber level) //glue_val/mu_val
{
	bool mu = level == mu_val;
	bool negative = false;
	Token t;
	do
	{
		t = getXSkipSpace(status);
		if (t.tok == other_token+'-')
		{
			negative = !negative;
			t.tok = other_token+'+';
		}
	} while (t.tok != other_token+'+');
	if (between(min_internal, t.cmd, max_internal))
	{
		somethingInternal(status, level, negative, t);
		switch (lev)
		{
			case int_val:
				val = getDimen(status, mu, false, true);
				break;
			case dimen_val:
				if (level == mu_val)
					error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.");
				break;
			default:
				if (lev != level)
					error("Incompatible glue units", "I'm going to assume that 1mu=1pt when they're mixed.");
				return gl;
		}
	}
	else
	{
		backinput(t);
		val = getDimen(status, mu, false);
		if (negative)
			val *= -1;
	}
	auto q = new GlueSpec(zero_glue);
	q->width = val;
	if (isKeyword(status, "plus"))
	{
		q->stretch = getDimen(status, mu, true);
		q->stretch_order = curorder;
	}
	if (isKeyword(status, "minus"))
	{
		q->shrink = getDimen(status, mu, true);
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
int Scanner::getInt(char status)
{
	int val, lev;
	GlueSpec *gl;
	radix = 0;
	bool OKsofar = true; // has an error message been issued?
	bool negative = false; // should the answer be negated?
	Token t;
	do
	{
		t = getXSkipSpace(status);
		if (t.tok == other_token+'-')
		{
			negative = !negative;
			t.tok = other_token+'+';
		}
	} while (t.tok == other_token+'+');
	if (t.tok == alpha_token)
	{
		t = get(status);
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
			t = getX(status);
			if (t.cmd != spacer)
				backinput(t);
		}
	}
	else 
		if (t.cmd >= min_internal && t.cmd <= max_internal)
			somethingInternal(status, int_val, false, t);
		else
		{
			switch (t.tok)
			{
				case octal_token:
					radix = 8;
					t = getX(status);
					break;
				case hex_token:
					radix = 16;
					t = getX(status);
				default:
					radix = 10;
			}
			auto m = (1<<31)/radix;
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
				t = getX(status);
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

bool Scanner::isKeyword(char status, const std::string &s)
{
	TokenList backupHead;
	for (size_t k = 0; k < s.size();)
	{
		auto t = getX(status);
		if (t.cs == 0 && (t.chr == s[k] || t.chr == s[k]-'a'+'A'))
		{
			backupHead.list.push_back(t.tok);
			k++;
		}
		else 
			if (t.cmd != spacer || backupHead.list.size())
			{
				backinput(t);
				if (backupHead.list.size())
					backList(backupHead);
				return false;
			}
	}
	return true;
}

void Scanner::leftBrace(char status)
{
	auto t = getXSkipSpaceAndEscape(status);
	if (t.cmd != left_brace)
	{
		backerror(t, "Missing { inserted", "A left brace was mandatory here, so I've put one in.\nYou might want to delete and/or insert some corrections\nso that I will find a matching right brace soon.\n(If you're confused by all this, try typing `I}' now.)");
		alignstate++;
	}
}

void NoadContent::scan(char status)
{
	auto t = scanner.getXSkipSpaceAndEscape(status);
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
					t = scanner.xpand(status, t);
					backinput(t);
					t = scanner.getXSkipSpaceAndEscape(status);
					another = true;
					continue;
				}
				break;
			case char_num:
				t.chr = scanner.getUChar(status);
				t.cmd = char_given;
				another = true;
				continue;
			case math_char_num:
				c = scanner.getUInt15(status);
				break;
			case math_given: 
				c = t.chr;
				break;
			case delim_num:
				c = scanner.getUInt27(status)>>12;
				break;
			default:
				backinput(t);
				scanner.leftBrace(status);
				savestack.push_back(new MemoryNode(this));
				pushmath(math_group);
				return;
		}
	} while (another);
	math_type = math_char;
	character = c&0xFF;
	fam = getFam(c);
}

void Scanner::optionalEquals(char status)
{
	auto t = getXSkipSpace(status);
	if (t.tok != other_token+'=') // other_char + '='
		backinput(t);
}

constexpr int default_rule = 26214; //0.4\thinspace pt

RuleNode::RuleNode(char status, Token t)
{
	if (t.cmd == vrule)
		width = default_rule;
	else
	{
		height = default_rule;
		depth = 0;
	}
	while (true)
	{
		if (scanner.isKeyword(status, "width"))
		{
			width = scanner.getNormalDimen(status);
			continue;
		}
		if (scanner.isKeyword(status, "height"))
		{
			height = scanner.getNormalDimen(status);
			continue;
		}
		if (scanner.isKeyword(status, "depth"))
		{
			depth = scanner.getNormalDimen(status);
			continue;
		}
		break;
	}
}

Token Scanner::getBoxSpec(char status, groupcode c)
{
	if (isKeyword(status, "to"))
	{
		savestack.push_back(new MemoryNode(exactly));
		savestack.push_back(new MemoryNode(getNormalDimen(status)));
	}
	else
	{
		savestack.push_back(new MemoryNode(additional));
		savestack.push_back(new MemoryNode(isKeyword(status, "spread") ? getNormalDimen(status) : 0));
	}
	newsavelevel(c);
	leftBrace(status);
	return left_brace_token+'{';
}

Token Scanner::getBoxSpec(char status, groupcode c, int s)
{
	savestack.push_back(new MemoryNode(s));
	return getBoxSpec(status, c);
}

void TokenList::beginCommon(quarterword t) const
{
	push_input();
	state = token_list;
	Start.list = list;
	token_type = t;
}

void TokenList::beginBelowMacro(quarterword t) const
{
	beginCommon(t);
	Loc = 0;
}

void TokenList::beginMacro(void) const
{
	beginCommon(macro);
	Start.token_ref_count++; //the token list starts with a reference count
	param_start = paramstack.size();
}

void TokenList::beginAboveMacro(quarterword t) 
{
	beginCommon(t);
	token_ref_count++; //the token list starts with a reference count
	Loc = 0;
	if (tracing_macros() > 1)
		switch (t)
		{
			case mark_text: 
				diagnostic("\r"+esc("mark")+"->"+toString(10000000));
				break;
			case write_text: 
				diagnostic("\r"+esc("write")+"->"+toString(10000000));
				break;
			default:
				diagnostic("\r"+Token(assign_toks, t-output_text+output_routine_loc).cmdchr()+"->"+toString(10000000));
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
			Start.list.clear();
			break;
		case macro:
			Start.deleteTokenRef();
			for (;paramstack.size() > param_start; paramstack.pop_back())
				paramstack.back().list.clear();
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
			Start.deleteTokenRef();
	}
	pop_input();
}

Token Scanner::getX(char status)
{
	for (auto t = next(status); true; t = next(status))
		switch (t.cmd)
		{
			case call:
			case long_call:
			case outer_call:
			case long_outer_call:
				macrocall(t);
				break;
			case undefined_cs:
			case expand_after:
			case no_expand:
			case input:
			case if_test:
			case fi_or_else:
			case cs_name:
			case convert:
			case the:
			case top_bot_mark:
				expand(status, t);
				break;
			case end_template:
			case dont_expand:
			case glue_ref:
			case shape_ref:
			case box_ref:
			case data:
				return Token(frozen_endv+cs_token_flag);
			default:
				return t;
		}
}

Token Scanner::xpand(char status, Token t)
{
	for (; t.cmd > max_command; t = scanner.next(status))
		expand(status, t);
	return t;
}

halfword Scanner::getR(char status)
{
	while (true)
	{
		if (auto t = scanner.getSkipSpace(status); t.cs)
		{ 
			if (t.cs <= frozen_control_sequence)
				return t.cs;
			backinput(t);
		}
		inserror(frozen_protection+cs_token_flag, "Missing control sequence inserted", "Please don't say `\\def cs{...}', say `\\def\\cs{...}'.\nI've inserted an inaccessible control sequence so that your\ndefinition will be completed without mixing me up too badly.\nYou can recover graciously from this error, if you're\ncareful; see exercise 27.2 in The TeXbook.");
	}
}

TokenList thetoks(char status)
{
	auto t = scanner.getX(status);
	scanner.somethingInternal(status, tok_val, false, t);
	switch (scanner.lev)
	{
		case ident_val:
			return TokenList(cs_token_flag+scanner.val);
		case tok_val:
			return scanner.tk->list;
		case int_val: 
			return std::to_string(scanner.val);
		case dimen_val:
			return asScaled(scanner.val)+"pt";
		default: // glue_val / mu_val
			deleteglueref(scanner.gl);
			return scanner.gl->print(scanner.lev == glue_val ? "pt" : "mu");
	}
}

