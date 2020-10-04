#include "formule.h"
#include "boite.h"
#include "vardelimiter.h"
#include "police.h"
#include "noeud.h"
#include "calcul.h"
#include "deleteglueref.h"
#include "erreur.h"
#include "popnest.h"
#include "equivalent.h"
#include "impression.h"
#include "primitive.h"

static smallnumber cursize;
static scaled curmu;

void setCurSize(smallnumber style, bool setMu)
{ 
	cursize = style < script_style ? text_size : 16*((style-text_style)/2); 
	if (setMu)
		curmu = xovern(math_quad(cursize), 18);
}

static int mathex(smallnumber p) { return fonts[fam_fnt(3+cursize)].param(p); }
	static int default_rule_thickness(void) { return mathex(8); }
	static int big_op_spacing1(void) { return mathex(9); } //!< minimum clearance above a displayed op
	static int big_op_spacing2(void) { return mathex(10); } //!< minimum clearance below a displayed op
	static int big_op_spacing3(void) { return mathex(11); } //!< minimum baselineskip above displayed op
	static int big_op_spacing4(void) { return mathex(12); } //!< minimum baselineskip below displayed op
	static int big_op_spacing5(void) { return mathex(13); } //!< padding above and below displayed limits
static int mathsy(smallnumber p, smallnumber c) { return fonts[fam_fnt(2+c)].param(p); }
	static int math_x_height(smallnumber c) { return mathsy(5, c); } //!< height of `x'
	int math_quad(smallnumber c) { return mathsy(6, c); } //!< 18mu
	static int num1(smallnumber c) { return mathsy(8, c); } //!< numerator shift-up in display styles
	static int num2(smallnumber c) { return mathsy(9, c); } //!< numerator shift-up in non-display, non-\atop 
	static int num3(smallnumber c) { return mathsy(10, c); } //!< numerator shift-up in non-display \atop
	static int denom1(smallnumber c) { return mathsy(11, c); } //!< denominator shift-down in display styles
	static int denom2(smallnumber c) { return mathsy(12, c); } //!< denominator shift-down in non-display styles
	static int sup1(smallnumber c) { return mathsy(13, c); } //!< superscript shift-up in uncramped display style 
	static int sup2(smallnumber c) { return mathsy(14, c); } //!< superscript shift-up in uncramped non-display
	static int sup3(smallnumber c) { return mathsy(15, c); } //!< superscript shift-up in cramped styles
	static int sub1(smallnumber c) { return mathsy(16, c); } //!< subscript shift-down if superscript is absent
	static int sub2(smallnumber c) { return mathsy(17, c); } //!< subscript shift-down if superscript is present
	static int sup_drop(smallnumber c) { return mathsy(18, c); } //!< superscript baseline below top of large box
	static int sub_drop(smallnumber c) { return mathsy(19, c); } //!< subscript baseline below bottom of large box
	static int delim1(smallnumber c) { return mathsy(20, c); } //!< size of \atopwithdelims delimiters
	static int delim2(smallnumber c) { return mathsy(21, c); } //!< size of \atopwithdelims delimiters in non-displays
	int axis_height(smallnumber c) { return mathsy(22, c); }  //!< height of fraction lines above the baseline

int& fam_fnt(halfword p) { return eqtb_local[p+math_font_base-local_base].int_; }

static void fetch(NoadContent &a, internalfontnumber &curf, quarterword &curc)
{
	curc = a.character;
	curf = fam_fnt(a.fam+cursize);
	auto &ft = fonts[curf];
	try
	{
		if (curf == null_font)
			throw 1;
		if (curc < ft.bc || curc > ft.ec)
			throw 0;
		if (!char_exists(ft.char_info(curc)))
			throw 0;
	}
	catch (int e)
	{
		if (e == 1)
			error(esc(primName[def_family][cursize])+" "+std::to_string(a.fam)+" is undefined (character "+char(curc)+")", "Somewhere in the math formula just ended, you used the\nstated character from an undefined font family. For example,\nplain TeX doesn't allow \\it or \\sl in subscripts. Proceed,\nand I'll try to forget that I needed that character.");
		else
			charwarning(ft, curc);
		a.fam = 0;
		a.character = 0;
	}
}

