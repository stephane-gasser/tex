#include "maincontrol.h"
#include "fixlanguage.h"
#include "getavail.h"
#include "newligature.h"
#include "newdisc.h"
#include "freenode.h"
#include "getnext.h"
#include "xtoken.h"
#include "scancharnum.h"
#include "newspec.h"
#include "newglue.h"
#include "newparamglue.h"
#include "getxtoken.h"
#include "charwarning.h"
#include "begintokenlist.h"
#include "backinput.h"
#include "pauseforinstructions.h"
#include "showcurcmdchr.h"
#include "appspace.h"
#include "reportillegalcase.h"
#include "newligitem.h"
#include "appendglue.h"
#include "insertdollarsign.h"
#include "appendkern.h"
#include "newsavelevel.h"
#include "unsave.h"
#include "offsave.h"
#include "scandimen.h"
#include "handlerightbrace.h"
#include "beginbox.h"
#include "scanbox.h"
#include "newgraf.h"
#include "indentinhmode.h"
#include "normalparagraph.h"
#include "buildpage.h"
#include "headforvmode.h"
#include "newkern.h"
#include "itsallover.h"
#include "endgraf.h"
#include "begininsertoradjust.h"
#include "makemark.h"
#include "appendpenalty.h"
#include "deletelast.h"
#include "unpackage.h"
#include "newkern.h"
#include "appenditaliccorrection.h"
#include "makeaccent.h"
#include "alignerror.h"
#include "noalignerror.h"
#include "omiterror.h"
#include "initalign.h"
#include "privileged.h"
#include "doendv.h"
#include "cserror.h"
#include "initmath.h"
#include "starteqno.h"
#include "newnoad.h"
#include "scanmath.h"
#include "scanrulespec.h"
#include "appenddiscretionary.h"
#include "setmathchar.h"
#include "scanfifteenbitint.h"
#include "scantwentysevenbitint.h"
#include "mathlimitswitch.h"
#include "mathac.h"
#include "mathradical.h"
#include "scanspec.h"
#include "pushnest.h"
#include "newstyle.h"
#include "appendchoices.h"
#include "subsup.h"
#include "mathfraction.h"
#include "mathleftright.h"
#include "aftermath.h"
#include "prefixedcommand.h"
#include "gettoken.h"
#include "saveforafter.h"
#include "issuemessage.h"
#include "openorclosein.h"
#include "showwhatever.h"
#include "shiftcase.h"
#include "doextension.h"

void goto70()
{
	mains = sf_code(curchr);
	if (mains == 1000)
		space_factor = 1000;
		else 
			if (mains < 1000)
			{
				if (mains > 0)
					space_factor = mains;
			}
			else 
				if (space_factor < 1000)
					space_factor = 1000;
				else
					space_factor = mains;
	mainf = cur_font();
	bchar = fontbchar[mainf];
	falsebchar = fontfalsebchar[mainf];
	if (mode > 0 && int_par(language_code) != clang)
		fixlanguage();
	ligstack = avail;
	if (ligstack == 0)
		ligstack = getavail();
	else
	{
		avail = link(ligstack);
		link(ligstack) = 0;
	}
	type(ligstack) = mainf;
	curl = curchr;
	subtype(ligstack) = curl;
	curq = tail;
	if (cancelboundary)
	{
		cancelboundary = false;
		maink = 0;
	}
	else
		maink = bcharlabel[mainf];
}

void goto80()
{
	if (curl < 256)
	{
		if (link(curq) > 0)
		if (subtype(tail) == hyphenchar[mainf])
			insdisc = true;
		if (ligaturepresent)
		{
			mainp = newligature(mainf, curl, link(curq));
			if (lfthit)
			{
				subtype(mainp) = 2;
				lfthit = false;
			}
			if (rthit && ligstack == 0)
			{
				subtype(mainp)++;
				rthit = false;
			}
			link(curq) = mainp;
			tail = mainp;
			ligaturepresent = false;
		}
		if (insdisc)
		{
			insdisc = false;
			if (mode > 0)
				tail_append(newdisc());
		}
	}
}

