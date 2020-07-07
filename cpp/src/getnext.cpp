#include "getnext.h"
#include "checkoutervalidity.h"
#include "impression.h"
#include "erreur.h"
#include "terminput.h"
#include "endfilereading.h"
#include "openlogfile.h"
#include "inputln.h"
#include <iostream>
#include "firmuptheline.h"
#include "pauseforinstructions.h"
#include "lecture.h"
#include "idlookup.h"
#include "texte.h"

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
		ASCIIcode cc = buffer[pos];
		if (is_hex(cc))
			return 16*toHex(c)+toHex(cc);
	}
	return -1;
}

static bool prochainCaractereOK(int pos)
{
	return buffer[pos] == curchr && pos < limit && buffer[pos+1] < 128;
}

template<class T> static int processBuffer(int k, T &var)
{
	ASCIIcode c = buffer[k+1];
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

void getnext(void)
{
	bool restart;
	do 
	{
		restart = false;
		curcs = 0;
		if (state != token_list)
		{
			bool skip;
			do
			{
				skip = false;
				if (loc <= limit)
				{
					curchr = buffer[loc];
					loc++;
					bool superscript2;
					do
					{
						superscript2 = false;
						curcmd = cat_code(curchr);
						switch (state+curcmd)
						{
							case ANY_STATE_PLUS(ignore):
							case skip_blanks+spacer:
							case new_line+spacer:
								skip = true;
								break;
							case ANY_STATE_PLUS(escape):
								if (loc > limit)
									curcs = null_cs;
								else
								{
									bool superscript, identifiant;
									do
									{
										superscript = false;
										identifiant = false;
										curchr = buffer[loc];
										int cat = cat_code(curchr);
										int k = loc+1;
										state = (cat == letter || cat == spacer) ? skip_blanks : mid_line;
										if (cat == letter && k <= limit)
										{
											do
											{
												curchr = buffer[k];
												cat = cat_code(curchr);
												k++;
											} while (cat == letter && k <= limit);
											if (cat == sup_mark && prochainCaractereOK(k))
											{
												if (processBuffer(k, buffer[k-1]) == 3)
												{
													curchr = buffer[k-1];
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
													curcs = idlookup(s);
													loc = k;
													identifiant = true;
												}
											}
										}
										else
											if (cat == sup_mark && prochainCaractereOK(k))
											{
												if (processBuffer(k, buffer[k-1]) == 3)
												{
													curchr = buffer[k-1];
													removeFromEnd(k, 3);
												}
												else
													removeFromEnd(k, 2);
												superscript = true;
											}
									} while (superscript && !identifiant);
									if (!identifiant)
									{
										curcs = single_base+buffer[loc];
										loc++;
									}
								}
								curcmd = eq_type(curcs);
								curchr = equiv(curcs);
								if (curcmd >= outer_call)
									checkoutervalidity();
								break;
							case ANY_STATE_PLUS(active_char):
								curcs = curchr+1;
								curcmd = eq_type(curcs);
								curchr = equiv(curcs);
								state = mid_line;
								if (curcmd >= outer_call)
									checkoutervalidity();
								break;
							case ANY_STATE_PLUS(sup_mark):
								if (prochainCaractereOK(loc))
								{
									loc += processBuffer(loc, curchr);
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
								curchr = ' ';
								break;
							case mid_line+car_ret:
								loc = limit+1;
								curcmd = spacer;
								curchr = ' ';
								break;
							case skip_blanks+car_ret:
							case ANY_STATE_PLUS(comment):
								loc = limit+1;
								skip = true;
								break;
							case new_line+car_ret:
								loc = limit+1;
								curcs = parloc;
								curcmd = eq_type(curcs);
								curchr = equiv(curcs);
								if (curcmd >= outer_call)
									checkoutervalidity();
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
							checkoutervalidity();
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
							curcmd = curchr = 0;
							return;
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
					{
						check_interrupt();
						skip = true;
					}
				}
			} while (skip && !restart);
		}
		else
			if (loc)
			{
				int t = info(loc);
				loc = link(loc);
				if (t >= cs_token_flag)
				{
					curcs = t-cs_token_flag;
					curcmd = eq_type(curcs);
					curchr = equiv(curcs);
					if (curcmd >= outer_call)
						if (curcmd == dont_expand)
						{
							curcs = info(loc)-cs_token_flag;
							loc = 0;
							curcmd = eq_type(curcs);
							curchr = equiv(curcs);
							if (curcmd > max_command)
							{
								curcmd = relax;
								curchr = no_expand_flag;
							}
						}
						else
							checkoutervalidity();
				}
				else
				{
					curcmd = t/0x1'00;
					curchr = t%0x1'00;
					switch (curcmd)
					{
						case left_brace: 
							alignstate++;
							break;
						case right_brace: 
							alignstate--;
							break;
						case out_param:
							begintokenlist(paramstack[limit+curchr-1], 0);
							restart = true;
					}
				}
			}
			else
			{
				endtokenlist();
				restart = true;
			}
		if (!restart && curcmd <= out_param && curcmd >= tab_mark && alignstate == 0)
		{
			if (scannerstatus == 4 || curalign == 0)
				fatalerror("(interwoven alignment preambles are not allowed)");
			curcmd = extra_info(curalign);
			extra_info(curalign) = curchr;
			if (curcmd == omit)
				begintokenlist(omit_template, v_template);
			else
				begintokenlist(v_part(curalign), v_template);
			alignstate = 1000000;
			restart = true;
		}
	} while (restart);
}