static GlueSpec *mathglue(GlueSpec *g, scaled m)
{
	int n = xovern(m, unity);
	scaled f = remainder_;
	if (f < 0)
	{
		n--;
		f += unity;
	}
	// m = unity * n + f
	auto p = new GlueSpec;
	p->width = mu_mult(n, g->width, f); // = (m *g->width) / unity;
	p->stretch_order = g->stretch_order;
	p->stretch = p->stretch_order == normal ? mu_mult(n, g->stretch, f) : g->stretch;
	p->shrink_order = g->shrink_order;
	p->shrink = p->shrink_order == normal ? mu_mult(n, g->shrink, f) : g->shrink;
	return p;
}

static int cramped_style(int c) { return 2*(c/2)+cramped; } //!< cramp the style
static int sub_style(int c) { return 2*(c/4)+script_style+cramped; } //!< smaller and cramped
static int sup_style(int c) { return 2*(c/4)+script_style+c%2; } //!< smaller

static void makeradical(RadicalNoad *Q)
{
	auto x = cleanbox(Q->nucleus, cramped_style(curstyle));
	scaled clr;
	if (curstyle < text_style)
		clr = default_rule_thickness()+abs(math_x_height(cursize))/4;
	else
	{
		clr = default_rule_thickness();
		clr += abs(clr)/4;
	}
	auto y = vardelimiter(Q->left_delimiter, cursize, x->height+x->depth+clr+default_rule_thickness());
	scaled delta = y->depth-(x->height+x->depth+clr);
	if (delta > 0)
		clr += half(delta);
	y->shift_amount = -(x->height+clr);
	y->link = overbar(x, clr, y->height);
	Q->nucleus.math_type = sub_box;
	Q->nucleus.info = hpack(y, 0, additional);
}
static int denom_style(int c) { return 2*(c/2)+cramped+2-2*(c/6); }  //!< smaller, cramped
static int num_style(int c) { return c+2-2*(c/6); } //!< smaller unless already script-script

static void makefraction(FractionNoad *Q)
{
	if (Q->thickness == default_code)
		Q->thickness = default_rule_thickness();
	auto x = cleanbox(Q->numerator, num_style(curstyle));
	auto z = cleanbox(Q->denominator, denom_style(curstyle));
	if (x->width < z->width)
		x = rebox(x, z->width);
	else
		z = rebox(z, x->width);
	scaled shiftup, shiftdown;
	if (curstyle < 2)
	{
		shiftup = num1(cursize);
		shiftdown = denom1(cursize);
	}
	else
	{
		shiftdown = denom2(cursize);
		if (Q->thickness)
			shiftup = num2(cursize);
		else
			shiftup = num3(cursize);
	}
	scaled clr, delta;
	if (Q->thickness == 0)
	{
		if (curstyle < 2)
			clr = 7*default_rule_thickness();
		else
			clr = 3*default_rule_thickness();
		delta = half(clr-((shiftup-x->depth)-(z->height-shiftdown)));
		if (delta > 0)
		{
			shiftup += delta;
			shiftdown += delta;
		}
	}
	else
	{
		if (curstyle < 2)
			clr = 3*Q->thickness;
		else
			clr = Q->thickness;
		delta = half(Q->thickness);
		scaled delta1 = clr-(shiftup-x->depth-(axis_height(cursize)+delta));
		scaled delta2 = clr-(axis_height(cursize)-delta-(z->height-shiftdown));
		if (delta1 > 0)
			shiftup += delta1;
		if (delta2 > 0)
			shiftdown += delta2;
	}
	auto v = new BoxNode;
	v->type = vlist_node;
	v->height = shiftup+x->height;
	v->depth = z->depth+shiftdown;
	v->width = x->width;
	if (Q->thickness == 0)
	{
		x->link = new KernNode((shiftup-x->depth)-(z->height-shiftdown));
		x->link->link = z;
	}
	else
	{
		auto y = new RuleNode(Q->thickness);
		y->link = new KernNode((axis_height(cursize)-delta)-(z->height-shiftdown));
		y->link->link = z;
		x->link = new KernNode((shiftup-x->depth)-(axis_height(cursize)+delta));
		x->link->link = y;
	}
	v->list_ptr = x;
	if (curstyle < 2)
		delta = delim1(cursize);
	else
		delta = delim2(cursize);
	x = vardelimiter(Q->left_delimiter, cursize, delta);
	x->link = v;
	z = vardelimiter(Q->right_delimiter, cursize, delta);
	v->link = z;
	Q->nucleus.info = hpack(x, 0, additional);
}

