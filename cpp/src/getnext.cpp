#include "getnext.h"
#include "impression.h"
#include "erreur.h"
#include "fichier.h"
#include "lecture.h"
#include "chaine.h"
#include "noeud.h"
#include "police.h"
#include "equivalent.h" 
#include "alignement.h"
#include "macrocall.h"
#include "conditional.h"
#include "etat.h"
#include "initprim.h"
#include "tampon.h"
#include <iostream>

static Token checkoutervalidity(char status, Token t)
{
	if (status == normal)
		return t;
	if (t.cs && (state == token_list || !isFile()))
		backList(cs_token_flag+t.cs);
	switch (status)
	{
		case skipping:
			inserror(t, "Incomplete "+Token(if_test, curif).cmdchr()+"; all text was ignored after line "+std::to_string(skipline), std::string(cs ? "A forbidden control sequence occurred in skipped text." : "The file ended while I was skipping conditional text.")+"This kind of error happens when you say `\\if...' and forget\nthe matching `\\fi'. I've inserted a `\\fi'; this might work.", false);
			return frozen_fi+cs_token_flag;
		case defining:
			print("\rRunaway definition?\n"+defRef.toString(errorline-10));
			error(t.cs ? "Forbidden control sequence found" : "File ended while scanning definition of "+scs(warningindex), "I suspect you have forgotten a `}', causing me\nto read past where you wanted me to stop.\nI'll try to recover; but if the error is serious,\nyou'd better type `E' or `X' now and fix your file.", false);
			insList(right_brace_token+'}');
			break;
		case matching:
			print("\rRunaway argument?\n"+tempHead.toString(errorline-10));
			error(t.cs ? "Forbidden control sequence found" : "File ended while scanning use of "+scs(warningindex), "I suspect you have forgotten a `}', causing me\nto read past where you wanted me to stop.\nI'll try to recover; but if the error is serious,\nyou'd better type `E' or `X' now and fix your file.", false);
			longstate = outer_call;
			insList(partoken);
			break;
		case aligning:
			print("\rRunaway preamble?\n"+holdHead.toString(errorline-10));
			error(t.cs ? "Forbidden control sequence found" : "File ended while scanning preamble of "+scs(warningindex), "I suspect you have forgotten a `}', causing me\nto read past where you wanted me to stop.\nI'll try to recover; but if the error is serious,\nyou'd better type `E' or `X' now and fix your file.", false);
			insList(std::vector<halfword>{frozen_cr+cs_token_flag, right_brace_token+'}'});
			alignstate = -1000000;
			break;
		case absorbing:
			print("\rRunaway text?\n"+defRef.toString(errorline-10));
			error(t.cs ? "Forbidden control sequence found" : "File ended while scanning text of "+scs(warningindex), "I suspect you have forgotten a `}', causing me\nto read past where you wanted me to stop.\nI'll try to recover; but if the error is serious,\nyou'd better type `E' or `X' now and fix your file.", false);
			insList(right_brace_token+'}');
	}
	return t.cs ? Token(spacer, ' ') : t;
}

static bool is_hex(ASCIIcode c) { return between('0', c, '9') || between('a', c, 'f'); }
static int toHex(ASCIIcode c) { return c <= '9' ? c -'0' : c-'a'+10; }

static int intFromTwoHexDigit(ASCIIcode c, int pos)
{
	if (is_hex(c) && pos <= curinput.limit)
	{
		auto &cc = getBuf(pos);
		if (is_hex(cc))
			return (toHex(c)<<4)+toHex(cc);
	}
	return -1;
}

static bool prochainCaractereOK(int pos, halfword chr) { return getBuf(pos) == chr && pos < curinput.limit && getBuf(pos+1) < 128; }

template<class T> static int processBuffer(int k, T &var)
{
	auto &c = getBuf(k+1);
	auto t = intFromTwoHexDigit(c, k+2);
	var = t >= 0 ? t : c < 64 ? c + 64 : c - 64;
	return t >= 0 ? 3 : 2;
}

