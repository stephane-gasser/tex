#include "mainloop.h"
#include "noeud.h"
#include "police.h"
#include "cesure.h"
#include "equivalent.h"
#include "lecture.h"
#include "getnext.h"
#include "calcul.h"
#include "fixlanguage.h"
#include "charwarning.h"

static void adjust_space_factor(halfword chr)
{
	switch (int sf = sf_code(chr); sf <= 0 ? -1 : sf > 1000 ? 1 : 0)
	{
		case 0: // 0 < sf <= 1000
			space_factor = sf;
			break;
		case 1: // sf > 1000
			space_factor = space_factor < 1000 ? 1000 : sf;
	}
}

//static fourquarters mainj; //!<ligature/kern command
//static fourquarters maini; //!<character information bytes for |cur_l|
static fontindex maink; //!< index into |font_info|

//! the parameter is either |rt_hit| or |false|
static void pack_lig(bool z)
{
	auto l = new LigatureNode(curFontNum(), curl, curq->link);
	if (lfthit)
	{
		l->subtype = 2; //implicit left boundary
		lfthit = false;
	}
	if (z && ligstack == nullptr)
	{
		l->subtype++; //implicit right boundary
		rthit = false;
	}
	curq->link = l;
	tail = l;
	ligaturepresent = false;
}

static bool insdisc = false;

static void wrapup(bool z)
{
	if (curl < non_char)
	{
		if (curq->link > 0 && dynamic_cast<CharNode*>(tail)->character == cur_font().hyphenchar) 
			insdisc = true; 
		if (ligaturepresent)
			pack_lig(z); 
		if (insdisc)
		{
			insdisc = false;
			if (mode > 0)
				tail_append(new DiscNode); 
		}
	}
}

static halfword falsebchar;

static void main_loop_lookahead(void)
{
	auto t = getnext();
	if (t.cmd != letter && t.cmd != other_char && t.cmd != char_given)
	{
		t = xtoken(t);
		if (t.cmd != letter && t.cmd != other_char && t.cmd != char_given)
		{
			if (t.cmd == char_num)
				t.chr = scancharnum();
			else
			{
				if (t.cmd == no_boundary)
					bchar = non_char;
				curr = bchar;
				ligstack = nullptr;
				return;
			}
		}
	}
	//main_loop_lookahead_1
	adjust_space_factor(t.chr);
	curr = t.chr;
	ligstack = new LigatureNode(curFontNum(), curr, nullptr);
	if (curr == falsebchar)
		curr = non_char;
}

static void main_loop_move_lig(void)
{
	auto l = dynamic_cast<LigatureNode*>(ligstack->lig_ptr);
	if (l)
		tail_append(l);
	auto temp = ligstack;
	next(ligstack);
	delete temp;
	ligaturepresent = true;
	if (ligstack == nullptr)
		if (l)
			main_loop_lookahead();
		else
			curr = bchar;
	else
		curr = ligstack->lig_char.character;
}

static bool main_loop_move_2(halfword chr)
{
	if (cur_font().bc <= chr && chr <= cur_font().ec)
	{
		if (cur_font().char_exists(curl))
		{
			tail_append(ligstack);
			main_loop_lookahead();
			return false;
		}
	}
	charwarning(cur_font(), chr);
	delete ligstack;
	ligstack = nullptr;
	return true;
}

static bool main_loop_move_1(halfword chr)
{

	if (!ligstack->is_char_node())
		main_loop_move_lig();
	else
		if (main_loop_move_2(chr))
			return true;
	return false;
}

static bool main_loop_move(halfword chr)
{
	if (ligstack == nullptr)
		return true;
	curq = dynamic_cast<CharNode*>(tail);
	curl = ligstack->lig_char.character;
	return main_loop_move_1(chr);
}

static bool main_loop_wrapup(halfword chr)
{
	wrapup(rthit);
	return main_loop_move(chr);
}