static void makemathaccent(AccentNoad *Q)
{
	internalfontnumber f;
	quarterword curc;
	fetch(Q->accent_chr, f, curc);
	if (char_exists(fonts[f].char_info(curc)))
	{
		auto c = curc;
		scaled s = 0;
		if (Q->nucleus.math_type == math_char)
		{
			fetch(Q->nucleus, f, curc);
			auto &ft = fonts[f];
				if (char_tag(ft.char_info(curc)) == lig_tag)
			{
				
				for (int a = ft.lig_kern_first(curc); true; a += Font::skip_byte(a)+1)
				{
					if (Font::next_char(a) == ft.skewchar)
					{
						if (Font::op_byte(a) >= kern_flag && Font::skip_byte(a) <= stop_flag)
							s = ft.char_kern(a);
						break;
					}
					if (Font::skip_byte(a) >= stop_flag)
						break;
				}
			}
		}
		auto x = cleanbox(Q->nucleus, cramped_style(curstyle));
		auto w = x->width;
		auto h = x->height;
		auto &ft = fonts[f];
		while (true)
		{
			if (char_tag(ft.char_info(c)) != list_tag)
				break;
			halfword y = rem_byte(ft.char_info(c));
			if (skip_byte(ft.char_info(y)) <= 0)
				break;
			if (ft.char_width(y) > w)
				break;
			c = y;
		}
		scaled delta = std::min(h, ft.x_height());
		if (Q->supscr.math_type || Q->subscr.math_type)
			if (Q->nucleus.math_type == math_char)
			{
				flushnodelist(x);
				auto n = new Noad;
				n->nucleus = Q->nucleus;
				n->supscr = Q->supscr;
				n->subscr = Q->subscr;
				Q->subscr.math_type = 0;
				// fam/character = 0
				Q->supscr.math_type = 0;
				// fam/character = 0
				//mem[supscr(q)].hh = twohalves{0, 0};
				//mem[subscr(q)].hh = twohalves{0, 0};
				Q->nucleus.math_type = sub_mlist;
				Q->nucleus.info = n;
				x = cleanbox(Q->nucleus, curstyle);
				delta += x->height-h;
				h = x->height;
			}
		auto y = charbox(f, c);
		y->shift_amount = s+half(w-y->width);
		y->width = 0;
		y->link = new KernNode(-delta);
		y->link->link = x;
		y = vpack(y, 0, additional);
		y->width = x->width;
		if (y->height < h)
		{
			appendAtStart(y->list_ptr, new KernNode(h-y->height));
			y->height = h;
		}
		Q->nucleus.math_type = sub_box;
		Q->nucleus.info = y;
	}
}

static void makeord(Noad *Q)
{
	bool label20 = false;
	do
	{
		if (Q->subscr.math_type == 0 && Q->supscr.math_type == 0 && Q->nucleus.math_type == math_char)
		{
			auto p = Q;
			next(p);
			if (p && p->type >= ord_noad && p->type <= punct_noad && p->nucleus.math_type == math_char && p->nucleus.fam == Q->nucleus.fam)
			{
				Q->nucleus.math_type = math_text_char;
				internalfontnumber f;
				quarterword curc;
				fetch(Q->nucleus, f, curc);
				auto &ft = fonts[f];
				if (char_tag(ft.char_info(curc)) == lig_tag)
				{
					curc = p->nucleus.character;
					for (int a = ft.lig_kern_first(curc); true; a += Font::skip_byte(a)+1)
					{
						if (Font::next_char(a) == curc && Font::skip_byte(a) <= stop_flag)
							if (Font::op_byte(a) >= kern_flag)
							{
								appendAtStart(Q->link, new KernNode(ft.char_kern(a)));
								return;
							}
							else
							{
								switch (Font::op_byte(a))
								{
									// AB -> CB (symboles =:| et =:|>)
									case 1:
									case 5: 
										Q->nucleus.character = rem_byte(Font::infos(a));
										break;
									// AB -> AC (symboles |=: et |=:>)
									case 2:
									case 6: 
										p->nucleus.character = rem_byte(Font::infos(a));
										break;
									// AB -> ACB (symboles |=:|, |=:|> et |=:|>>)
									case 3:
									case 7:
									case 11:
									{
										auto r = new Noad;
										r->nucleus.character = rem_byte(Font::infos(a));
										r->nucleus.fam = Q->nucleus.fam;
										appendAtStart(Q->link, r);
										if (Font::op_byte(a) < 11) // symboles |=:| et |=:|>
											r->nucleus.math_type = math_char;
										else // symbole |=:|>>
											r->nucleus.math_type = math_text_char;
										break;
									// AB -> C (symbole =:)
									}
									default:
										Q->nucleus.character = rem_byte(Font::infos(a));
										Q->subscr = p->subscr;
										Q->supscr = p->supscr;
										removeNodeAfter(Q);
								}
								if (Font::op_byte(a) > 3)
									return;
								Q->nucleus.math_type = math_char;
								label20 = true;
							}
						if (label20)
							break;
						if (Font::skip_byte(a) >= stop_flag)
							return;
					}
				}
			}
		}
	} while (label20);
}

