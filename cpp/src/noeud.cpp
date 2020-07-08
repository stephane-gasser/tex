#include "noeud.h"
#include "getavail.h"
#include "charwarning.h"
#include "getnode.h"
#include "openlogfile.h"
#include "impression.h"
#include "geqdefine.h"
#include "eqdefine.h"
#include "lecture.h"
#include "erreur.h"
#include "xnoverd.h"
#include "readfontinfo.h"
#include "texte.h"
#include "pushnest.h"
#include "normmin.h"
#include "buildpage.h"
#include "getavail.h"
#include "makestring.h"
#include "erreur.h"
#include "texte.h"
#include "flushlist.h"

void newhyphexceptions(void)
{
	char n, j;
	hyphpointer h;
	halfword p;
	poolpointer u, v;
	scanleftbrace();
	curlang = cur_fam();
	if (curlang < 0 || curlang > 255)
		curlang = 0;
	n = 0;
	p = 0;
	getxtoken();
	while (true)
	{
		switch (curcmd)
		{
			case letter:
			case other_char:
			case char_given:
				if (curchr == '-')
				{
					if (n < 63)
					{
						auto q = getavail();
						link(q) = p;
						info(q) = n;
						p = q;
					}
				}
				else 
					if (lc_code(curchr) == 0)
						error("Not a letter", "Letters in \\hyphenation words must have \\lccode>0.\nProceed; I'll ignore the character I just read.");
					else 
						if (n < 63)
						{
							n++;
							hc[n] = lc_code(curchr);
						}
				break;
			case char_num:
				curchr = scancharnum();
				curcmd = char_given;
				continue;
			case spacer:
			case right_brace:
				if (n > 1)
				{
					n++;
					hc[n] = curlang;
					h = 0;
					for (j = 1; j <= n; j++)
					{
						h = (2*h+hc[j])%hyph_size;
						append_char(hc[j]);
					}
					auto s = makestring();
					if (hyphcount == hyph_size)
						overflow("exception dictionary", hyph_size);
					hyphcount++;
					while (hyphword[h] != "")
					{
						if (hyphword[h].size() < s.size())
						{
							std::swap(hyphlist[h], p);
							std::swap(hyphword[h], s);
						}
						else 
							if (hyphword[h].size() == s.size())
							{
								u = 0;
								v = 0;
								bool label45 = false;
								do
								{
									if (hyphword[h][u] < s[v])
									{
										std::swap(hyphlist[h], p);
										std::swap(hyphword[h], s);
										label45 = true;
									}
									if (hyphword[h][u] > s[v])
										label45 = true;
									if (label45)
										break;
									u++;
									v++;
								} while (u < hyphword[h].size());
								if (!label45)
								{
									std::swap(hyphlist[h], p);
									std::swap(hyphword[h], s);
								}
							}
						if (h > 0)
							h--;
						else
							h = hyph_size;
					}
					hyphword[h] = s;
					hyphlist[h] = p;
				}
				if (curcmd == right_brace)
					return;
				n = 0;
				p = 0;
				break;
			default:
				error("Improper "+esc("hyphenation")+" will be flushed", "Hyphenation exceptions must contain only letters\nand hyphens. But continue; I'll forgive and forget.");
		}
		getxtoken();
	}
}

halfword newcharacter(internalfontnumber f, eightbits c)
{
	if (fontbc[f] <= c)
		if (fontec[f] >= c)
			if ((skip_byte(char_info(f, c)) > 0))
			{
				auto p = getavail();
				type(p) = f;
				subtype(p) = c;
				return p;
			}
	charwarning(f, c);
	return 0;
}

halfword newchoice(void)
{
	auto p = getnode(style_node_size);
	type(p) = choice_node;
	subtype(p) = 0;
	display_mlist(p) = 0;
	text_mlist(p) = 0;
	script_mlist(p) = 0;
	script_script_mlist(p) = 0;
	return p;
}

halfword newdisc(void)
{
	auto p = getnode(2);
	type(p) = disc_node;
	replace_count(p) = 0;
	pre_break(p) = 0;
	post_break(p) = 0;
	return p;
}

