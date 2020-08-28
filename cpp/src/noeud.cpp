#include "noeud.h"
#include "police.h"
#include "charwarning.h"
#include "openlogfile.h"
#include "impression.h"
#include "geqdefine.h"
#include "eqdefine.h"
#include "lecture.h"
#include "erreur.h"
#include "xnoverd.h"
#include "texte.h"
#include "pushmath.h"
#include "pushnest.h"
#include "normmin.h"
#include "buildpage.h"
#include "makestring.h"
#include "erreur.h"
#include "texte.h"
#include "deleteglueref.h"
#include "cesure.h"
#include "sauvegarde.h"
#include "runaway.h"

LinkedNode* copynodelist(LinkedNode *p)
{
	static LinkedNode head;
	auto q = &head;
	for (; p; next(p))
	{
		q->link = p->copy();
		next(q);
	}
	q->link = nullptr;
	return head.link;
}
void flushnodelist(LinkedNode *p)
{
	while (p)
	{
		auto q = p->link;
		delete p;
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

void newhyphexceptions(void)
{
	char n, j;
	hyphpointer h;
	poolpointer u, v;
	auto t = scanleftbrace();
	curlang = cur_fam();
	if (curlang < 0 || curlang > 255)
		curlang = 0;
	n = 0;
	LinkedNode *p = nullptr;
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
						auto q = new TokenNode; // HyphenNode ???
						q->link = p;
						q->token = n;
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
							std::swap(hyphlist[h], p->num);
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
										std::swap(hyphlist[h], p->num);
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
									std::swap(hyphlist[h], p->num);
									std::swap(hyphword[h], s);
								}
							}
						if (h > 0)
							h--;
						else
							h = hyph_size;
					}
					hyphword[h] = s;
					hyphlist[h] = p->num;
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

CharNode* newcharacter(internalfontnumber f, eightbits c)
{
	auto &ft = fonts[f];
	if (ft.bc <= c && ft.ec >= c && skip_byte(ft.char_info(c)) > 0)
		return new CharNode(ft, c);
	charwarning(ft, c);
	return nullptr;
}

void newfont(smallnumber a)
{
	std::string t;
	if (jobname == "")
		openlogfile();
	auto u = getrtoken();
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
	scaled s;
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
	for (auto &ft: fonts)
		if (ft.name == curname && ft.area == curarea)
		{
			if (curname == flushablestring)
			{
				flush_string();
				curname = ft.name;
			}
			if (s > 0)
			{
				if (s == ft.size)
					break;
			}
			else 
				if (ft.size == xnoverd(ft.dsize, -s, 1000))
					break;
		}
	if (f >= fonts.size())
		f = readfontinfo(u, curname, curarea, s);
	equiv(u) = f;
	eqtb[frozen_null_font+f] = eqtb[u];
	text(frozen_null_font+f) = txt(t);
}

/*static halfword& every_par(void) { return equiv(every_par_loc); }*/
static TokenNode ep;//!< points to token list for \\everypar
static TokenNode* every_par(void) { return &ep; } 

