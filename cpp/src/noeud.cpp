#include "noeud.h"
#include "police.h"
#include "charwarning.h"
#include "openlogfile.h"
#include "impression.h"
#include "equivalent.h"
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
#include "xovern.h"
#include "multandadd.h"

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
	{
		t = eqtb_cs[u-hash_base].text;
		define(a, &eqtb_cs[u-hash_base], set_font, null_font);
	}
	else 
	{
		if (u >= single_base)
			if (u == txt("char"))
				t = "FONT";
			else
				t = char(u-single_base);
		else
			t = "FONT"+char(u-1);
		define(a, &eqtb_active[u-active_base], set_font, null_font);
	}
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
	int f; //ft
	if (f >= fonts.size())
		f = readfontinfo(u, curname, curarea, s);
	eqtb[u].int_ = f; // index : Font*
	eqtb_cs[f+frozen_null_font-hash_base] = eqtb[u];
	eqtb_cs[f+frozen_null_font-hash_base].text = t;
}

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
	auto p = new GlueNode(new GlueSpec(glue_par(n)));
	p->glue_ptr->glue_ref_count = 0;
	p->subtype = n+1;
	return p;
}

void appendchoices(void)
{
	tail_append(new ChoiceNode);
	auto m = new MemoryNode;
	m->int_ = 0;
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
		auto m = new MemoryNode;
		m->int_ = 0;
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

//! When a box is being appended to the current vertical list, the
//! baselineskip calculation is handled by the \a append_to_vlist routine.
void appendtovlist(BoxNode *b)
{
	if (prev_depth > ignore_depth)
	{
		scaled d = baseline_skip()->width-prev_depth-b->height;
		GlueNode *p;
		if (d < line_skip_limit())
			p = new GlueNode(line_skip());
		else
		{
			p = newskipparam(baseline_skip_code);
			p->glue_ptr->width = d;
		}
		tail_append(p);
	}
	tail_append(b);
	prev_depth = b->depth;
}

//! Handle spaces when <em> space_factor != 1000 </em>.
void appspace(LinkedNode *mainp, fontindex &maink)
{
	if (space_factor >= 2000 && xspace_skip() != zero_glue)
		mainp = new GlueNode(xspace_skip());
	else
	{
		GlueSpec *Mainp;
		if (space_skip() != zero_glue)
			Mainp = space_skip();
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
		mainp = new GlueNode(Mainp);
		Mainp->glue_ref_count = 0;
	}
	tail_append(mainp);
}

void followUntilBeforeTarget(LinkedNode* &running, LinkedNode *target)
{
	while (running->link != target)
		next(running);
}

void KernNode::mathkern(scaled m)
{
	if (subtype == mu_glue)
	{
		int n = xovern(m, unity);
		scaled f = remainder_;
		if (f < 0)
		{
			n--;
			f += unity;
		}
		width = mu_mult(n, width, f);
		subtype = 1;
	}
}