void goto101()
{
	mains = sf_code(curchr);
	if (mains == 1000)
		space_factor = 1000;
	else 
		if (mains < 1000)
		{
			if (mains > 0)
				space_factor = mains;
		}
		else 
			if (space_factor < 1000)
				space_factor = 1000;
			else
				space_factor = mains;
	ligstack = avail;
	if (ligstack == 0)
		ligstack = getavail();
	else
	{
		avail = link(ligstack);
		link(ligstack) = 0;
	}
	type(ligstack) = mainf;
	curr = curchr;
	subtype(ligstack) = curr;
	if (curr == falsebchar)
		curr = 256;
}

void goto95()
{
	mainp = link(ligstack+1);
	if (mainp > 0)
		tail_append(mainp);
	tempptr = ligstack;
	ligstack = link(tempptr);
	freenode(tempptr, 2);
	maini = char_info(mainf, curl);
	ligaturepresent = true;
	if (ligstack == 0)
		if (mainp > 0)
		{
			getnext();
			if (curcmd == letter || curcmd == other_char || curcmd == char_given)
			{
				goto101();
				return;
			}
			xtoken();
			if (curcmd == letter || curcmd == other_char || curcmd == char_given)
			{
				goto101();
				return;
			}
			if (curcmd == char_num)
			{
				scancharnum();
				curchr = curval;
				goto101();
				return;
			}
			if (curcmd == no_boundary)
				bchar = 256;
			curr = bchar;
			ligstack = 0;
			return;
		}
		else
			curr = bchar;
	else
		curr = subtype(ligstack);
}

void goto120()
{
	if (space_skip())
	{
		mainp = fontglue[cur_font()];
		if (mainp == 0)
		{
			mainp = newspec(0);
			maink = parambase[cur_font()]+2;
			width(mainp) = param(space_code, cur_font());
			stretch(mainp) = param(space_stretch_code, cur_font());
			shrink(mainp) = param(space_shrink_code, cur_font());
			fontglue[cur_font()] = mainp;
		}
		tempptr = newglue(mainp);
	}
	else
		tempptr = newparamglue(12);
	tail_append(tempptr);
	getxtoken();
}

bool goto92()
{
	if (curchr < fontbc[mainf] || curchr > fontec[mainf])
	{
		charwarning(mainf, curchr);
		link(ligstack) = avail;
		avail = ligstack;
		getxtoken();
		return true;
	}
	maini = char_info(mainf, curl);
	if (maini.b0 <= 0)
	{
		charwarning(mainf, curchr);
		link(ligstack) = avail;
		avail = ligstack;
		getxtoken();
		return true;
	}
	tail_append(ligstack);
	getnext();
	if (curcmd == letter || curcmd == other_char || curcmd == char_given)
		goto101();
	else
	{
		xtoken();
		if (curcmd == letter || curcmd == other_char || curcmd == char_given)
			goto101();
		else
		{
			if (curcmd == char_num)
			{
				scancharnum();
				curchr = curval;
				goto101();
			}
			else
			{
				if (curcmd == no_boundary)
					bchar = 256;
				curr = bchar;
				ligstack = 0;
			}
		}
	}
	return false;
}

