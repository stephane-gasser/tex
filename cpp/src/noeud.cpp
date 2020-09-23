#include "noeud.h"
#include "police.h"
#include "impression.h"
#include "equivalent.h"
#include "lecture.h"
#include "erreur.h"
#include "fichier.h"
#include "calcul.h"
#include "pushmath.h"
#include "pushnest.h"
#include "buildpage.h"
#include "chaine.h"
#include "erreur.h"
#include "deleteglueref.h"
#include "cesure.h"
#include "sauvegarde.h"
#include "runaway.h"
#include "calcul.h"
#include "police.h"

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
		return new CharNode(f, c);
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
			if (u == null_cs)
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
		if (s <= 0 || s >= 2048*unity)
		{
			error("Improper `at' size ("+asScaled(s)+"pt), replaced by 10pt", "I can only handle fonts at positive sizes that are\nless than 2048pt, so I've changed what you said to 10pt.");
			s = 10*unity;
		}
	}
	else 
		if (scankeyword("scaled"))
		{
			s = -scanint();
			if (s >= 0 || s < -(1<<15))
			{
				interror(-s, "Illegal magnification has been changed to 1000", "The magnification ratio must be between 1 and 0x80'00.");
				s = -1000;
			}
		}
		else
			s = -1000;
	nameinprogress = false;
	for (size_t f = 0; f < fonts.size(); f++)
		if (auto &ft = fonts[f]; ft.name == curname && ft.area == curarea)
			if ((s > 0 && s == ft.size) || (s < 0 && ft.size == xnoverd(ft.dsize, -s, 1000)))
			{
				eqtb[u].int_ = f; // index : Font*
				eqtb_cs[f+frozen_null_font-hash_base] = eqtb[u];
				eqtb_cs[f+frozen_null_font-hash_base].text = t;
				break;
			}
	int f; //ft
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
	prev_graf = (left_hyphen_min()<<6+right_hyphen_min())<<16+curlang;
	if (indented)
	{
		auto b = new BoxNode;
		b->width = par_indent();
		tail = b;
		head->link = tail;
	}
	if (every_par())
		begintokenlist(every_par(), every_par_text);
	if (nest.size() == 2)
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
	(void)scanleftbrace();
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
		(void)scanleftbrace();
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
	if (tail == head)
		return;
	if (tail->type != char_node && tail->type != ligature_node)
		return;
	auto p = dynamic_cast<CharNode*>(tail);
	tail_append(new KernNode(fonts[p->font].char_italic(p->character), explicit_));
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

void followUntilBeforeTarget(LinkedNode* &running, LinkedNode *target)
{
	while (running->link != target)
		next(running);
}

void followUntilBeforeTarget(LinkedNode* start, LinkedNode* &running, LinkedNode *target)
{
	running = start;
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

AccentNoad::AccentNoad(void)
{ 
	type = accent_noad; 
	subtype = normal; 
	nucleus.math_type = 0; // twohalves{0, 0};
	subscr.math_type = 0; // = twohalves{0, 0};
	supscr.math_type = 0; // = twohalves{0, 0};
	int val = scanfifteenbitint();
	accent_chr.math_type = math_char; 
	accent_chr.character = val%0x1'00;
	accent_chr.fam = val >= var_code && fam_in_range() ? cur_fam() : (val>>8)%0x10;
	scanmath(nucleus);
}


RadicalNoad::RadicalNoad(Token t)
{ 
	type = radical_noad; 
	subtype = normal; 
	nucleus.math_type = 0; // = twohalves{0, 0};
	subscr.math_type = 0; // = twohalves{0, 0};
	supscr.math_type = 0; // = twohalves{0, 0};
	scandelimiter(left_delimiter, true, t);
	scanmath(nucleus);
}

FractionNoad::FractionNoad(halfword c, Token t) 
{ 
	type = fraction_noad; 
	subtype = normal; 
	numerator.math_type = sub_mlist;
	numerator.info = head->link;
	denominator.math_type = 0; // = twohalves{0, 0};
	if (c >= delimited_code)
	{
		scandelimiter(left_delimiter, false, t);
		scandelimiter(right_delimiter, false, t);
	}
	switch (c%delimited_code)
	{
		case above_code:
			thickness = scan_normal_dimen();
			break;
		case over_code: 
			thickness = default_code;
			break;
		case atop_code: 
			thickness = 0;
			break;
	}
}

LeftRightNoad::LeftRightNoad(Token t)
{ 
	type = t.chr; 
	scandelimiter(delimiter, false, t);
}

int CharNode::width(void) { return fonts[font].char_width(character); }
int CharNode::depth(void) { return fonts[font].char_depth(character); }
int CharNode::height(void) { return fonts[font].char_height(character); }
int CharNode::italic(void) { return fonts[font].char_italic(character); }

