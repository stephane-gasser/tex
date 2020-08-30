#include "getnext.h"
#include "impression.h"
#include "erreur.h"
#include "terminput.h"
#include "endfilereading.h"
#include "openlogfile.h"
#include "inputln.h"
#include <iostream>
#include "firmuptheline.h"
#include "lecture.h"
#include "idlookup.h"
#include "texte.h"
#include "noeud.h"
#include "runaway.h"
#include "police.h"
#include "equivalent.h" 

[[nodiscard]] static Token checkoutervalidity(Token t)
{
	if (scannerstatus == normal)
		return t;
	if (t.cs)
	{
		if (state == token_list || txt(name) < 1 || txt(name) > 17)
			back_list(new TokenNode(cs_token_flag+t.cs));
		t.cmd = spacer;
		t.chr = ' ';
	}
	if (scannerstatus == skipping)
	{
		Token tk;
		tk.cmd = if_test;
		tk.chr = curif;
		inserror(t, "Incomplete "+cmdchr(tk)+"; all text was ignored after line "+std::to_string(skipline), std::string(cs ? "A forbidden control sequence occurred in skipped text." : "The file ended while I was skipping conditional text.")+"This kind of error happens when you say `\\if...' and forget\nthe matching `\\fi'. I've inserted a `\\fi'; this might work.", false);
		t.tok = frozen_fi+cs_token_flag;
	}
	else
	{
		runaway();
		switch (scannerstatus)
		{
			case defining:
				error(t.cs ? "Forbidden control sequence found" : "File ended while scanning definition of "+scs(warningindex), "I suspect you have forgotten a `}', causing me\nto read past where you wanted me to stop.\nI'll try to recover; but if the error is serious,\nyou'd better type `E' or `X' now and fix your file.", false);
				ins_list(new TokenNode(right_brace_token+'}'));
				break;
			case matching:
				error(t.cs ? "Forbidden control sequence found" : "File ended while scanning use of "+scs(warningindex), "I suspect you have forgotten a `}', causing me\nto read past where you wanted me to stop.\nI'll try to recover; but if the error is serious,\nyou'd better type `E' or `X' now and fix your file.", false);
				ins_list(new TokenNode(partoken));
				longstate = outer_call;
				break;
			case aligning:
			{
				error(t.cs ? "Forbidden control sequence found" : "File ended while scanning preamble of "+scs(warningindex), "I suspect you have forgotten a `}', causing me\nto read past where you wanted me to stop.\nI'll try to recover; but if the error is serious,\nyou'd better type `E' or `X' now and fix your file.", false);
				auto p = new TokenNode(frozen_cr+cs_token_flag);
				p->link = new TokenNode(right_brace_token+'}');
				ins_list(p);
				alignstate = -1000000;
				break;
			}
			case absorbing:
				error(t.cs ? "Forbidden control sequence found" : "File ended while scanning text of "+scs(warningindex), "I suspect you have forgotten a `}', causing me\nto read past where you wanted me to stop.\nI'll try to recover; but if the error is serious,\nyou'd better type `E' or `X' now and fix your file.", false);
				ins_list(new TokenNode(right_brace_token+'}'));
		}
	}
	t.cs = 0;
	return t;
}

static bool is_hex(ASCIIcode c)
{
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
}

static int toHex(ASCIIcode c)
{
	return c <= '9' ? c -'0' : c-'a'+10;
}

static int intFromTwoHexDigit(ASCIIcode c, int pos)
{
	if (is_hex(c) && pos <= limit)
	{
		auto &cc = buffer[pos];
		if (is_hex(cc))
			return 16*toHex(c)+toHex(cc);
	}
	return -1;
}

static bool prochainCaractereOK(int pos, halfword chr)
{
	return buffer[pos] == chr && pos < limit && buffer[pos+1] < 128;
}

template<class T> static int processBuffer(int k, T &var)
{
	auto &c = buffer[k+1];
	auto t = intFromTwoHexDigit(c, k+2);
	var = t >= 0 ? t : c < 64 ? c + 64 : c - 64;
	return t >= 0 ? 3 : 2;
}

static void removeFromEnd(int &k, int d)
{
	limit -= d;
	First -= d;
	for (;k <= limit; k++)
		buffer[k] = buffer[k+d];
}

#define ANY_STATE_PLUS(cmd) mid_line+cmd: case skip_blanks+cmd: case new_line+cmd
#define ADD_DELIMS_TO(state) state+math_shift: case state+tab_mark: case state+mac_param: case state+sub_mark: case state+letter: case state+other_char 