static void makescripts(Noad *q, scaled delta)
{
	auto p = new_hlist(q);
	scaled shiftup, shiftdown;
	if (p->type == char_node)
	{
		shiftup = 0;
		shiftdown = 0;
	}
	else
	{
		auto z = hpack(p, 0, additional);
		smallnumber t = curstyle < script_style ? script_size : script_script_size;
		shiftup = z->height-sup_drop(t);
		shiftdown = z->depth+sub_drop(t);
		delete z;
	}
	scaled clr;
	BoxNode *x;
	if (q->supscr.math_type == 0)
	{
		x = cleanbox(q->subscr, sub_style(curstyle));
		x->width += script_space();
		if (shiftdown < sub1(cursize))
			shiftdown = sub1(cursize);
		clr = x->height-(math_x_height(cursize)*4)/5;
		if (shiftdown < clr)
			shiftdown = clr;
		x->shift_amount = shiftdown;
	}
	else
	{
		x = cleanbox(q->supscr, sup_style(curstyle));
		x->width += script_space();
		if (curstyle%2)
			clr = sup3(cursize);
		else 
			if (curstyle < 2)
				clr = sup1(cursize);
			else
				clr = sup2(cursize);
		if (shiftup < clr)
			shiftup = clr;
		clr = x->depth+abs(math_x_height(cursize))/4;
		if (shiftup < clr)
			shiftup = clr;
		if (q->subscr.math_type == 0)
			x->shift_amount = -shiftup;
		else
		{
			auto y = cleanbox(q->subscr, sub_style(curstyle));
			y->width += script_space();
			if (shiftdown < sub2(cursize))
				shiftdown = sub2(cursize);
			clr = 4*default_rule_thickness()-(shiftup-x->depth-(y->height-shiftdown));
			if (clr > 0)
			{
				shiftdown += clr;
				clr = (abs(math_x_height(cursize)*4)/5)-(shiftup-x->depth);
				if (clr > 0)
				{
					shiftup += clr;
					shiftdown -= clr;
				}
			}
			x->shift_amount = delta;
			x->link = new KernNode(shiftup-x->depth-(y->height-shiftdown));
			x->link->link = y;
			x = vpack(x, 0, additional);
			x->shift_amount = shiftdown;
		}
	}
	if (new_hlist(q) == 0)
		q->nucleus.info = x; // new_hlist(q) = x;
	else
	{
		followUntilEnd(new_hlist(q), p);
		p->link = x;
	}
}

static void makeunder(Noad *q)
{
	auto x = cleanbox(q->nucleus, curstyle);
	x->link = new KernNode(3*default_rule_thickness());
	x->link->link = new RuleNode(default_rule_thickness());
	auto y = vpack(x, 0, additional);
	scaled delta = y->height+y->depth+default_rule_thickness();
	y->height = x->height;
	y->depth = delta-y->height;
	q->nucleus.math_type = sub_box;
	q->nucleus.info = y;
}

static void makevcenter(Noad *q)
{
	auto v = dynamic_cast<BoxNode*>(q->nucleus.info);
	if (!v || v->type != vlist_node)
		confusion("vcenter");
	scaled delta = v->height+v->depth;
	v->height = axis_height(cursize)+half(delta);
	v->depth = delta-v->height;
}

static void makeover(Noad *q)
{
	q->nucleus.math_type = sub_box;
	q->nucleus.info = overbar(cleanbox(q->nucleus, cramped_style(curstyle)), 3*default_rule_thickness(), default_rule_thickness());
}

