#include "noeud.h"
#include "police.h"
#include "impression.h"
#include "equivalent.h"
#include "lecture.h"
#include "erreur.h"
#include "fichier.h"
#include "calcul.h"
#include "pushmath.h"
#include "etat.h"
#include "buildpage.h"
#include "chaine.h"
#include "erreur.h"
#include "cesure.h"
#include "sauvegarde.h"
#include "runaway.h"
#include "calcul.h"
#include "police.h"
#include "etat.h"
#include "getnext.h"

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

void newfont(char status, smallnumber prefix)
{
	std::string t;
	if (jobname == "")
		openlogfile();
	auto u = scanner.getR(status);
	if (u >= hash_base)
	{
		t = eqtb_cs[u-hash_base].text;
		eqtb_cs[u-hash_base].define(prefix, set_font, null_font);
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
		eqtb_active[u-active_base].define(prefix, set_font, null_font);
	}
	scanner.optionalEquals(status);
	scanfilename(status);
	nameinprogress = true;
	scaled s;
	if (scanner.isKeyword(status, "at"))
	{
		s = scanner.getNormalDimen(status);
		if (!between(1, s, (unity<<11)-1))
		{
			error("Improper `at' size ("+asScaled(s)+"pt), replaced by 10pt", "I can only handle fonts at positive sizes that are\nless than 2048pt, so I've changed what you said to 10pt.");
			s = 10*unity;
		}
	}
	else 
		if (scanner.isKeyword(status, "scaled"))
		{
			s = -scanner.getInt(status);
			if (!between(-(1<<15), s, -1))
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

void newgraf(char status, bool indented)
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
		beginTokenListAboveMacro(every_par(), every_par_text);
	if (nest.size() == 2)
		buildpage(status);
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

void appendchoices(char status)
{
	tail_append(new ChoiceNode);
	auto m = new MemoryNode;
	m->int_ = 0;
	savestack.push_back(m);
	pushmath(math_choice_group);
	scanner.leftBrace(status);
}

void appenddiscretionary(char status, halfword s)
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
		scanner.leftBrace(status);
		pushnest();
		mode = -hmode;
		space_factor = 1000;
	}
}