[[nodiscard]] Token getnext(void)
{
	Token t;
	bool restart;
	do 
	{
		restart = false;
		t.cs = 0;
		if (state != token_list)
		{
			bool skip;
			do
			{
				skip = false;
				if (loc <= limit)
				{
					t.chr = buffer[loc];
					loc++;
					bool superscript2;
					do
					{
						superscript2 = false;
						t.cmd = cat_code(t.chr);
						switch (state+t.cmd)
						{
							case ANY_STATE_PLUS(ignore):
							case skip_blanks+spacer:
							case new_line+spacer:
								skip = true;
								break;
							case ANY_STATE_PLUS(escape):
								if (loc > limit)
								{
									t.cs = null_cs;
									t.cmd = eqtb_active[null_cs-active_base].type;
									t.chr = eqtb_active[null_cs-active_base].int_;
								}
								else
								{
									bool superscript, identifiant;
									do
									{
										superscript = false;
										identifiant = false;
										t.chr = buffer[loc];
										int cat = cat_code(t.chr);
										int k = loc+1;
										state = (cat == letter || cat == spacer) ? skip_blanks : mid_line;
										if (cat == letter && k <= limit)
										{
											do
											{
												t.chr = buffer[k];
												cat = cat_code(t.chr);
												k++;
											} while (cat == letter && k <= limit);
											if (cat == sup_mark && prochainCaractereOK(k, t.chr))
											{
												if (processBuffer(k, buffer[k-1]) == 3)
												{
													t.chr = buffer[k-1];
													removeFromEnd(k, 3);
												}
												else
													removeFromEnd(k, 2);
												superscript = true;
											}
											else
											{
												if (cat != letter)
													k--;
												if (k > loc+1)
												{
													std::string s;
													for (int i = loc; i <= k; i++)
														s += buffer[i];
													t.cs = idlookup(s);
													t.cmd = eqtb_cs[t.cs-hash_base].type;
													t.chr = eqtb_cs[t.cs-hash_base].int_;
													loc = k;
													identifiant = true;
												}
											}
										}
										else
											if (cat == sup_mark && prochainCaractereOK(k, t.chr))
											{
												if (processBuffer(k, buffer[k-1]) == 3)
												{
													t.chr = buffer[k-1];
													removeFromEnd(k, 3);
												}
												else
													removeFromEnd(k, 2);
												superscript = true;
											}
									} while (superscript && !identifiant);
									if (!identifiant)
									{
										t.cs = single_base+buffer[loc];
										t.cmd = eqtb_active[t.cs-active_base].type;
										t.chr = eqtb_active[t.cs-active_base].int_;
										loc++;
									}
								}
								if (t.cmd >= outer_call)
									t = checkoutervalidity(t);
								break;
							case ANY_STATE_PLUS(active_char):
								t.cs = t.chr+active_base;
								t.cmd = eqtb_active[t.cs-active_base].type;
								t.chr = eqtb_active[t.cs-active_base].int_;
								state = mid_line;
								if (t.cmd >= outer_call)
									t = checkoutervalidity(t);
								break;
							case ANY_STATE_PLUS(sup_mark):
								if (prochainCaractereOK(loc, t.chr))
								{
									loc += processBuffer(loc, t.chr);
									superscript2 = true;
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
								loc = limit+1;
								t.cmd = spacer;
								t.chr = ' ';
								break;
							case skip_blanks+car_ret:
							case ANY_STATE_PLUS(comment):
								loc = limit+1;
								skip = true;
								break;
							case new_line+car_ret:
								loc = limit+1;
								t.cs = parloc;
								t.cmd = eqtb[t.cs].type;
								t.chr = eqtb[t.cs].int_;
								if (t.cmd >= outer_call)
									t = checkoutervalidity(t);
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
					} while (superscript2 && !skip && !restart);
				}
				else
				{
					state = new_line;
					if (txt(name) > 17)
					{
						line++;
						First = start;
						if (!forceeof)
							if (inputln(cur_file(), true))
								firmuptheline();
							else
								forceeof = true;
						if (forceeof)
						{
							print(")");
							openparens--;
							std::cout << std::flush;
							forceeof = false;
							endfilereading();
							t = checkoutervalidity(t);
							restart = true;
						}
						if (!restart)
						{
							if (end_line_char_inactive())
								limit--;
							else
								buffer[limit] = end_line_char();
							First = limit+1;
							loc = start;
						}
					}
					else
					{
						if (!terminal_input(name))
						{
							t.cmd = 0;
							t.chr = 0;
							return t;
						}
						if (inputptr > 0)
						{
							endfilereading();
							restart = true;
						}
						if (!restart)
						{
							if (selector < log_only)
								openlogfile();
							if (interaction > nonstop_mode)
							{
								if (end_line_char_inactive())
									limit++;
								if (limit == start)
									printnl("(Please type a command or say `\\end')");
								println();
								First = start;
								print("*");
								terminput();
								limit = last;
								if (end_line_char_inactive())
									limit--;
								else
									buffer[limit] = end_line_char();
								First = limit+1;
								loc = start;
							}
							else
								fatalerror("*** (job aborted, no legal \end found)");
						}
					}
					if (!restart)
						skip = true;
				}
			} while (skip && !restart);
		}
		else
			if (Loc)
			{
				int tt = Loc->token;
				Loc = dynamic_cast<TokenNode*>(Loc->link);
				if (tt >= cs_token_flag)
				{
					t.cs = tt-cs_token_flag;
					t.cmd = eqtb[t.cs].type;
					t.chr = eqtb[t.cs].int_;
					if (t.cmd >= outer_call)
						if (t.cmd == dont_expand)
						{
							t.cs = Loc->token-cs_token_flag;
							Loc = nullptr;
							t.cmd = eqtb[t.cs].type;
							t.chr = eqtb[t.cs].int_;
							if (t.cmd > max_command)
							{
								t.cmd = relax;
								t.chr = no_expand_flag;
							}
						}
						else
							t = checkoutervalidity(t);
				}
				else
				{
					t.cmd = tt>>8;
					t.chr = tt%(1<<8);
					switch (t.cmd)
					{
						case left_brace: 
							alignstate++;
							break;
						case right_brace: 
							alignstate--;
							break;
						case out_param:
							begintokenlist(paramstack[limit+t.chr-1], 0);
							restart = true;
					}
				}
			}
			else
			{
				endtokenlist();
				restart = true;
			}
		if (!restart && t.cmd <= out_param && t.cmd >= tab_mark && alignstate == 0)
		{
			if (scannerstatus == aligning || curalign == 0)
				fatalerror("(interwoven alignment preambles are not allowed)");
			t.cmd = extra_info(curalign);
			extra_info(curalign) = t.chr;
			TokenNode *T;
			T->num = t.cmd == omit ? omit_template->num : v_part(curalign);
			begintokenlist(T, v_template);
			alignstate = 1000000;
			restart = true;
		}
	} while (restart);
	return t;
}