void goto110112(bool is110)
{
	while (true)
	{
		if (is110)
		{
			if (maini.b2%4 != 1)
			{
				goto80();
				if (ligstack == 0)
					return;
				curq = tail;
				curl = subtype(ligstack);
				if (ligstack < himemmin)
					goto95();
				else 
					if (goto92())
						return;;
				is110 = true;
				continue;
			}
			if (curr == 256)
			{
				goto80();
				if (ligstack == 0)
					return;;
				curq = tail;
				curl = subtype(ligstack);
				if (ligstack < himemmin)
					goto95();
				else 
					if (goto92())
						return;
				is110 = true;
				continue;
			}
			maink = lig_kern_start(mainf, maini);
			mainj = fontinfo[maink].qqqq;
			if (skip_byte(mainj) > stop_flag)
			{
				maink = lig_kern_restart(mainf, mainj);
				mainj = fontinfo[maink].qqqq;
			}
		}
		if (mainj.b1 == curr)
			if (mainj.b0 <= 128)
			{
				if (mainj.b2 >= 128)
				{
					if (curl < 256)
					{
						if (link(curq) > 0 && subtype(tail) == hyphenchar[mainf])
							insdisc = true;
						if (ligaturepresent)
						{
							mainp = newligature(mainf, curl, link(curq));
							if (lfthit)
							{
								subtype(mainp) = 2;
								lfthit = false;
							}
							if (rthit && ligstack == 0)
							{
								subtype(mainp)++;
								rthit = false;
							}
							link(curq) = mainp;
							tail = mainp;
							ligaturepresent = false;
						}
						if (insdisc)
						{
							insdisc = false;
							if (mode > 0)
								tail_append(newdisc());
						}
					}
					tail_append(newkern(char_kern(mainf, mainj)));
					if (ligstack == 0)
						return;;
					curq = tail;
					curl = subtype(ligstack);
					if (ligstack < himemmin)
						goto95();
					else
						if (goto92())
							return;
					is110 = true;
					continue;
				}
				if (curl == 256)
					lfthit = true;
				else 
					if (ligstack == 0)
						rthit = true;
				if (interrupt)
					pauseforinstructions();
				switch (mainj.b2)
				{
					case 1:
					case 5:
						curl = mainj.b3;
						maini = char_info(mainf, curl);
						ligaturepresent = true;
						break;
					case 2:
					case 6:
						curr = mainj.b3;
						if (ligstack == 0)
						{
							ligstack = newligitem(curr);
							bchar = 256;
						}
						else 
							if (ligstack >= himemmin)
							{
								mainp = ligstack;
								ligstack = newligitem(curr);
								link(ligstack+1) = mainp;
							}
							else
								subtype(ligstack) = curr;
						break;
					case 3:
						curr = mainj.b3;
						mainp = ligstack;
						ligstack = newligitem(curr);
						link(ligstack) = mainp;
						break;
					case 7:
					case 11:
						if (curl < 256)
						{
							if (link(curq) > 0)
							if (subtype(tail) == hyphenchar[mainf])
								insdisc = true;
							if (ligaturepresent)
							{
								mainp = newligature(mainf, curl, link(curq));
								if (lfthit)
								{
									subtype(mainp) = 2;
									lfthit = false;
								}
								link(curq) = mainp;
								tail = mainp;
								ligaturepresent = false;
							}
							if (insdisc)
							{
								insdisc = false;
								if (mode > 0)
									tail_append(newdisc());
							}
						}
						curq = tail;
						curl = mainj.b3;
						maini = char_info(mainf, curl);
						ligaturepresent = true;
						break;
					default:
						curl = mainj.b3;
						ligaturepresent = true;
						if (ligstack == 0)
						{
							goto80();
							if (ligstack == 0)
								return;;
							curq = tail;
							curl = subtype(ligstack);
						}
						if (ligstack < himemmin)
							goto95();
						else
							if (goto92())
								return;;
				}
				if (mainj.b2 > 4 && mainj.b2 != 7)
				{
					goto80();
					if (ligstack == 0)
						return;;
					curq = tail;
					curl = subtype(ligstack);
					if (ligstack < himemmin)
						goto95();
					else 
						if (goto92())
							return;
					is110 = true;
					continue;
				}
				if (curl < 256)
				{
					is110 = true;
					continue;
				}
				maink = bcharlabel[mainf];
				mainj = fontinfo[maink].qqqq;
				is110 = false;
				continue;
			}
		if (mainj.b0 == 0)
			maink++;
		else
		{
			if (mainj.b0 >= 128)
			{
				goto80();
				if (ligstack == 0)
					return;;
				curq = tail;
				curl = subtype(ligstack);
				if (ligstack < himemmin)
					goto95();
				else 
					if (goto92())
						return;
				is110 = true;
				continue;
			}
			maink += mainj.b0+1;
		}
		mainj = fontinfo[maink].qqqq;
		is110 = false;
	}
}

