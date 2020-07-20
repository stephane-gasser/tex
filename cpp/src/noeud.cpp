#include "noeud.h"
#include "getavail.h"
#include "charwarning.h"
#include "openlogfile.h"
#include "impression.h"
#include "geqdefine.h"
#include "eqdefine.h"
#include "lecture.h"
#include "erreur.h"
#include "xnoverd.h"
#include "readfontinfo.h"
#include "texte.h"
#include "pushmath.h"
#include "pushnest.h"
#include "normmin.h"
#include "buildpage.h"
#include "getavail.h"
#include "makestring.h"
#include "erreur.h"
#include "texte.h"
#include "flushlist.h"
#include "deleteglueref.h"

halfword copynodelist(halfword p)
{
	auto h = getavail();
	auto q = h;
	while (p)
	{
		int words = 1;
		halfword r;
		if (is_char_node(p))
			r = getavail();
		else
			switch (type(p))
			{
				case hlist_node:
				case vlist_node:
				case unset_node:
					r = getnode(box_node_size);
					mem[r+6] = mem[p+6];
					mem[r+5] = mem[p+5];
					list_ptr(r) = copynodelist(list_ptr(p));
					words = 5;
					break;
				case rule_node:
					r = getnode(rule_node_size);
					words = rule_node_size;
					break;
				case ins_node:
					r = getnode(ins_node_size);
					mem[r+4] = mem[p+4];
					add_glue_ref(split_top_ptr(p));
					ins_ptr(r) = copynodelist(ins_ptr(p));
					words = ins_node_size-1;
					break;
				case whatsit_node:
					switch (subtype(p))
					{
						case open_node:
							r = getnode(open_node_size);
							words = open_node_size;
							break;
						case write_node:
						case special_node:
							r = getnode(write_node_size);
							add_token_ref(write_tokens(p));
							words = write_node_size;
							break;
						case close_node:
						case language_node:
							r = getnode(small_node_size);
							words = small_node_size;
							break;
						default:
							confusion("ext2");
					}
					break;
				case glue_node:
					r = getnode(small_node_size);
					add_glue_ref(glue_ptr(p));
					glue_ptr(r) = glue_ptr(p);
					leader_ptr(r) = copynodelist(leader_ptr(p));
					break;
				case kern_node:
				case math_node:
				case penalty_node:
					r = getnode(small_node_size);
					words = 2;
					break;
				case ligature_node:
					r = getnode(small_node_size);
					mem[lig_char(r)] = mem[lig_char(p)];
					lig_ptr(r) = copynodelist(lig_ptr(p));
					break;
				case disc_node:
					r = getnode(small_node_size);
					pre_break(r) = copynodelist(pre_break(p));
					post_break(r) = copynodelist(post_break(p));
					break;
				case mark_node:
					r = getnode(small_node_size);
					info(mark_ptr(p))++;
					words = small_node_size;
					break;
				case adjust_node:
					r = getnode(small_node_size);
					adjust_ptr(r) = copynodelist(adjust_ptr(p));
					break;
				default: 
					confusion("copying");
			}
		;
		for (;words > 0; words--)
			mem[r+words] = mem[p+words];
		link(q) = r;
		q = r;
		p = link(p);
	}
	link(q) = 0;
	q = link(h);
	link(h) = avail;
	avail = h;
	return q;
}