BoxNode* overbar(BoxNode *b, scaled k, scaled t)
{
	auto p = new KernNode(t);
	p->link = new RuleNode(t);
	p->link->link = new KernNode(k);
	p->link->link->link = b;
	return vpack(p, 0, additional);
}

static scaled makeop(Noad *Q)
{
	if (Q->subtype == normal && curstyle < text_style)
		Q->subtype = limits;
	scaled delta;
	if (Q->nucleus.math_type == math_char)
	{
		internalfontnumber f;
		quarterword curc;
		fetch(Q->nucleus, f, curc);
		auto &ft = fonts[f];
		if (curstyle < text_style && char_tag(ft.char_info(curc)) == list_tag)
		{
			auto c = rem_byte(ft.char_info(curc));
			if (char_exists(ft.char_info(c)))
			{
				curc = c;
				Q->nucleus.character = c;
			}
		}
		delta = ft.char_italic(curc);
		auto x = cleanbox(Q->nucleus, curstyle);
		if (Q->subscr.math_type && Q->subtype != limits)
		x->width -= delta;
		x->shift_amount = half(x->height-x->depth)-axis_height(cursize);
		Q->nucleus.math_type = sub_box;
		Q->nucleus.info = x;
	}
	else
		delta = 0;
	if (Q->subtype == limits)
	{
		auto x = cleanbox(Q->supscr, sup_style(curstyle));
		auto y = cleanbox(Q->nucleus, curstyle);
		auto z = cleanbox(Q->subscr, sub_style(curstyle));
		auto v = new BoxNode;
		v->type = vlist_node;
		v->width = std::max(std::max(x->width, y->width), z->width);
		x = rebox(x, v->width);
		y = rebox(y, v->width);
		z = rebox(z, v->width);
		x->shift_amount = half(delta);
		z->shift_amount = -x->shift_amount;
		v->height = y->height;
		v->depth = y->depth;
		if (Q->supscr.math_type == 0)
		{
			delete x;
			v->list_ptr = y;
		}
		else
		{
			scaled shiftup = big_op_spacing3()-x->depth;
			if (shiftup < big_op_spacing1())
				shiftup = big_op_spacing1();
			x->link = new KernNode(shiftup);
			x->link->link = y;
			v->list_ptr = new KernNode(big_op_spacing5());
			v->list_ptr->link = x;
			v->height += mathex(big_op_spacing5())+x->height+x->depth+shiftup;
		}
		if (Q->subscr.math_type == 0)
			delete z;
		else
		{
			scaled shiftdown = big_op_spacing4()-z->height;
			if (shiftdown < big_op_spacing2())
				shiftdown = big_op_spacing2();
			y->link = new KernNode(shiftdown);
			y->link->link = z;
			z->link = new KernNode(big_op_spacing5());
			v->depth += big_op_spacing5()+z->height+z->depth+shiftdown;
		}
		Q->nucleus.info = v; //new_hlist(Q) = v
	}
	return delta;
}


static smallnumber makeleftright(LeftRightNoad *q, smallnumber style, scaled maxd, scaled maxh)
{
	setCurSize(style, false);
	scaled delta2 = maxd+axis_height(cursize);
	scaled delta1 = std::max(delta2, maxh+maxd-delta2);
	scaled delta = std::max(2*delta1-delimiter_shortfall(), (delta1/500)*delimiter_factor());
	q->nucleus.info = vardelimiter(q->delimiter, cursize, delta);
	return q->type-(left_noad-open_noad);
}

static void updateMax(Noad *q, scaled &maxh, scaled &maxd)
{
	auto z = hpack(new_hlist(q), 0, additional);
	maxh = std::max(z->height, maxh);
	maxd = std::max(z->depth, maxd);
	delete z;
}

void FractionNoad::mToH(scaled &maxh, scaled &maxd)
{
	makefraction(this);
	updateMax(this, maxh, maxd);
}

void RadicalNoad::mToH(void) { makeradical(this); }
void KernNode::mToH(void) { mathkern(curmu); }
void AccentNoad::mToH(void) { makemathaccent(this); }

void Noad::mToH(scaled &, scaled &) 
{ 
	switch (type)
	{
		case open_noad:
		case inner_noad: 
			break;
		case ord_noad: 
			makeord(this); 
			break;
		case over_noad:
			makeover(this);
			break;
		case under_noad:
			makeunder(this);
			break;
		case vcenter_noad: 
			makevcenter(this);
			break;
	}
}