static void removeFromEnd(int &k, int d)
{
	curinput.limit -= d;
	First -= d;
	shiftBuf(k+d, curinput.limit+1+d, k);
	k = curinput.limit+1;
}

static bool testDoubleSup(int k, Token &tk)
{
	if (k >= curinput.limit)
		return false;
	if (getBuf(k) == tk.chr /* ^^ */ && getBuf(k+1) < 128)
	{
		auto &c = getBuf(k+1);
		auto t = intFromTwoHexDigit(c, k+2);
		tk.chr = getBuf(k-1) = t >= 0 ? t : c < 64 ? c + 64 : c - 64;
		if (t >= 0) // ^^xx avec xx hexadécimal
			removeFromEnd(k, 3);
		else // ^^c avec c caractère
			removeFromEnd(k, 2);
		return true;
	}
	return false;
}


static TokenList omit_template(end_template_token); //!< a constant token list

#define ANY_STATE_PLUS(cmd) mid_line+cmd: case skip_blanks+cmd: case new_line+cmd
#define ADD_DELIMS_TO(state) state+math_shift: case state+tab_mark: case state+mac_param: case state+sub_mark: case state+letter: case state+other_char 

Token Scanner::next(char status, bool nonewcontrolsequence)
{
	while (true)
	{
		bool restart = false;
		Token t;
		if (state != token_list)
		{
			bool skip;
			do
			{
				skip = false;
				if (!isBufFull())
				{
					t.chr = currentBuf();
					bufNext();
					bool doubleSup2;
					do
					{
						doubleSup2 = false;
						t.cmd = cat_code(t.chr);
						switch (state+t.cmd)
						{
							case ANY_STATE_PLUS(ignore):
							case skip_blanks+spacer:
							case new_line+spacer:
								skip = true;
								break;
							case ANY_STATE_PLUS(escape):
								if (isBufFull())
									t = equivToken(null_cs-active_base, eqtb_active);
								else
								{   // loc <= limit
									bool identifiant = false;
									for (bool doubleSup = true; doubleSup && !identifiant;)
									{
										doubleSup = false;
										switch (int cat = cat_code(t.chr = currentBuf()); cat)
										{
											case letter:
												if (atLeastTwoInBuf())
												{
													int k;
													for (k = curinput.loc+1; cat == letter && k <= curinput.limit; k++)
														cat = cat_code(t.chr = getBuf(k));
													if (cat == sup_mark && testDoubleSup(k, t)) // "^^" 
														doubleSup = true;
													else
													{
														if (cat != letter)
															k--;
														if (k-curinput.loc >= 1)
														{
															t = equivToken(idlookup(readBufUpTo(k), nonewcontrolsequence)-hash_base, eqtb_cs);
															curinput.loc = k;
															identifiant = true;
														}
													}
												} [[fallthrough]];
											case spacer:
												state = skip_blanks;
												break;
											case sup_mark:
												if (testDoubleSup(curinput.loc+1, t))
													doubleSup = true; [[fallthrough]];
											default:
												state = mid_line;
										}
									}
									if (!identifiant)
									{
										t = equivToken(currentBuf()+single_base-active_base, eqtb_active);
										bufNext();
									}
								}
								if (t.cmd >= outer_call)
									t = checkoutervalidity(status, t);
								break;
							case ANY_STATE_PLUS(active_char):
								t = equivToken(t.chr, eqtb_active);
								state = mid_line;
								if (t.cmd >= outer_call)
									t = checkoutervalidity(status, t);
								break;
							case ANY_STATE_PLUS(sup_mark):
								if (prochainCaractereOK(curinput.loc, t.chr)) 
								{
									curinput.loc += processBuffer(curinput.loc, t.chr);
									doubleSup2 = true;
								}
								else
									state = mid_line;
								break;
							case ANY_STATE_PLUS(invalid_char):
								error("Text line contains an invalid character", "A funny symbol that I can't read has just been input.\nContinue, and I'll forget that it ever happened.", false);
								restart = true;
								break;
							case mid_line+spacer:
								state = skip_blanks;
								t.chr = ' ';
								break;
							case mid_line+car_ret:
								bufEnd();
								t.cmd = spacer;
								t.chr = ' ';
								break;
							case skip_blanks+car_ret:
							case ANY_STATE_PLUS(comment):
								bufEnd();
								skip = true;
								break;
							case new_line+car_ret:
								bufEnd();
								t = equivToken(parloc, eqtb);
								if (t.cmd >= outer_call)
									t = checkoutervalidity(status, t);
								break;
							case skip_blanks+left_brace:
							case new_line+left_brace:
								state = mid_line;
							case mid_line+left_brace:
								alignstate++;
								break;
							case skip_blanks+right_brace:
							case new_line+right_brace:
								state = mid_line;
							case mid_line+right_brace:
								alignstate--;
								break;
							case ADD_DELIMS_TO(skip_blanks):
							case ADD_DELIMS_TO(new_line):
								state = mid_line;
						}
					} while (doubleSup2 && !skip && !restart);
				}
				else // loc > limit
				{
					state = new_line;
					if (isFile())
					{
						if (!terminal_input(name))
							return Token(0, 0);
						if (inputstack.size() > 1)
						{
							First = curinput.start;
							endfilereading();
							restart = true;
						}
						if (!restart)
						{
							if (selector < log_only)
								openlogfile(First);
							if (interaction > nonstop_mode)
							{
								if (end_line_char_inactive())
									curinput.limit++;
								if (sizeBuf() == 1)
									print("\r(Please type a command or say `\\end')");
								println();
								print("*");
								curinput.limit = terminput(curinput.start);
								removeLastBuf();
								First = curinput.limit+1;
								bufBegin();
							}
							else
								fatalerror("*** (job aborted, no legal \end found)");
						}
					}
					else
					{
						line++;
						First = curinput.start;
						if (int lst = inputln(cur_file(), true, curinput.start); !forceeof && lst >= 0)
						{
							curinput.limit = lst;
							if (pausing() > 0 && interaction > nonstop_mode)
							{
								lst = firmuptheline();
								First = curinput.limit;
							}
							if (!restart)
							{
								removeLastBuf();
								First = curinput.limit+1;
								bufBegin();
							}
						}
						else
						{
							print(")");
							openparens--;
							std::cout << std::flush;
							forceeof = false;
							First = curinput.start;
							endfilereading();
							t = checkoutervalidity(status, t);
							restart = true;
						}
					}
					if (!restart)
						skip = true;
				}
			} while (skip && !restart);
		}
		else
			if (!Loc)
			{
				endtokenlist();
				restart = true;
			}
			else
			{
				Loc++;
				if (Start.list[Loc] >= cs_token_flag)
				{
					t = equivToken(Start.list[Loc]-cs_token_flag, eqtb);
					switch (t.cmd)
					{
						case outer_call:
						case long_outer_call:
						case end_template:
						case glue_ref:
						case shape_ref:
						case box_ref:
						case data:
							t = checkoutervalidity(status, t);
							break;
						case dont_expand:
						{
							t = equivToken(Start.list[Loc]-cs_token_flag, eqtb);
							Loc = 0;
							if (t.cmd > max_command)
								t = Token(relax, no_expand_flag);
						}
					}
				}
				else
					switch (t = Token(Start.list[Loc]>>8, Start.list[Loc]%(1<<8)); t.cmd)
					{
						case left_brace: 
							alignstate++;
							break;
						case right_brace: 
							alignstate--;
							break;
						case out_param:
							paramstack[curinput.limit+t.chr-1].beginBelowMacro(parameter);
							restart = true;
					}
			}
		if (!restart)
		{ 
			if (between(tab_mark, t.cmd, out_param) && alignstate == 0)
			{
				if (status == aligning || curalign == nullptr)
					fatalerror("(interwoven alignment preambles are not allowed)");
				t.cmd = curalign->extra_info;
				curalign->extra_info = t.chr;
				t.cmd == omit ? omit_template.beginBelowMacro(v_template) : curalign->vPart.beginBelowMacro(v_template);
				alignstate = 1000000;
				restart = true;
			}
			return t;
		}
	}
}