void flushnodelist(halfword p)
{
	while (p)
	{
		auto q = link(p);
		if (p >= himemmin)
		{
			link(p) = avail;
			avail = p;
		}
		else
		{
			switch (type(p))
			{
				case hlist_node:
				case vlist_node:
				case unset_node:
					flushnodelist(list_ptr(p));
					freenode(p, box_node_size);
					break;
				case rule_node:
					freenode(p, rule_node_size);
					break;
				case ins_node:
					flushnodelist(ins_ptr(p));
					deleteglueref(ins_ptr(p));
					freenode(p, ins_node_size);
					break;
				case whatsit_node:
					switch (subtype(p))
					{
						case open_node:
							freenode(p, open_node_size);
							break;
						case write_node:
						case special_node:
							deletetokenref(write_tokens(p));
							freenode(p, write_node_size);
							break;
						case close_node:
						case language_node: 
							freenode(p, small_node_size);
							break;
						default: 
							confusion("ext3");
					}
					break;
				case glue_node:
					deleteglueref(glue_ptr(p));
					if (leader_ptr(p))
						flushnodelist(leader_ptr(p));
					freenode(p, small_node_size);
					break;
				case kern_node:
				case math_node:
				case penalty_node: 
					freenode(p, small_node_size);
					break;
				case ligature_node: 
					flushnodelist(lig_ptr(p));
					freenode(p, small_node_size);
					break;
				case mark_node: 
					deletetokenref(mark_ptr(p));
					freenode(p, small_node_size);
					break;
				case disc_node:
					flushnodelist(pre_break(p));
					flushnodelist(post_break(p));
					freenode(p, small_node_size);
					break;
				case adjust_node: 
					flushnodelist(adjust_ptr(p));
					freenode(p, small_node_size);
					break;
				case style_node:
					freenode(p, style_node_size);
					break;
				case choice_node:
					flushnodelist(display_mlist(p));
					flushnodelist(text_mlist(p));
					flushnodelist(script_mlist(p));
					flushnodelist(script_script_mlist(p));
					freenode(p, style_node_size);
					break;
				case ord_noad:
				case op_noad:
				case bin_noad:
				case rel_noad:
				case open_noad:
				case close_noad:
				case punct_noad:
				case inner_noad:
				case radical_noad:
				case over_noad:
				case under_noad:
				case vcenter_noad:
				case accent_noad:
					if (math_type(nucleus(p)) >= sub_box)
						flushnodelist(nucleus(p));
					if (math_type(supscr(p)) >= sub_box)
						flushnodelist(info(supscr(p)));
					if (math_type(subscr(p)) >= sub_box)
						flushnodelist(info(subscr(p)));
					if (type(p) == radical_noad || type(p) == accent_noad)
						freenode(p, radical_noad_size);
					else
						freenode(p, noad_size);
					break;
				case left_noad:
				case right_noad:
					freenode(p, noad_size);
					break;
				case fraction_noad:
					flushnodelist(info(numerator(p)));
					flushnodelist(info(denominator(p)));
					freenode(p, fraction_noad_size);
					break;
				default: 
					confusion("flushing"); 
			}
		}
		p = q;
	}
}

void freenode(halfword p, halfword s)
{
	node_size(p) = s;
	link(p) = empty_flag;
	halfword q = llink(rover);
	llink(p) = q;
	rlink(p) = rover;
	llink(rover) = p;
	rlink(q) = p;
}

halfword getnode(int s)
{
	bool label20;
	halfword r;
	do
	{
		label20 = false;
		halfword p = rover;
		do
		{ 
			halfword q = p+node_size(p);
			while (link(q) == empty_flag)
			{
				auto t = rlink(q);
				if (q == rover)
					rover = t;
				llink(t) = llink(q);
				rlink(llink(q)) = t;
				q += node_size(q);
			}
			r = q-s;
			if (r > p+1)
			{
				node_size(p) = r-p;
				rover = p;
				link(r) = 0;
				return r;
			}
			if (r == p)
			if (rlink(p) != p)
			{
				rover = rlink(p);
				int t = llink(p);
				llink(rover) = t;
				rlink(t) = rover;
				link(r) = 0;
				return r;
			}
			node_size(p) = q-p;
			p = rlink(p);
		} while (p != rover);
		if (s == 1<<30)
			return empty_flag;
		if (lomemmax+2 < himemmin && lomemmax+2 <= empty_flag)
		{
			int t;
			if (himemmin-lomemmax >= 1998)
				t = lomemmax+1000;
			else
				t = lomemmax+1+(himemmin-lomemmax)/2;
			p = llink(rover);
			halfword q = lomemmax;
			rlink(p) = q;
			llink(rover) = q;
			if (t > empty_flag)
				t = empty_flag;
			rlink(q) = rover;
			llink(q) = p;
			link(q) = empty_flag;
			info(q) = t-lomemmax;
			lomemmax = t;
			link(lomemmax) = 0;
			info(lomemmax) = 0;
			rover = q;
			label20 = true;
		}
	} while (label20);
	overflow("main memory size", memmax+1-memmin);
	link(r) = 0;
	return r;
}

triepointer trienode(triepointer p)
{
	triepointer h = abs(triec[p]+1009*trieo[p]+2718*triel[p]+3142*trier[p])%triesize;
	while (true)
	{
		triepointer q = triehash[h];
		if (q == 0)
		{
			triehash[h] = p;
			return p;
		}
		if (triec[q] == triec[p] && trieo[q] == trieo[p] && triel[q] == triel[p] && trier[q] == trier[p])
			return q;
		if (h > 0)
			h--;
		else
			h = triesize;
	}
}