[[nodiscard]] static Token main_lig_loop(bool is110, halfword chr)
{
	while (true)
	{
		if (is110)
		{
			if (cur_font().char_tag(curl) != lig_tag || curr == non_char)
			{
				if (main_loop_wrapup(chr))
					return getxtoken();
				continue;
			}
			maink = cur_font().lig_kern_start(cur_font().char_info(curl));
			if (Font::skip_byte(maink) > stop_flag)
				maink = cur_font().lig_kern_restart(Font::infos(maink));
		}
		//main_lig_loop+2
		if (Font::next_char(maink) == curr)
			if (Font::skip_byte(maink) <= stop_flag)
			{
				if (Font::op_byte(maink) >= kern_flag) // c'est un kern
				{
					if (curl < non_char)
					{
						if (curq->link && dynamic_cast<CharNode*>(tail)->character == cur_font().hyphenchar)
							insdisc = true;
						if (ligaturepresent)
							pack_lig(rthit);
						if (insdisc)
						{
							insdisc = false;
							if (mode > 0)
								tail_append(new DiscNode);
						}
					}
					tail_append(new KernNode(cur_font().char_kern(Font::infos(maink))));
					if (main_loop_move(chr))
						return getxtoken();
					is110 = true;
					continue;
				}
				// Font::op_byte(maink) < kern_flag => c'est une ligature
				if (curl == non_char)
					lfthit = true;
				else 
					if (ligstack == nullptr)
						rthit = true;
				switch (Font::op_byte(maink))
				{
					// AB -> CB (symboles =:| et =:|>)
					case 1: //a=0 b=0 c=1 => delete current char
					case 5: //a=1 b=0 c=1 => idem
						curl = Font::rem_byte(maink);
						ligaturepresent = true;
						break;
					// AB -> AC (symboles |=: et |=:>)
					case 2: //a=0 b=1 c=0 => delete next char
					case 6: //a=1 b=1 c=0 => delete next char
						curr = Font::rem_byte(maink);
						if (ligstack == nullptr)
						{
							ligstack = new LigatureNode(curr);
							bchar = non_char;
						}
						else 
							if (ligstack->is_char_node())
							{
								auto l = ligstack;
								ligstack = new LigatureNode(curr);
								ligstack->lig_ptr = l;
							}
							else
								ligstack->lig_char.character = curr;
						break;
					// AB -> ACB (symbole |=:|)
					case 3: //a=0 b=1 c=1
					{
						curr = Font::rem_byte(maink);
						appendAtStart(ligstack, new LigatureNode(curr));
						break;
					}
					// AB -> ACB (symboles |=:|> et |=:|>>)
					case 7: //a=1 b=1 c=1
					case 11://a=2 b=1 c=1
						wrapup(false);
						curq = dynamic_cast<CharNode*>(tail);
						curl = Font::rem_byte(maink);
						ligaturepresent = true;
						break;
					// AB -> C (symbole !=)
					default:
						curl = Font::rem_byte(maink);
						ligaturepresent = true;
						if (ligstack == nullptr)
						{
							if (main_loop_wrapup(chr))
								return getxtoken();
						}
						else
							if (main_loop_move_1(chr))
								return getxtoken();
				}
				if (Font::op_byte(maink) > 4 && Font::op_byte(maink) != 7) // a>=1 et pas a=1,b=1,c=1
				{
					if (main_loop_wrapup(chr))
						return getxtoken();
					is110 = true;
					continue;
				}
				if (curl < non_char)
				{
					is110 = true;
					continue;
				}
				maink = cur_font().bcharlabel;
				is110 = false;
				continue;
			}
		if (Font::skip_byte(maink) == 0)
			maink++;
		else
		{
			if (Font::skip_byte(maink) >= stop_flag)
			{
				if (main_loop_wrapup(chr))
					return getxtoken();
				is110 = true;
				continue;
			}
			maink += Font::skip_byte(maink)+1;
		}
		is110 = false;
	}
}

void main_loop(Token t)
{
	adjust_space_factor(t.chr);
	bchar = cur_font().bchar;
	falsebchar = cur_font().falsebchar;
	if (mode > 0 && language() != clang)
		fixlanguage();
	curl = t.chr;
	ligstack = new LigatureNode(curFontNum(), curl, nullptr);
	curq = dynamic_cast<CharNode*>(tail);
	maink = cancelboundary ? non_address : cur_font().bcharlabel;
	cancelboundary = false;
	if (maink == non_address)
		if (main_loop_move_2(t.chr))
		{
			t = getxtoken();
			curr = curl;
			curl = non_char;
			t = main_lig_loop(false, t.chr);
		}
		else
			t = main_lig_loop(true, t.chr);
}

[[nodiscard]] Token append_normal_space(void)
{
	if (space_skip() == zero_glue)
	{
		auto g = cur_font().glue;
		if (g == nullptr)
		{
			g = new GlueSpec(zero_glue);
			maink = cur_font().parambase+space_code;
			g->width = cur_font().space();
			g->stretch = cur_font().space_stretch();
			g->shrink = cur_font().space_shrink();
			cur_font().glue = g;
		}
		tail_append(new GlueNode(g));
	}
	else
		tail_append(new GlueNode(space_skip()));
	return getxtoken();
}

//! Handle spaces when <em> space_factor != 1000 </em>.
void appspace(void)
{
	if (space_factor >= 2000 && xspace_skip() != zero_glue)
	{
		tail_append(new GlueNode(xspace_skip()));
		return;
	}
	GlueSpec *g;
	if (space_skip() != zero_glue)
		g = space_skip();
	else // Find the glue specification, \a main_p, for text spaces in the current font
	{
		g = cur_font().glue;
		if (g == nullptr)
		{
			g = new GlueSpec(zero_glue);
			maink = space_code+cur_font().parambase;
			g->width = cur_font().space();
			g->stretch = cur_font().space_stretch();
			g->shrink = cur_font().space_shrink();
			cur_font().glue = g;
		}
	}
	g = new GlueSpec(g);
	// Modify the glue specification in \a main_p according to the space factor
	if (space_factor >= 2000)
		g->width += cur_font().extra_space();
	g->stretch = xnoverd(g->stretch, space_factor, 1000);
	g->shrink = xnoverd(g->shrink, 1000, space_factor);
	tail_append(new GlueNode(g));
	g->glue_ref_count = 0;
}
