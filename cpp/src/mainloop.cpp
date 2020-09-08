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


static void wrapup(bool z)
{
	if (curl < non_char)
	{
		bool insdisc = curq->link && dynamic_cast<CharNode*>(tail)->character == cur_font().hyphenchar;
		if (ligaturepresent)
			pack_lig(z); 
		if (insdisc && mode > 0)
			tail_append(new DiscNode); 
	}
}

static halfword falsebchar;

enum 
{
	lookahead,
	move_lig,
	move_2,
	move_1,
	move,
	wrap_up,
	main,
	main_2,
	big_switch,
	reswitch
};

//! Make a ligature node, if |ligature_present|; insert a null discretionary, if appropriate
static int main_loop_wrapup(void) //1035
{
	wrapup(rthit);
	return move; //main_loop_move(chr);
}

//! If the cursor is immediately followed by the right boundary,  |goto reswitch|; if it's followed by an invalid character, |goto big_switch|;
//!  otherwise move the cursor one step to the right and |goto main_lig_loop|
static int main_loop_move(void) //1036
{
	if (ligstack == nullptr)
		return reswitch;
	curq = tail;
	curl = ligstack->lig_char.character;
	return move_1; //main_loop_move_1(chr);
}

static int main_loop_move_1(void)
{

	if (!ligstack->is_char_node())
		return move_lig; //main_loop_move_lig(chr);
	return move_2; //main_loop_move_2(chr);
}

static int main_loop_move_2(Token &t)
{
	if (cur_font().bc > t.chr || t.chr > cur_font().ec || !cur_font().char_exists(curl))
	{
		charwarning(cur_font(), t.chr);
		delete ligstack;
		ligstack = nullptr;
		return big_switch; // invalid character
	}
	tail_append(ligstack);
	return lookahead; //main_loop_lookahead();
}

//! Look ahead for another character, or leave |lig_stack| empty if there's none there
static int main_loop_lookahead(Token &t) //1038
{
	t = getnext();
	bool ahead = true;
	if (t.cmd != letter && t.cmd != other_char && t.cmd != char_given)
	{
		t = xtoken(t);
		switch (t.cmd)
		{
			case char_num:
				t.chr = scancharnum();
				break;
			case letter:
			case other_char:
			case char_given:
				break;
			case no_boundary:
				bchar = non_char;
				[[fallthrough]];
			default:
				curr = bchar;
				ligstack = nullptr;
				ahead = false;
		}
	}
	if (ahead)
	{
		adjust_space_factor(t.chr);
		curr = t.chr;
		ligstack = new LigatureNode(curFontNum(), curr, nullptr);
		if (curr == falsebchar)
			curr = non_char; // this prevents spurious ligatures
	}
	return main;// main_lig_loop(true, t.chr);
}

//! If there's a ligature/kern command relevant to |cur_l| and |cur_r|, adjust the text appropriately; exit to |main_loop_wrapup|
static int main_lig_loop(void) //1039
{
	if (cur_font().char_tag(curl) != lig_tag || curr == non_char)
		return wrap_up; //main_loop_wrapup(chr);
	maink = cur_font().lig_kern_start(cur_font().char_info(curl));
	if (Font::skip_byte(maink) > stop_flag)
		maink = cur_font().lig_kern_restart(Font::infos(maink));
	return main_2;
}

static int main_lig_loop_2(void) //1039
{
	if (Font::next_char(maink) == curr && Font::skip_byte(maink) <= stop_flag)
	{	// 1040
		//Do ligature or kern command, returning to |main_lig_loop| or |main_loop_wrapup| or |main_loop_move|
		if (Font::op_byte(maink) >= kern_flag) // c'est un kern
		{
			wrapup(rthit);
			tail_append(new KernNode(cur_font().char_kern(Font::infos(maink))));
			return main;
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
				curq = tail;
				curl = Font::rem_byte(maink);
				ligaturepresent = true;
				break;
			// AB -> C (symbole !=)
			default:
				curl = Font::rem_byte(maink);
				ligaturepresent = true;
				if (ligstack == nullptr)
					return wrap_up; //main_loop_wrapup(chr);
				return move_1; //main_loop_move_1(chr);
		}
		if (Font::op_byte(maink) > 4 && Font::op_byte(maink) != 7) // a>=1 et pas a=1,b=1,c=1
			return wrap_up; //main_loop_wrapup(chr);
		if (curl < non_char)
			return main;
		maink = cur_font().bcharlabel;
		return main_2;
	}
	if (Font::skip_byte(maink) >= stop_flag)
		return wrap_up; //main_loop_wrapup(chr);
	maink += Font::skip_byte(maink)+1;
	return main_2;
}

//! Move the cursor past a pseudo-ligature, then |goto main_loop_lookahead| or |main_lig_loop|
static int main_loop_move_lig(void) // 1037
{
	auto l = ligstack->lig_ptr;
	if (l)
		tail_append(l); // append a single character
	auto temp = ligstack;
	next(ligstack);
	delete temp;
	ligaturepresent = true;
	if (ligstack == nullptr)
		if (l)
			return lookahead; //main_loop_lookahead();
		else
			curr = bchar;
	else
		curr = ligstack->lig_char.character;
	return main; //main_lig_loop(true, chr);
}

//! Append character |cur_chr| and the following characters (if~any) to the current hlist in the current font; |goto reswitch| when a non-character has been fetched
void main_loop(Token &t) //t: char_num / letter / other_char / char_given
{
	adjust_space_factor(t.chr);
	bchar = cur_font().bchar;
	falsebchar = cur_font().falsebchar;
	if (mode > 0 && language() != clang)
		fixlanguage();
	curl = t.chr;
	ligstack = new LigatureNode(curFontNum(), curl, nullptr);
	curq = tail;
	maink = cancelboundary ? non_address : cur_font().bcharlabel;
	cancelboundary = false;
	int cycle;
	if (maink == non_address) 
		cycle = move_2; //no left boundary processing
	else
	{
		curr = curl;
		curl = non_char;
		cycle = main_2; //begin with cursor after left boundary
	}
	while (cycle != reswitch)
		switch (cycle)
		{
			case wrap_up:
				cycle = main_loop_wrapup();
				break;
			case move:
				cycle = main_loop_move();
				break;
			case move_1:
				cycle = main_loop_move_1();
				break;
			case move_2:
				cycle = main_loop_move_2(t);
				break;
			case lookahead:
				cycle = main_loop_lookahead(t);
				break;
			case move_lig:
				cycle = main_loop_move_lig();
				break;
			case main:
				cycle = main_lig_loop();
				break;
			case main_2:
				cycle = main_lig_loop_2();
				break;
			case big_switch:
				t = getxtoken();
				cycle = reswitch;
		}
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