void newgraf(bool indented)
{
	prev_graf = 0;
	if (mode == vmode || head != tail)
		tail_append(new GlueNode(par_skip_code));
	pushnest();
	mode = hmode;
	space_factor = 1000;
	set_cur_lang();
	clang = curlang;
	prev_graf = (normmin(left_hyphen_min())<<6+normmin(right_hyphen_min()))<<16+curlang;
	if (indented)
	{
		auto b = new BoxNode;
		b->width = par_indent();
		tail = b;
		head->link = tail;
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

GlueNode* newskipparam(smallnumber n)
{
	auto p = new GlueNode(new GlueSpec(glueParams[n]));
	p->glue_ptr->glue_ref_count = 0;
	p->subtype = n+1;
	return p;
}

void appendchoices(void)
{
	tail_append(new ChoiceNode);
	memoryword m;
	m.int_ = 0;
	savestack.push_back(m);
	pushmath(math_choice_group);
	auto _ = scanleftbrace();
}

void appenddiscretionary(halfword s)
{
	tail_append(new DiscNode);
	if (s == 1)
	{
		int c = cur_font().hyphenchar;
		if (c >= 0 && c < 0x1'00)
			dynamic_cast<DiscNode*>(tail)->pre_break = newcharacter(curFontNum(), c);
	}
	else
	{
		memoryword m;
		m.int_ = 0;
		savestack.push_back(m);
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
			tail_append(new GlueNode(fil_glue));
			break;
		case fill_code: 
			tail_append(new GlueNode(fill_glue));
			break;
		case ss_code: 
			tail_append(new GlueNode(ss_glue));
			break;
		case fil_neg_code:
			tail_append(new GlueNode(fil_neg_glue));
			break;
		case skip_code:
		{
			auto g = scanglue(mu_val);
			g->glue_ref_count--;
			tail_append(new GlueNode(g));
			break;
		}
		case mskip_code: 
		{
			auto g = scanglue(mu_val);
			g->glue_ref_count--;
			auto G = new GlueNode(g);
			G->subtype = mu_glue;
			tail_append(G);
		}
	}
}

void appenditaliccorrection(void)
{
	if (tail != head)
	{
		CharNode *p;
		if (tail->is_char_node())
			p = dynamic_cast<CharNode*>(tail);
		else 
			if (tail->type == ligature_node)
				p = &dynamic_cast<LigatureNode*>(tail)->lig_char;
			else
				return;
		tail_append(new KernNode(p->font.char_italic(p->character), explicit_));
	}
}

void appendkern(halfword s)
{
	tail_append(new KernNode(scandimen(s == mu_glue, false, false), s));
}

void appendpenalty(void)
{
	tail_append(new PenaltyNode(scanint()));
	if (mode == vmode)
		buildpage();
}

static int line_skip_limit(void) { return dimen_par(line_skip_limit_code); }

//! When a box is being appended to the current vertical list, the
//! baselineskip calculation is handled by the \a append_to_vlist routine.
void appendtovlist(halfword b)
{
	if (prev_depth > ignore_depth)
	{
		scaled d = baseline_skip->width-prev_depth-height(b);
		GlueNode *p;
		if (d < line_skip_limit())
			p = new GlueNode(line_skip);
		else
		{
			p = newskipparam(baseline_skip_code);
			p->glue_ptr->width = d;
		}
		tail_append(p);
	}
	tail_append(b);
	prev_depth = depth(b);
}

//! Handle spaces when <em> space_factor != 1000 </em>.
void appspace(halfword &mainp, fontindex &maink)
{
	GlueNode *q; // glue node
	if (space_factor >= 2000 && xspace_skip != zero_glue)
		q = new GlueNode(xspace_skip);
	else
	{
		GlueSpec *Mainp;
		if (space_skip != zero_glue)
			Mainp = space_skip;
		else // Find the glue specification, \a main_p, for text spaces in the current font
		{
			Mainp = cur_font().glue;
			if (Mainp == nullptr)
			{
				Mainp = new GlueSpec(zero_glue);
				maink = space_code+cur_font().parambase;
				Mainp->width = cur_font().space();
				Mainp->stretch = cur_font().space_stretch();
				Mainp->shrink = cur_font().space_shrink();
				cur_font().glue = Mainp;
			}
		}
		Mainp = new GlueSpec(Mainp);
		// Modify the glue specification in \a main_p according to the space factor
		if (space_factor >= 2000)
			Mainp->width += cur_font().extra_space();
		Mainp->stretch = xnoverd(Mainp->stretch, space_factor, 1000);
		Mainp->shrink = xnoverd(Mainp->shrink, 1000, space_factor);
		q = new GlueNode(Mainp);
		Mainp->glue_ref_count = 0;
		mainp = Mainp->num;
	}
	tail_append(q);
}

void followUntilBeforeTarget(LinkedNode* &running, LinkedNode *target)
{
	while (running->link != target)
		next(running);
}
