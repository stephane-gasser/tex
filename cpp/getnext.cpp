#include "getnext.h"
#include "checkoutervalidity.h"
#include "printnl.h"
#include "println.h"
#include "print.h"
#include "error.h"
#include "terminput.h"
#include "fatalerror.h"
#include "endfilereading.h"
#include "openlogfile.h"
#include "printchar.h"
#include "inputln.h"
#include <iostream>
#include "firmuptheline.h"
#include "pauseforinstructions.h"
#include "begintokenlist.h"
#include "endtokenlist.h"
#include "idlookup.h"
#include "globals.h"
#include "texte.h"

bool isHexDigit(ASCIIcode c)
{
	return (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f');
}

int toHex(ASCIIcode c)
{
	return c <= '9' ? c -'0' : c-'a'+10;
}

int intFromTwoHexDigit(ASCIIcode c, int pos)
{
	if (isHexDigit(c) && pos <= curinput.limitfield)
	{
		ASCIIcode cc = buffer[pos];
		if (isHexDigit(cc))
			return 16*toHex(c)+toHex(cc);
	}
	return -1;
}

bool prochainCaractereOK(int pos)
{
	return buffer[pos] == curchr && pos < curinput.limitfield && buffer[pos+1] < 128;
}

template<class T> int processBuffer(int k, T &var)
{
	ASCIIcode c = buffer[k+1];
	auto t = intFromTwoHexDigit(c, k+2);
	var = t >= 0 ? t : c < 64 ? c + 64 : c - 64;
	return t >= 0 ? 3 : 2;
}

void removeFromEnd(int &k, int d)
{
	curinput.limitfield -= d;
	First -= d;
	for (;k <= curinput.limitfield; k++)
		buffer[k] = buffer[k+d];
}

void getnext(void)
{
	bool recommence;
	do 
	{
		recommence = false;
		curcs = 0;
		if (curinput.statefield)
		{
			bool skip;
			do
			{
				skip = false;
				if (curinput.locfield <= curinput.limitfield)
				{
					curchr = buffer[curinput.locfield];
					curinput.locfield++;
					bool superscript2;
					do
					{
						superscript2 = false;
						curcmd = cat_code(curchr);
						switch (curinput.statefield+curcmd)
						{
							case mid_line+ignore:
							case skip_blanks+ignore:
							case new_line+ignore:
							case skip_blanks+spacer:
							case new_line+spacer:
								skip = true;
								break;
							case mid_line+escape:
							case skip_blanks+escape:
							case new_line+escape:
								if (curinput.locfield > curinput.limitfield)
									curcs = 513;
								else
								{
									bool superscript, identifiant;
									do
									{
										superscript = false;
										identifiant = false;
										curchr = buffer[curinput.locfield];
										int cat = cat_code(curchr);
										int k = curinput.locfield+1;
										curinput.statefield = (cat == letter || cat == spacer) ? skip_blanks : mid_line;
										if (cat == letter && k <= curinput.limitfield)
										{
											do
											{
												curchr = buffer[k];
												cat = cat_code(curchr);
												k++;
											} while (cat == letter && k <= curinput.limitfield);
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
												if (k > curinput.locfield+1)
												{
													curcs = idlookup(curinput.locfield, k-curinput.locfield);
													curinput.locfield = k;
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
										curcs = 257+buffer[curinput.locfield];
										curinput.locfield++;
									}
								}
								curcmd = eq_type(curcs);
								curchr = equiv(curcs);
								if (curcmd >= outer_call)
									checkoutervalidity();
								break;
							case mid_line+active_char:
							case skip_blanks+active_char:
							case new_line+active_char:
								curcs = curchr+1;
								curcmd = eq_type(curcs);
								curchr = equiv(curcs);
								curinput.statefield = mid_line;
								if (curcmd >= outer_call)
									checkoutervalidity();
								break;
							case mid_line+sup_mark:
							case skip_blanks+sup_mark:
							case new_line+sup_mark:
								if (prochainCaractereOK(curinput.locfield))
								{
									curinput.locfield += processBuffer(curinput.locfield, curchr);
									superscript2 = true;
								}
								else
									curinput.statefield = mid_line;
								break;
							case mid_line+invalid_char:
							case skip_blanks+invalid_char:
							case new_line+invalid_char:
								printnl("! ");
								print("Text line contains an invalid character");
								helpptr = 2;
								helpline[1] = txt("A funny symbol that I can't read has just been input.");
								helpline[0] = txt("Continue, and I'll forget that it ever happened.");
								deletionsallowed = false;
								error();
								deletionsallowed = true;
								recommence = true;
								break;
							case mid_line+spacer:
								curinput.statefield = skip_blanks;
								curchr = ' ';
								break;
							case mid_line+car_ret:
								curinput.locfield = curinput.limitfield+1;
								curcmd = spacer;
								curchr = ' ';
								break;
							case skip_blanks+car_ret:
							case mid_line+comment:
							case skip_blanks+comment:
							case new_line+comment:
								curinput.locfield = curinput.limitfield+1;
								skip = true;
								break;
							case new_line+car_ret:
								curinput.locfield = curinput.limitfield+1;
								curcs = parloc;
								curcmd = eq_type(curcs);
								curchr = equiv(curcs);
								if (curcmd >= outer_call)
									checkoutervalidity();
								break;
							case skip_blanks+left_brace:
							case new_line+left_brace:
								curinput.statefield = mid_line;
							case mid_line+left_brace:
								alignstate++;
								break;
							case skip_blanks+right_brace:
							case new_line+right_brace:
								curinput.statefield = mid_line;
							case mid_line+right_brace:
								alignstate--;
								break;
							case skip_blanks+math_shift:
							case skip_blanks+tab_mark:
							case skip_blanks+mac_param:
							case skip_blanks+sub_mark:
							case skip_blanks+letter:
							case skip_blanks+other_char:
							case new_line+math_shift:
							case new_line+tab_mark:
							case new_line+mac_param:
							case new_line+sub_mark:
							case new_line+letter:
							case new_line+other_char:
								curinput.statefield = mid_line;
						}
					} while (superscript2 && !skip && !recommence);
				}
				else
				{
					curinput.statefield = new_line;
					if (curinput.namefield > 17)
					{
						line++;
						First = curinput.startfield;
						if (!forceeof)
							if (inputln(inputfile[curinput.indexfield], true))
								firmuptheline();
							else
								forceeof = true;
						if (forceeof)
						{
							printchar(')');
							openparens--;
							std::cout << std::flush;
							forceeof = false;
							endfilereading();
							checkoutervalidity();
							recommence = true;
						}
						if (!recommence)
						{
							if (int_par(end_line_char_code) < 0 || int_par(end_line_char_code) > 255)
								curinput.limitfield--;
							else
								buffer[curinput.limitfield] = int_par(end_line_char_code);
							First = curinput.limitfield+1;
							curinput.locfield = curinput.startfield;
						}
					}
					else
					{
						if (curinput.namefield)
						{
							curcmd = curchr = 0;
							return;
						}
						if (inputptr > 0)
						{
							endfilereading();
							recommence = true;
						}
						if (!recommence)
						{
							if (selector < log_only)
								openlogfile();
							if (interaction > nonstop_mode)
							{
								if (int_par(end_line_char_code) < 0 || int_par(end_line_char_code) > 255)
									curinput.limitfield++;
								if (curinput.limitfield == curinput.startfield)
									printnl("(Please type a command or say `\\end')");
								println();
								First = curinput.startfield;
								printchar('*');
								terminput();
								curinput.limitfield = last;
								if (int_par(end_line_char_code) < 0 || int_par(end_line_char_code) > 255)
									curinput.limitfield--;
								else
									buffer[curinput.limitfield] = int_par(end_line_char_code);
								First = curinput.limitfield+1;
								curinput.locfield = curinput.startfield;
							}
							else
								fatalerror("*** (job aborted, no legal \end found)");
						}
					}
					if (!recommence)
					{
						if (interrupt)
							pauseforinstructions();
						skip = true;
					}
				}
			} while (skip && !recommence);
		}
		else
			if (curinput.locfield)
			{
				int t = info(curinput.locfield);
				curinput.locfield = link(curinput.locfield);
				if (t >= cs_token_flag)
				{
					curcs = t-cs_token_flag;
					curcmd = eq_type(curcs);
					curchr = equiv(curcs);
					if (curcmd >= outer_call)
						if (curcmd == dont_expand)
						{
							curcs = info(curinput.locfield)-cs_token_flag;
							curinput.locfield = 0;
							curcmd = eq_type(curcs);
							curchr = equiv(curcs);
							if (curcmd > max_command)
							{
								curcmd = relax;
								curchr = 257;
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
							begintokenlist(paramstack[curinput.limitfield+curchr-1], 0);
							recommence = true;
					}
				}
			}
			else
			{
				endtokenlist();
				recommence = true;
			}
		if (!recommence && curcmd <= out_param && curcmd >= tab_mark && alignstate == 0)
		{
			if (scannerstatus == 4 || curalign == 0)
				fatalerror("(interwoven alignment preambles are not allowed)");
			curcmd = info(curalign+5);
			info(curalign+5) = curchr;
			if (curcmd == omit)
				begintokenlist(omit_template, 2);
			else
				begintokenlist(v_part(curalign), 2);
			alignstate = 1000000;
			recommence = true;
		}
	} while (recommence);
}