GlueNode *glueToAppend(char status, halfword s)
{
	switch (s)
	{
		case fil_code: 
			return new GlueNode(fil_glue);
		case fill_code: 
			return new GlueNode(fill_glue);
		case ss_code: 
			return new GlueNode(ss_glue);
		case fil_neg_code:
			return new GlueNode(fil_neg_glue);
		case skip_code:
		{
			auto g = scanner.getGlue(status, mu_val);
			g->glue_ref_count--;
			return new GlueNode(g);
		}
		default:
		//case mskip_code: 
		{
			auto g = scanner.getGlue(status, mu_val);
			g->glue_ref_count--;
			auto G = new GlueNode(g);
			G->subtype = mu_glue;
			return G;
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

AccentNoad::AccentNoad(char status)
{ 
	type = accent_noad; 
	subtype = normal; 
	nucleus.math_type = 0; // twohalves{0, 0};
	subscr.math_type = 0; // = twohalves{0, 0};
	supscr.math_type = 0; // = twohalves{0, 0};
	int val = scanner.getUInt15(status);
	accent_chr.math_type = math_char; 
	accent_chr.character = val&0xFF;
	accent_chr.fam = getFam(val);
	nucleus.scan(status);
}


RadicalNoad::RadicalNoad(char status, Token t)
{ 
	type = radical_noad; 
	subtype = normal; 
	nucleus.math_type = 0; // = twohalves{0, 0};
	subscr.math_type = 0; // = twohalves{0, 0};
	supscr.math_type = 0; // = twohalves{0, 0};
	left_delimiter.scan(status, true, t);
	nucleus.scan(status);
}

FractionNoad::FractionNoad(char status, halfword c, Token t) 
{ 
	type = fraction_noad; 
	subtype = normal; 
	numerator.math_type = sub_mlist;
	numerator.info = head->link;
	denominator.math_type = 0; // = twohalves{0, 0};
	if (c >= delimited_code)
	{
		left_delimiter.scan(status, false, t);
		right_delimiter.scan(status, false, t);
	}
	switch (c%delimited_code)
	{
		case above_code:
			thickness = scanner.getNormalDimen(status);
			break;
		case over_code: 
			thickness = default_code;
			break;
		case atop_code: 
			thickness = 0;
			break;
	}
}

LeftRightNoad::LeftRightNoad(char status, Token t)
{ 
	type = t.chr; 
	delimiter.scan(status, false, t);
}

int CharNode::width(void) { return fonts[font].char_width(character); }
int CharNode::depth(void) { return fonts[font].char_depth(character); }
int CharNode::height(void) { return fonts[font].char_height(character); }
int CharNode::italic(void) { return fonts[font].char_italic(character); }

LanguageWhatsitNode::LanguageWhatsitNode(ASCIIcode l) : WhatsitNode(language_node), what_lang(l), what_lhm(left_hyphen_min()), what_rhm(right_hyphen_min()) {}

std::string CharNode::shortDisplay(void)
{
	std::string s;
	if (font != fontinshortdisplay)
	{
		s += esc(fonts[font].name)+" ";
		fontinshortdisplay = font;
	}
	s += char(character);
	return s;
}

std::string GlueNode::shortDisplay(void) 
{ 
	if (glue_ptr != zero_glue)
		return " "; 
	return "";
}

std::string LigatureNode::shortDisplay(void) { return shortdisplay(lig_ptr); }
std::string DiscNode::shortDisplay(void) { return shortdisplay(pre_break)+shortdisplay(post_break); }


ShapeNode::ShapeNode(char status, int n) : values(2*n)
{
	for (int j = 0; j < 2*n; j++)
		values.push_back(scanner.getNormalDimen(status));
}

LinkedNode::~LinkedNode(void) 
{ 
	if (type != char_node && type > right_noad)
		confusion("flushing"); 
	flushnodelist(link);
}

LinkedNode *LinkedNode::copy(void)
{ 
	confusion("copying"); 
	return nullptr; 
}

WhatsitNode::~WhatsitNode(void) 
{ 
	if (subtype > language_node) 
		confusion("ext3"); 
}

ChoiceNode::~ChoiceNode(void) 
{ 
	flushnodelist(display_mlist); 
	flushnodelist(text_mlist); 
	flushnodelist(script_mlist); 
	flushnodelist(script_script_mlist);
}
		
DiscNode *DiscNode::copy(void) 
{ 
	auto d = new DiscNode; 
	d->pre_break = copynodelist(pre_break);  
	d->post_break = copynodelist(post_break); 
	return d; 
}

InsNode *InsNode::copy(void) 
{ 
	auto i = new InsNode; 
	i->height = height; 
	i->depth = depth; 
	i->split_top_ptr = split_top_ptr; 
	i->float_cost = float_cost; 
	split_top_ptr->glue_ref_count++; 
	i->ins_ptr = copynodelist(ins_ptr); 
	return i; 
}

AdjustNode *AdjustNode::copy(void) 
{ 
	auto a = new AdjustNode; 
	a->adjust_ptr = copynodelist(adjust_ptr); 
	return a; 
}

GlueNode *GlueNode::copy(void) 
{ 
	auto g = new GlueNode(glue_ptr); 
	g->leader_ptr = copynodelist(leader_ptr); 
	return g; 
}

BoxNode *BoxNode::copy(void) 
{ 
	auto r = new BoxNode; 
	r->width = width; 
	r->depth = depth; 
	r->height = height; 
	r->glue_set = glue_set; 
	r->glue_sign = glue_sign; 
	r->glue_order = glue_order; 
	r->list_ptr = copynodelist(list_ptr); 
	r->shift_amount = shift_amount; 
	return r; 
}

UnsetNode *UnsetNode::copy(void) 
{ 
	auto r = new UnsetNode; 
	r->width = width; 
	r->depth = depth; 
	r->height = height; 
	r->glue_shrink = glue_shrink; 
	r->glue_sign = glue_sign; 
	r->glue_order = glue_order; 
	r->list_ptr = copynodelist(list_ptr); 
	r->glue_stretch = glue_stretch; 
	return r; 
}

NoadContent::~NoadContent(void) 
{ 
	if (math_type >= sub_box) 
		flushnodelist(info); 
}

BoxNode::~BoxNode(void) { flushnodelist(list_ptr); }
AdjustNode::~AdjustNode(void) { flushnodelist(adjust_ptr); }
LigatureNode::~LigatureNode(void) { flushnodelist(lig_ptr); }
DiscNode::~DiscNode(void) { flushnodelist(pre_break); flushnodelist(post_break); }
InsNode::~InsNode(void) { flushnodelist(ins_ptr); deleteglueref(split_top_ptr); }
GlueNode::~GlueNode(void) { deleteglueref(glue_ptr); flushnodelist(leader_ptr); }

void CharNode::vlist(scaled) { confusion("vlistout"); }
WhatsitNode *WhatsitNode::copy(void) { confusion("ext2"); return nullptr; }
LigatureNode* LigatureNode::copy(void) { return new LigatureNode(font, character, dynamic_cast<CharNode*>(copynodelist(lig_ptr))); }

void deleteglueref(GlueSpec *p)
{
	if (p->glue_ref_count == 0)
		delete p;
	else
		p->glue_ref_count--;
}

GlueSpec *trapzeroglue(GlueSpec *g)
{
	if (g->width == 0 && g->stretch == 0 && g->shrink == 0)
	{
		zero_glue->glue_ref_count++;
		deleteglueref(g);
		return nullptr;
	}
	return g;
}