bool Noad::mToH(scaled &delta, scaled &maxh, scaled &maxd)
{
	delta = makeop(this);
	if (subtype == 1)
	{
		updateMax(this, maxh, maxd);
		return true;
	}
	return false;
}

void GlueNode::mToH(scaled &, scaled &) 
{
	if (subtype == mu_glue)
	{
		auto y = mathglue(glue_ptr, curmu);
		deleteglueref(glue_ptr);
		glue_ptr = y;
		subtype = 0;
		return;
	}
	if (cursize && subtype == cond_math_glue)
	{
		if (link && (link->type == glue_node || link->type == kern_node))
		{
			auto p = link;
			next(link);
			p->link = nullptr;
			flushnodelist(p);
		}
	}
}

void RuleNode::mToH(scaled &maxh, scaled &maxd)
{
	maxh = std::max(height, maxh);
	maxd = std::max(depth, maxd);
}

void ChoiceNode::mToH(LinkedNode* &p)
{
	switch (curstyle/2)
	{
		case 0:
			p = display_mlist;
			display_mlist = nullptr;
			break;
		case 1:
			p = text_mlist;
			text_mlist = nullptr;
			break;
		case 2:
			p = script_mlist;
			script_mlist = nullptr;
			break;
		case 3:
			p = script_script_mlist;
			script_script_mlist = nullptr;
	}
	flushnodelist(display_mlist);
	flushnodelist(text_mlist);
	flushnodelist(script_mlist);
	flushnodelist(script_script_mlist);
}

void Noad::mToH2(scaled &delta, scaled &maxd, scaled &maxh)
{
	switch (nucleus.math_type)
	{
		case math_char:
		case math_text_char:
		{
			quarterword curc;
			internalfontnumber f;
			fetch(nucleus, f, curc);
			if (auto &ft = fonts[f]; char_exists(ft.char_info(curc)))
			{
				delta = ft.char_italic(curc);
				nucleus.info = newcharacter(fam_fnt(nucleus.fam+cursize), curc);
				if (nucleus.math_type == math_text_char && ft.space())
					delta = 0;
				if (subscr.math_type == 0 && delta)
				{
					nucleus.info->link = new KernNode(delta);
					delta = 0;
				}
			}
			else
				nucleus.info = nullptr;
			break;
		}
		case 0:
			nucleus.info = nullptr;
			break;
		case sub_box: 
			break;
		case sub_mlist:
		{
			curmlist = dynamic_cast<Noad*>(nucleus.info);
			auto savestyle = curstyle;
			mlistpenalties = false;
			mlisttohlist();
			curstyle = savestyle;
			setCurSize(curstyle);
			nucleus.info = hpack(temp_head->link, 0, additional);
			break;
		}
		default: 
			confusion("mlist2");
	}
	if (subscr.math_type || supscr.math_type)
		makescripts(this, delta);
	updateMax(this, maxh, maxd);
}