void newfont(smallnumber a)
{
	halfword u;
	scaled s;
	internalfontnumber f;
	std::string t;
	if (jobname == "")
		openlogfile();
	getrtoken();
	u = curcs;
	if (u >= hash_base)
		t = TXT(text(u));
	else 
		if (u >= single_base)
			if (u == txt("char"))
				t = "FONT";
			else
				t = char(u-single_base);
		else
			t = "FONT"+char(u-1);
	define(a, u, set_font, null_font);
	scanoptionalequals();
	scanfilename();
	nameinprogress = true;
	if (scankeyword("at"))
	{
		s = scan_normal_dimen();
		if (s <= 0 || s >= 134217728)
		{
			error("Improper `at' size ("+asScaled(s)+"pt), replaced by 10pt", "I can only handle fonts at positive sizes that are\nless than 2048pt, so I've changed what you said to 10pt.");
			s = 10*unity;
		}
	}
	else 
		if (scankeyword("scaled"))
		{
			s = -scanint();
			if (s >= 0 || s < -0x80'00)
			{
				interror(-s, "Illegal magnification has been changed to 1000", "The magnification ratio must be between 1 and 0x80'00.");
				s = -1000;
			}
		}
		else
			s = -1000;
	nameinprogress = false;
	auto flushablestring = strings.back();
	for (f = 1; f <= fontptr; f++)
		if (fontname[f] == curname && fontarea[f] == curarea)
		{
			if (curname == flushablestring)
			{
				flush_string();
				curname = fontname[f];
			}
			if (s > 0)
			{
				if (s == fontsize[f])
					break;
			}
			else 
				if (fontsize[f] == xnoverd(fontdsize[f], -s, 1000))
					break;
		}
	if (f > fontptr)
		f = readfontinfo(u, curname, curarea, s);
	equiv(u) = f;
	eqtb[frozen_null_font+f] = eqtb[u];
	text(frozen_null_font+f) = txt(t);
}

halfword newglue(halfword q)
{
	auto p = getnode(2);
	type(p) = glue_node;
	subtype(p) = 0;
	link(p+1) = 0;
	info(p+1) = q;
	link(q)++;
	return p;
}

static halfword& every_par(void) { return equiv(every_par_loc); }

void newgraf(bool indented)
{
	prev_graf = 0;
	if (mode == vmode || head != tail)
		tail_append(newparamglue(par_skip_code));
	pushnest();
	mode = hmode;
	space_factor = 1000;
	set_cur_lang();
	clang = curlang;
	prev_graf = (normmin(left_hyphen_min())<<6+normmin(right_hyphen_min()))<<16+curlang;
	if (indented)
	{
		tail = newnullbox();
		link(head) = tail;
		width(tail) = par_indent();
	}
	if (every_par())
		begintokenlist(every_par(), every_par_text);
	if (nestptr == 1)
		buildpage();
}

void newinteraction(void)
{
	println();
	interaction = curchr;
	if (interaction == batch_mode)
		selector = no_print;
	else
		selector = term_only;
	if (logopened)
		selector += 2;
}

halfword newkern(scaled w)
{
	auto p = getnode(2);
	type(p) = kern_node;
	subtype(p) = 0;
	width(p) = w;
	return p;
}

halfword newligature(quarterword f, quarterword c, halfword q)
{
	auto p = getnode(2);
	type(p) = ligature_node;
	type(p+1) = f;
	subtype(p+1) = c;
	link(p+1) = q;
	subtype(p) = 0;
	return p;
}

halfword newligitem(quarterword c)
{
	auto p = getnode(2);
	subtype(p) = c;
	link(p+1) = 0;
	return p;
}

halfword newmath(scaled w, smallnumber s)
{ 
	auto p = getnode(2);
	type(p) = math_node;
	subtype(p) = s;
	width(p) = w;
	return p;
}

halfword newnoad(void)
{
	auto p = getnode(noad_size);
	type(p) = ord_noad;
	subtype(p) = normal;
	mem[p+1].hh = emptyfield;
	mem[p+3].hh = emptyfield;
	mem[p+2].hh = emptyfield;
	return p;
}

halfword newnullbox(void)
{
	halfword p = getnode(box_node_size);
	type(p) = hlist_node;
	subtype(p) = 0;
	width(p) = 0;
	depth(p) = 0;
	height(p) = 0;
	shift_amount(p) = 0;
	list_ptr(p) = 0;
	glue_sign(p) = normal;
	glue_order(p) = normal;
	glue_set(p) = 0.0;
	return p;
}

halfword newparamglue(smallnumber n)
{
	auto p = getnode(2);
	type(p) = glue_node;
	subtype(p) = n+1;
	link(p+1) = 0;
	auto q = glue_par(n);
	info(p+1) = q;
	link(q)++;
	return p;
}

void newpatterns(void)
{
	char k, l;
	bool digitsensed;
	quarterword v;
	triepointer p, q;
	bool firstchild;
	ASCIIcode c;
	if (trienotready)
	{
		curlang = cur_fam();
		if (curlang <= 0 || curlang > 255)
				curlang = 0;
		scanleftbrace();
		k = 0;
		hyf[0] = 0;
		digitsensed = false;
		bool keepIn = true;
		while (keepIn)
		{
			getxtoken();
			switch (curcmd)
			{
				case letter:
				case other_char:
					if (digitsensed  || curchr < '0' || curchr > '9')
					{
						if (curchr == '.')
							curchr = 0;
						else
						{
							curchr = lc_code(curchr);
							if (curchr == 0)
								error("Nonletter", "(See Appendix H.)");
						}
						if (k < 63)
						{
							k++;
							hc[k] = curchr;
							hyf[k] = 0;
							digitsensed = false;
						}
					}
					else 
						if (k < 63)
						{
							hyf[k] = curchr-'0';
							digitsensed = true;
						}
					break;
				case spacer:
				case right_brace:
					if (k > 0)
					{
						if (hc[1] == 0)
							hyf[0] = 0;
						if (hc[k] == 0)
							hyf[k] = 0;
						l = k;
						v = 0;
						while (true)
						{
							if (hyf[l] != 0)
							v = newtrieop(k-l, hyf[l], v);
							if (l > 0)
								l--;
							else
								break;
						}
						q = 0;
						hc[0] = curlang;
						while (l <= k)
						{
							c = hc[l];
							l++;
							p = triel[q];
							firstchild = true;
							while (p > 0 && c > triec[p])
							{
								q = p;
								p = trier[q];
								firstchild = false;
							}
							if (p == 0 || c < triec[p])
							{
								if (trieptr == triesize)
									overflow("pattern memory", triesize);
								trieptr++;
								trier[trieptr] = p;
								p = trieptr;
								triel[p] = 0;
								if (firstchild)
									triel[q] = p;
								else
									trier[q] = p;
								triec[p] = c;
								trieo[p] = 0;
							}
							q = p;
						}
						if (trieo[q])
							error("Duplicate pattern", "(See Appendix H.)");
						trieo[q] = v;
					}
					if (curcmd == right_brace)
					{
						keepIn = false;
						continue;
					}
					k = 0;
					hyf[0] = 0;
					digitsensed = false;
					break;
				default:
					error("Bad "+esc("patterns"), "(See Appendix H.)");
			}
		}
	}
	else
	{
		error("Too late for "+esc("patterns"), "All patterns must be given before typesetting begins.");
		link(garbage) = scantoks(false, false);
		flushlist(defref);
	}
}

halfword newpenalty(int m)
{
	auto p = getnode(2);
	type(p) = penalty_node;
	subtype(p) = 0;
	penalty(p) = m;
	return p;
}

halfword newrule(void)
{
	auto p = getnode(rule_node_size);
	type(p) = rule_node;
	subtype(p) = 0;
	width(p) = null_flag;
	depth(p) = null_flag;
	height(p) = null_flag;
	return p;
}

void newsavelevel(groupcode c)
{
	check_full_save_stack();
	save_type(saveptr) = level_boundary;
	save_level(saveptr) = curgroup;
	save_index(saveptr) = curboundary;
	if (curlevel == 255)
		overflow("grouping levels", 255);
	curboundary = saveptr;
	curlevel++;
	saveptr++;
	curgroup = c;
}

halfword newskipparam(smallnumber n)
{
	tempptr = newspec(glue_par(n));
	auto p = newglue(tempptr);
	link(tempptr) = 0;
	subtype(p) = n+1;
	return p;
}

halfword newspec(halfword p)
{
	auto q = getnode(4);
	mem[q] = mem[p];
	link(q) = 0;
	mem[q+1] = mem[p+1];
	mem[q+2] = mem[p+2];
	mem[q+3] = mem[p+3];
	return q;
}

halfword newstyle(smallnumber s)
{
	auto p = getnode(style_node_size);
	type(p) = style_node;
	subtype(p) = s;
	width(p) = 0;
	depth(p) = 0;
	return p;
}

quarterword newtrieop(smallnumber d, smallnumber  n, quarterword v)
{
	int h = abs(n+313*d+361*v+1009*curlang)%(2*trieopsize)-trieopsize;
	while (true)
	{
		int l = trieophash[h];
		if (l == 0)
		{
			if (trieopptr == trieopsize)
				overflow("pattern memory ops", trieopsize);
			quarterword u = trieused[curlang];
			if (u == 255)
				overflow("pattern memory ops per language", 255);
			trieopptr++;
			u++;
			trieused[curlang] = u;
			hyfdistance[trieopptr] = d;
			hyfnum[trieopptr] = n;
			hyfnext[trieopptr] = v;
			trieoplang[trieopptr] = curlang;
			trieophash[h] = trieopptr;
			trieopval[trieopptr] = u;
			return u;
		}
		if (hyfdistance[l] == d && hyfnum[l] == n && hyfnext[l] == v && trieoplang[l] == curlang)
			return trieopval[l];
		if (h > -trieopsize)
			h--;
		else
			h = trieopsize;
	}
}

void newwhatsit(smallnumber s, smallnumber w)
{
	auto p = getnode(w);
	type(p) = whatsit_node;
	subtype(p) = s;
	tail_append(p);
}

void newwritewhatsit(smallnumber w)
{
	newwhatsit(curchr, w);
	int val;
	if (w != write_node_size)
		val = scanfourbitint();
	else
	{
		val = scanint();
		if (val < 0)
			val = 17;
		else 
			if (val > 15)
				val = 16;
	}
	write_stream(tail) = val;
}