void newhyphexceptions(void)
{
	char n, j;
	hyphpointer h;
	halfword p;
	poolpointer u, v;
	auto t = scanleftbrace();
	curlang = cur_fam();
	if (curlang < 0 || curlang > 255)
		curlang = 0;
	n = 0;
	p = 0;
	t = getxtoken();
	while (true)
	{
		switch (t.cmd)
		{
			case letter:
			case other_char:
			case char_given:
				if (t.chr == '-')
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
					if (lc_code(t.chr) == 0)
						error("Not a letter", "Letters in \\hyphenation words must have \\lccode>0.\nProceed; I'll ignore the character I just read.");
					else 
						if (n < 63)
						{
							n++;
							hc[n] = lc_code(t.chr);
						}
				break;
			case char_num:
				t.chr = scancharnum();
				t.cmd = char_given;
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
				if (t.cmd == right_brace)
					return;
				n = 0;
				p = 0;
				break;
			default:
				error("Improper "+esc("hyphenation")+" will be flushed", "Hyphenation exceptions must contain only letters\nand hyphens. But continue; I'll forgive and forget.");
		}
		t = getxtoken();
	}
}

halfword newcharacter(internalfontnumber f, eightbits c)
{
	if (fontbc[f] <= c && fontec[f] >= c && skip_byte(char_info(f, c)) > 0)
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
	auto p = getnode(small_node_size);
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
	u = getrtoken();
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
	auto p = getnode(small_node_size);
	type(p) = glue_node;
	subtype(p) = normal;
	leader_ptr(p) = 0;
	glue_ptr(p) = q;
	glue_ref_count(q)++;
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

void newinteraction(Token t)
{
	println();
	interaction = t.chr;
	selector = interaction == batch_mode ? no_print : term_only;
	if (logopened)
		selector += 2;
}

halfword newkern(scaled w)
{
	auto p = getnode(small_node_size);
	type(p) = kern_node;
	subtype(p) = normal;
	width(p) = w;
	return p;
}

halfword newligature(quarterword f, quarterword c, halfword q)
{
	auto p = getnode(small_node_size);
	type(p) = ligature_node;
	font(lig_char(p)) = f;
	character(lig_char(p)) = c;
	lig_ptr(p) = q;
	subtype(p) = 0;
	return p;
}

halfword newligitem(quarterword c)
{
	auto p = getnode(small_node_size);
	character(p) = c;
	lig_ptr(p) = 0;
	return p;
}

halfword newmath(scaled w, smallnumber s)
{ 
	auto p = getnode(small_node_size);
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
	mem[nucleus(p)].hh = emptyfield;
	mem[subscr(p)].hh = emptyfield;
	mem[supscr(p)].hh = emptyfield;
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
	auto p = getnode(small_node_size);
	type(p) = glue_node;
	subtype(p) = n+1;
	leader_ptr(p) = 0;
	auto q = glue_par(n);
	glue_ptr(p) = q;
	glue_ref_count(q)++;
	return p;
}

void newpatterns(Token t)
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
		auto t = scanleftbrace();
		k = 0;
		hyf[0] = 0;
		digitsensed = false;
		bool keepIn = true;
		while (keepIn)
		{
			auto t = getxtoken();
			switch (t.cmd)
			{
				case letter:
				case other_char:
					if (digitsensed || t.chr < '0' || t.chr > '9')
					{
						if (t.chr == '.')
							t.chr = 0;
						else
						{
							t.chr = lc_code(t.chr);
							if (t.chr == 0)
								error("Nonletter", "(See Appendix H.)");
						}
						if (k < 63)
						{
							k++;
							hc[k] = t.chr;
							hyf[k] = 0;
							digitsensed = false;
						}
					}
					else 
						if (k < 63)
						{
							hyf[k] = t.chr-'0';
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
					if (t.cmd == right_brace)
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
		link(garbage) = scantoks(false, false, t);
		flushlist(defref);
	}
}

halfword newpenalty(int m)
{
	auto p = getnode(small_node_size);
	type(p) = penalty_node;
	subtype(p) = 0; //the |subtype| is not used
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
	glue_ref_count(tempptr) = 0;
	subtype(p) = n+1;
	return p;
}

halfword newspec(halfword p)
{
	auto q = getnode(glue_spec_size);
	mem[q] = mem[p];
	glue_ref_count(q) = 0;
	width(q) = width(p);
	stretch(q) = stretch(p);
	shrink(q) = shrink(p);
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

quarterword newtrieop(smallnumber d, smallnumber n, quarterword v)
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

void newwritewhatsit(smallnumber w, Token t)
{
	newwhatsit(t.chr, w);
	if (w != write_node_size)
		write_stream(tail) = scanfourbitint();
	else
	{
		int val = scanint();
		if (val < 0)
			val = 17;
		else 
			if (val > 15)
				val = 16;
		write_stream(tail) = val;
	}
}

void appendchoices(void)
{
	tail_append(newchoice());
	saved(0) = 0;
	saveptr++;
	pushmath(math_choice_group);
	auto _ = scanleftbrace();
}

void appenddiscretionary(halfword s)
{
	tail_append(newdisc());
	if (s == 1)
	{
		int c = hyphenchar[cur_font()];
		if (c >= 0 && c < 0x1'00)
			pre_break(tail) = newcharacter(cur_font(), c);
	}
	else
	{
		saved(0) = 0;
		saveptr++;
		newsavelevel(disc_group);
		auto _ = scanleftbrace();
		pushnest();
		mode = -hmode;
		space_factor = 1000;
	}
}

void appendglue(halfword s)
{
	switch (s)
	{
		case fil_code: 
			tail_append(newglue(fil_glue));
			break;
		case fill_code: 
			tail_append(newglue(fill_glue));
			break;
		case ss_code: 
			tail_append(newglue(ss_glue));
			break;
		case fil_neg_code:
			tail_append(newglue(fil_neg_glue));
			break;
		case skip_code: 
			tail_append(newglue(scanglue(glue_val)));
			glue_ref_count(tail)--;
			break;
		case mskip_code: 
			tail_append(newglue(scanglue(mu_val)));
			glue_ref_count(tail)--;
			subtype(tail) = mu_glue;
	}
}

void appenditaliccorrection(void)
{
	if (tail != head)
	{
		halfword p;
		if (is_char_node(tail))
			p = tail;
		else 
			if (type(tail) == ligature_node)
				p = lig_char(tail);
			else
				return;
		auto f = font(p);
		tail_append(newkern(char_italic(f, char_info(f, character(p)))));
		subtype(tail) = explicit_;
	}
}

void appendkern(halfword s)
{
	tail_append(newkern(scandimen(s == mu_glue, false, false)));
	subtype(tail) = s;
}

void appendpenalty(void)
{
	tail_append(newpenalty(scanint()));
	if (mode == vmode)
		buildpage();
}

static halfword& baseline_skip(void) { return glue_par(baseline_skip_code); }
static int line_skip_limit(void) { return dimen_par(line_skip_limit_code); }

//! When a box is being appended to the current vertical list, the
//! baselineskip calculation is handled by the \a append_to_vlist routine.
void appendtovlist(halfword b)
{
	if (prev_depth > ignore_depth)
	{
		scaled d = width(baseline_skip())-prev_depth-height(b);
		halfword p;
		if (d < line_skip_limit())
			p = newparamglue(line_skip_code);
		else
		{
			p = newskipparam(baseline_skip_code);
			width(tempptr) = d;
		}
		tail_append(p);
	}
	tail_append(b);
	prev_depth = depth(b);
}

//! additional space at end of sentence
static int& extra_space(internalfontnumber f) { return param(extra_space_code, f); }

static halfword& xspace_skip(void) { return glue_par(xspace_skip_code); }

//! Handle spaces when <em> space_factor != 1000 </em>.
void appspace(halfword &mainp, fontindex &maink)
{
	halfword q; // glue node
	if (space_factor >= 2000 && xspace_skip() != zero_glue)
		q = newparamglue(xspace_skip_code);
	else
	{
		if (space_skip() != zero_glue)
			mainp = space_skip();
		else // Find the glue specification, \a main_p, for text spaces in the current font
		{
			mainp = fontglue[cur_font()];
			if (mainp == 0)
			{
				mainp = newspec(zero_glue);
				maink = space_code+parambase[cur_font()];
				width(mainp) = space(cur_font());
				stretch(mainp) = space_stretch(cur_font());
				shrink(mainp) = space_shrink(cur_font());
				fontglue[cur_font()] = mainp;
			}
		}
		mainp = newspec(mainp);
		// Modify the glue specification in \a main_p according to the space factor
		if (space_factor >= 2000)
			width(mainp) += extra_space(cur_font());
		stretch(mainp) = xnoverd(stretch(mainp), space_factor, 1000);
		shrink(mainp) = xnoverd(shrink(mainp), 1000, space_factor);
		q = newglue(mainp);
		link(mainp) = 0;
	}
	tail_append(q);
}