void mlisttohlist(void)
{
	auto mlist = curmlist;
	auto penalties = mlistpenalties;
	auto style = curstyle;
	smallnumber prevType = op_noad;
	scaled maxh = 0;
	scaled maxd = 0;
	setCurSize(curstyle);
	for (LinkedNode *q = mlist; q; next(q))
	{
		scaled delta = 0;
		switch (q->type)
		{
			case bin_noad: 
				switch (prevType)
				{
					case bin_noad:
					case op_noad:
					case rel_noad:
					case open_noad:
					case punct_noad:
					case left_noad:
						q->type = ord_noad;
						q->mToH();
				}
				q->mToH2(delta, maxh, maxd);
				break;
			case ord_noad: 
			case over_noad: 
			case under_noad: 
			case vcenter_noad: 
			case radical_noad:
			case accent_noad: 
			case open_noad:
			case inner_noad: 
				q->mToH();
				q->mToH2(delta, maxh, maxd);
				break;
			case op_noad:
				if (q->mToH(delta, maxh, maxd))
					break; 
				[[fallthrough]];
			case rel_noad:
			case close_noad:
			case punct_noad:
				q->mToH2(delta, maxh, maxd);
				break;
			case left_noad: 
			case right_noad:
				break;
			case fraction_noad:
				q->mToH(maxh, maxd);
				break;
			case kern_node:
				q->mToH();
				break;
			case style_node:
				curstyle = q->getSubtype();
				setCurSize(curstyle);
				break;
			case choice_node:
			{
				LinkedNode *p;
				q->mToH(p);
				replaceNode(q, new StyleNode(curstyle));
				if (p)
				{
					auto z = q->link;
					followUntilEnd(q, p); // q -> ... -> p -> nullptr
					p->link = z;
				}
				break;
			}
			case rule_node:
			case glue_node:
				q->mToH(maxh, maxd); [[fallthrough]];
			case ins_node:
			case mark_node:
			case adjust_node:
			case whatsit_node:
			case penalty_node:
			case disc_node: 
				break;
			default: 
				confusion("mlist1");
		}
		if (q->type >= ord_noad && q-> type <= right_noad)
			prevType = q->type;
	}
	if (prevType == bin_noad)
		prevType = ord_noad;
	temp_head->link = nullptr;
	prevType = 0;
	curstyle = style;
	setCurSize(curstyle);
	LinkedNode *p = temp_head;
	for (LinkedNode *q = mlist; q; )
	{
		smallnumber t = ord_noad;
		int pen = inf_penalty;
		switch (q->type)
		{
			case op_noad:
			case open_noad:
			case close_noad:
			case punct_noad:
			case inner_noad: 
				t = q->type;
				break;
			case bin_noad:
				t = bin_noad;
				pen = bin_op_penalty();
				break;
			case rel_noad:
				t = rel_noad;
				pen = rel_penalty();
				break;
			case ord_noad:
			case vcenter_noad:
			case over_noad:
			case under_noad:
				break;
			case radical_noad: 
				break;
			case accent_noad:
				break;
			case fraction_noad:
				t = inner_noad;
				break;
			case left_noad:
			case right_noad:
				t = makeleftright(dynamic_cast<LeftRightNoad*>(q), style, maxd, maxh);
				break;
			case style_node:
				curstyle = q->getSubtype();
				setCurSize(curstyle);
				replaceNode(q, q->link);
				continue;
			case whatsit_node:
			case penalty_node:
			case rule_node:
			case disc_node:
			case adjust_node:
			case ins_node:
			case mark_node:
			case glue_node:
			case kern_node:
				appendAtEnd(p, q); // p -> q
				next(q); // p-> ? -> q
				delete p->link;
				p->link = nullptr; 
				continue;
			default: 
				confusion("mlist3");
		}
		if (prevType > 0)
		{
			constexpr char math_spacing[] = "0234000122*4000133**3**344*0400400*000000234000111*1111112341011";
			halfword x = 0;
			switch (math_spacing[(prevType-ord_noad)*8+t-ord_noad])
			{
				case '0': 
					break;
				case '1': 
					x = curstyle < script_style ? thin_mu_skip_code : 0;
					break;
				case '2': 
					x = thin_mu_skip_code;
					break;
				case '3': 
					x = curstyle < script_style ? med_mu_skip_code : 0;
					break;
				case '4': 
					x = curstyle < script_style ? thick_mu_skip_code : 0;
					break;
				default: 
					confusion("mlist4");
			}
			if (x)
			{
				auto g = new GlueSpec(mathglue(glue_par(x), curmu));
				g->glue_ref_count = 0;
				auto z = new GlueNode(g);
				z->subtype = x+1;
				p->link = z;
				next(p);
			}
		}
		if (auto H = new_hlist(dynamic_cast<Noad*>(q)); H)
			followUntilEnd(H, p);
		if (penalties && q->link && pen < inf_penalty)
		{
			prevType = q->link->type;
			if (prevType != penalty_node && prevType != rel_noad)
				appendAtEnd(p, new PenaltyNode(pen));
		}
		prevType = t;
	}
}

Noad* finmlist(Noad *p)
{
	static Noad *q;
	if (incompleat_noad) 
	{
		incompleat_noad->denominator.math_type = sub_mlist;
		incompleat_noad->denominator.info = head->link;
		if (p == nullptr)
			q = incompleat_noad;
		else
		{
			q = dynamic_cast<Noad*>(incompleat_noad->numerator.info);
			if (q->type != left_noad)
				confusion("right");
			incompleat_noad->numerator.info = q->link;
			q->link = incompleat_noad;
			incompleat_noad->link = p;
		}
	}
	else
	{
		tail->link = p;
		q = dynamic_cast<Noad*>(head->link);
	}
	popnest();
	return q;
}