#include <iostream>
void maincontrol(void)
{
	int t;
	if (every_job())
		begintokenlist(every_job(), 12);
	getxtoken();
	while (true)
	{
		if (interrupt && OKtointerrupt)
		{
			backinput();
			if (interrupt)
				pauseforinstructions();
			getxtoken();
			continue;
		}
		if (int_par(tracing_commands_code) > 0)
			showcurcmdchr();
		switch (abs(mode)+curcmd)
		{
			case hmode+letter:
			case hmode+other_char:
			case hmode+char_given:
				goto70();
				if (maink == 0)
				{
					if (!goto92())
						goto110112(true);
					continue;
				}
				curr = curl;
				curl = 256;
				mainj = fontinfo[maink].qqqq;
				goto110112(false);
				continue;
			case hmode+char_num:
				scancharnum();
				curchr = curval;
				if (maink == 0)
				{
					if (!goto92())
						goto110112(true);
					continue;
				}
				curr = curl;
				curl = 256;
				goto70();
				mainj = fontinfo[maink].qqqq;
				goto110112(false);
				continue;
			case hmode+no_boundary:
				getxtoken();
				if (curcmd == letter || curcmd == other_char || curcmd == char_given|| curcmd == char_num)
					cancelboundary = true;
				continue;
			case hmode+spacer: 
				if (space_factor == 1000)
				{
					goto120();
					continue;
				}
				appspace();
				break;
			case hmode+ex_space:
			case mmode+ex_space: 
				goto120();
				continue;
			case vmode+escape:
			case hmode+escape:
			case mmode+escape:
			case vmode+spacer:
			case mmode+spacer:
			case mmode+no_boundary: 
				break;
			case vmode+ignore_spaces:
			case hmode+ignore_spaces:
			case mmode+ignore_spaces:
				do
					getxtoken();
				while (curcmd == spacer);
				continue;
			case vmode+stop: 
				if (itsallover())
					return;
				break;
			case vmode+vmove:
			case hmode+hmove:
			case mmode+hmove:
			case vmode+last_item:
			case hmode+last_item:
			case mmode+last_item:
			case vmode+vadjust:
			case vmode+ital_corr:
			case vmode+eq_no:
			case hmode+eq_no:
			case vmode+mac_param:
			case hmode+mac_param:
			case mmode+mac_param: 
				reportillegalcase();
				break;
			case vmode+sup_mark:
			case hmode+sup_mark:
			case vmode+sub_mark:
			case hmode+sub_mark:
			case vmode+math_char_num:
			case hmode+math_char_num:
			case vmode+math_given:
			case hmode+math_given:
			case vmode+math_comp:
			case hmode+math_comp:
			case vmode+delim_num:
			case hmode+delim_num:
			case vmode+left_right:
			case hmode+left_right:
			case vmode+above:
			case hmode+above:
			case vmode+radical:
			case hmode+radical:
			case vmode+math_style:
			case hmode+math_style:
			case vmode+math_choice:
			case hmode+math_choice:
			case vmode+vcenter:
			case hmode+vcenter:
			case vmode+non_script:
			case hmode+non_script:
			case vmode+mkern:
			case hmode+mkern:
			case vmode+limit_switch:
			case hmode+limit_switch:
			case vmode+mskip:
			case hmode+mskip:
			case vmode+math_accent:
			case hmode+math_accent:
			case mmode+endv:
			case mmode+par_end:
			case mmode+stop:
			case mmode+vskip:
			case mmode+un_vbox:
			case mmode+valign:
			case mmode+hrule: 
				insertdollarsign();
				break;
			case vmode+hrule:
			case hmode+vrule:
			case mmode+vrule:
				tail_append(scanrulespec());
				if (abs(mode) == vmode)
					prev_depth = -0x1'00'00*1000;
				else 
					if (abs(mode) == hmode)
						space_factor = 1000;
				break;
			case vmode+vskip:
			case hmode+hskip:
			case mmode+hskip:
			case mmode+mskip: 
				appendglue();
				break;
			case vmode+kern:
			case hmode+kern:
			case mmode+kern:
			case mmode+mkern: 
				appendkern();
				break;
			case vmode+left_brace:
			case hmode+left_brace: 
				newsavelevel(1);
				break;
			case vmode+begin_group:
			case hmode+begin_group:
			case mmode+begin_group: 
				newsavelevel(14);
				break;
			case vmode+end_group:
			case hmode+end_group:
			case mmode+end_group: 
				if (curgroup == 14)
					unsave();
				else
					offsave();
				break;
			case vmode+right_brace:
			case hmode+right_brace:
			case mmode+right_brace: 
				handlerightbrace();
				break;
			case vmode+hmove:
			case hmode+vmove:
			case mmode+vmove:
				t = curchr;
				scandimen(false, false, false);
				if (t == 0)
					scanbox(curval);
				else
					scanbox(-curval);
				break;
			case vmode+leader_ship:
			case hmode+leader_ship:
			case mmode+leader_ship: 
				scanbox(0x40'00'02'00+curchr-99);
				break;
			case vmode+make_box:
			case hmode+make_box:
			case mmode+make_box: 
				beginbox(0);
				break;
			case vmode+start_par: 
				newgraf(curchr > 0);
				break;
			case vmode+letter:
			case vmode+other_char:
			case vmode+char_num:
			case vmode+char_given:
			case vmode+math_shift:
			case vmode+un_hbox:
			case vmode+vrule:
			case vmode+accent:
			case vmode+discretionary:
			case vmode+hskip:
			case vmode+valign:
			case vmode+ex_space:
			case vmode+no_boundary:
				backinput();
				newgraf(true);
				break;
			case hmode+start_par:
			case mmode+start_par: 
				indentinhmode();
				break;
			case vmode+par_end:
				normalparagraph();
				if (mode > 0)
				buildpage();
				break;
			case hmode+par_end:
				if (alignstate < 0)
					offsave();
				endgraf();
				if (mode == 1)
					buildpage();
				break;
			case hmode+stop:
			case hmode+vskip:
			case hmode+hrule:
			case hmode+un_vbox:
			case hmode+halign: 
				headforvmode();
				break;
			case vmode+insert:
			case hmode+insert:
			case mmode+insert:
			case hmode+vadjust:
			case mmode+vadjust: 
				begininsertoradjust();
				break;
			case vmode+mark:
			case hmode+mark:
			case mmode+mark: 
				makemark();
				break;
			case vmode+break_penalty:
			case hmode+break_penalty:
			case mmode+break_penalty: 
				appendpenalty();
				break;
			case vmode+remove_item:
			case hmode+remove_item:
			case mmode+remove_item: 
				deletelast();
				break;
			case vmode+un_vbox:
			case hmode+un_hbox:
			case mmode+un_hbox: 
				unpackage();
				break;
			case hmode+ital_corr: 
				appenditaliccorrection();
				break;
			case mmode+ital_corr:
				tail_append(newkern(0));
				break;
			case hmode+discretionary:
			case mmode+discretionary: 
				appenddiscretionary();
				break;
			case hmode+accent: 
				makeaccent();
				break;
			case vmode+out_param:
			case hmode+out_param:
			case mmode+out_param:
			case vmode+tab_mark:
			case hmode+tab_mark:
			case mmode+tab_mark: 
				alignerror();
				break;
			case vmode+no_align:
			case hmode+no_align:
			case mmode+no_align: 
				noalignerror();
				break;
			case vmode+omit:
			case hmode+omit:
			case mmode+omit: 
				omiterror();
				break;
			case vmode+halign:
			case hmode+valign: 
				initalign();
				break;
			case mmode+halign: 
				if (privileged())
					if (curgroup == 15)
						initalign();
					else
						offsave();
				break;
			case vmode+endv:
			case hmode+endv: 
				doendv();
				break;
			case vmode+end_cs_name:
			case hmode+end_cs_name:
			case mmode+end_cs_name: 
				cserror();
				break;
			case hmode+math_shift: 
				initmath();
				break;
			case mmode+eq_no: 
				if (privileged())
					if (curgroup == 15)
						starteqno();
					else
						offsave();
				break;
			case mmode+left_brace:
				tail_append(newnoad());
				backinput();
				scanmath(tail+1);
				break;
			case mmode+letter:
			case mmode+other_char:
			case mmode+char_given: 
				setmathchar(math_code(curchr));
				break;
			case mmode+char_num:
				scancharnum();
				curchr = curval;
				setmathchar(math_code(curchr));
				break;
			case mmode+math_char_num:
				scanfifteenbitint();
				setmathchar(curval);
				break;
			case mmode+math_given: 
				setmathchar(curchr);
				break;
			case mmode+delim_num:
				scantwentysevenbitint();
				setmathchar(curval/0x10'00);
				break;
			case mmode+math_comp:
				tail_append(newnoad());
				type(tail) = curchr;
				scanmath(tail+1);
				break;
			case mmode+limit_switch: 
				mathlimitswitch();
				break;
			case mmode+radical: 
				mathradical();
				break;
			case mmode+accent:
			case mmode+math_accent: 
				mathac();
				break;
			case mmode+vcenter:
				scanspec(12, false);
				normalparagraph();
				pushnest();
				mode = -vmode;
				prev_depth = -0x1'00'00*1000;
				if (every_vbox())
				begintokenlist(every_vbox(), 11);
				break;
			case mmode+math_style:
				tail_append(newstyle(curchr));
				break;
			case mmode+non_script:
				tail_append(newglue(0));
				subtype(tail) = cond_math_glue;
				break;
			case mmode+math_choice: 
				appendchoices();
				break;
			case mmode+sub_mark:
			case mmode+sup_mark: 
				subsup();
				break;
			case mmode+above: 
				mathfraction();
				break;
			case mmode+left_right: 
				mathleftright();
				break;
			case mmode+math_shift: 
				if (curgroup == 15)
					aftermath();
				else
					offsave();
				break;
			case vmode+toks_register:
			case hmode+toks_register:
			case mmode+toks_register:
			case vmode+assign_toks:
			case hmode+assign_toks:
			case mmode+assign_toks:
			case vmode+assign_int:
			case hmode+assign_int:
			case mmode+assign_int:
			case vmode+assign_dimen:
			case hmode+assign_dimen:
			case mmode+assign_dimen:
			case vmode+assign_glue:
			case hmode+assign_glue:
			case mmode+assign_glue:
			case vmode+assign_mu_glue:
			case hmode+assign_mu_glue:
			case mmode+assign_mu_glue:
			case vmode+assign_font_dimen:
			case hmode+assign_font_dimen:
			case mmode+assign_font_dimen:
			case vmode+assign_font_int:
			case hmode+assign_font_int:
			case mmode+assign_font_int:
			case vmode+set_aux:
			case hmode+set_aux:
			case mmode+set_aux:
			case vmode+set_prev_graf:
			case hmode+set_prev_graf:
			case mmode+set_prev_graf:
			case vmode+set_page_dimen:
			case hmode+set_page_dimen:
			case mmode+set_page_dimen:
			case vmode+set_page_int:
			case hmode+set_page_int:
			case mmode+set_page_int:
			case vmode+set_box_dimen:
			case hmode+set_box_dimen:
			case mmode+set_box_dimen:
			case vmode+set_shape:
			case hmode+set_shape:
			case mmode+set_shape:
			case vmode+def_code:
			case hmode+def_code:
			case mmode+def_code:
			case vmode+def_family:
			case hmode+def_family:
			case mmode+def_family:
			case vmode+set_font:
			case hmode+set_font:
			case mmode+set_font:
			case vmode+def_font:
			case hmode+def_font:
			case mmode+def_font:
			case vmode+register_:
			case hmode+register_:
			case mmode+register_:
			case vmode+advance:
			case hmode+advance:
			case mmode+advance:
			case vmode+multiply:
			case hmode+multiply:
			case mmode+multiply:
			case vmode+divide:
			case hmode+divide:
			case mmode+divide:
			case vmode+prefix:
			case hmode+prefix:
			case mmode+prefix:
			case vmode+let:
			case hmode+let:
			case mmode+let:
			case vmode+shorthand_def:
			case hmode+shorthand_def:
			case mmode+shorthand_def:
			case vmode+read_to_cs:
			case hmode+read_to_cs:
			case mmode+read_to_cs:
			case vmode+def:
			case hmode+def:
			case mmode+def:
			case vmode+set_box:
			case hmode+set_box:
			case mmode+set_box:
			case vmode+hyph_data:
			case hmode+hyph_data:
			case mmode+hyph_data:
			case vmode+max_command:
			case hmode+max_command:
			case mmode+max_command:
				prefixedcommand();
				break;
			case vmode+after_assignment:
			case hmode+after_assignment:
			case mmode+after_assignment:
				gettoken();
				aftertoken = curtok;
				break;
			case vmode+after_group:
			case hmode+after_group:
			case mmode+after_group:
				gettoken();
				saveforafter(curtok);
				break;
			case vmode+in_stream:
			case hmode+in_stream:
			case mmode+in_stream:
				openorclosein();
				break;
			case vmode+message:
			case hmode+message:
			case mmode+message:
				issuemessage();
				break;
			case vmode+case_shift:
			case hmode+case_shift:
			case mmode+case_shift:
				shiftcase();
				break;
			case vmode+xray:
			case hmode+xray:
			case mmode+xray:
				showwhatever();
				break;
			case vmode+extension:
			case hmode+extension:
			case mmode+extension:
				doextension();
		}
		getxtoken();
	}
}
