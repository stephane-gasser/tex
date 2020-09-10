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
static halfword curl, curr; //!< characters before and after the cursor
static bool lfthit = false, rthit = false; //!< did we hit a ligature with a boundary character?
static LinkedNode *curq; //!< where a ligature should be detached

//! the parameter is either |rt_hit| or |false|
static void wrapup(bool z)
{
	if (curl < non_char)
	{
		bool insdisc = curq->link && dynamic_cast<LigatureNode*>(tail)->character == cur_font().hyphenchar;
		if (ligaturepresent)
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
		if (insdisc && mode > 0)
			tail_append(new DiscNode); 
	}
}

enum 
{
	lookahead,
	move_lig,
	move,
	move_1,
	move_2,
	wrap_up,
	init_main,
	main_2,
};

static halfword falsebchar;

static void next(fontindex &maink, int &cycle)
{
	if (cycle == main_2)
		if (Font::skip_byte(maink) >= stop_flag)
			cycle = wrap_up;
		else
			maink += Font::skip_byte(maink)+1;
}

static bool programMatches(fontindex maink, halfword curr) { return Font::next_char(maink) == curr && Font::skip_byte(maink) <= stop_flag; }

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
	int cycle = move_2;  //no left boundary processing
	if (maink != non_address)
	{
		curr = curl;
		curl = non_char;
		cycle = main_2; //begin with cursor after left boundary
	}
	while (true)
		try
		{
			switch (cycle)
			{
				case init_main: //! If there's a ligature/kern command relevant to |cur_l| and |cur_r|, adjust the text appropriately; exit to |main_loop_wrapup|
					if (cur_font().char_tag(curl) != lig_tag || curr == non_char)
					{
						cycle = wrap_up;
						continue;
					}
					maink = cur_font().lig_kern_first(curl); [[fallthrough]];
				case main_2:
					// boucle sur les programmes
					for (; cycle == main_2; next(maink, cycle))
						if (programMatches(maink, curr)) //Do ligature or kern command, returning to |main_lig_loop| or |main_loop_wrapup| or |main_loop_move|
						{
							if (Font::op_byte(maink) >= kern_flag) // c'est un kern
							{
								wrapup(rthit);
								tail_append(new KernNode(cur_font().char_kern(maink)));
								cycle = init_main;
								continue;
							}
							if (curl == non_char)
								lfthit = true; //implicit left boundary
							else 
								if (ligstack == nullptr)
									rthit = true; //implicit right boundary
							switch (Font::op_byte(maink))
							{
								// AB -> CB (symboles =:| et =:|>)
								case 1: //a=0 b=0 c=1 => delete current char
								case 5: //a=1 b=0 c=1 => delete current char and shift right once
									curl = Font::rem_byte(maink);
									ligaturepresent = true;
									break;
								// AB -> AC (symboles |=: et |=:>)
								case 2: //a=0 b=1 c=0 => delete next char
								case 6: //a=1 b=1 c=0 => delete next char and shift right once
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
											ligstack->character = curr;
									break;
								// AB -> ACB (symbole |=:|)
								case 3: //a=0 b=1 c=1 
								{
									curr = Font::rem_byte(maink);
									appendAtStart(ligstack, new LigatureNode(curr));
									break;
								}
								// AB -> ACB (symboles |=:|> et |=:|>>)
								case 7: //a=1 b=1 c=1 shift right once
								case 11://a=2 b=1 c=1 shift right twice
									wrapup(false);
									curq = tail;
									curl = Font::rem_byte(maink);
									ligaturepresent = true;
									break;
								// AB -> C (symbole !=)
								default: //a=0 b=0 c=0 delete both chars
									curl = Font::rem_byte(maink);
									ligaturepresent = true;
									cycle = ligstack == nullptr ? wrap_up : move_1;
									continue;
							}
							if (Font::op_byte(maink) > 4 && Font::op_byte(maink) != 7) // a>=1 et pas a=1,b=1,c=1
							{
								cycle = wrap_up;
								continue;
							}
							if (curl < non_char)
							{
								cycle = init_main;
								continue;
							}
							maink = cur_font().bcharlabel;
						}
					break;
				case wrap_up: //! Make a ligature node, if |ligature_present|; insert a null discretionary, if appropriate
					wrapup(rthit); [[fallthrough]];
				case move: //! If the cursor is immediately followed by the right boundary,|goto reswitch|; 
					if (ligstack == nullptr)
						return; // reswitch
					curq = tail;
					curl = ligstack->character; [[fallthrough]];
				case move_1:
					if (!ligstack->is_char_node())
					{
						cycle = move_lig;
						continue;
					} [[fallthrough]];
				case move_2: //if it's followed by an invalid character, |goto big_switch|; 
					if (cur_font().bc > t.chr || t.chr > cur_font().ec || !cur_font().char_exists(curl)) // invalid character
						throw;
					//!  otherwise move the cursor one step to the right and |goto main_lig_loop|
					tail_append(ligstack); [[fallthrough]];
				case lookahead: //! Look ahead for another character, or leave |lig_stack| empty if there's none there
					t = getnext();
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
								bchar = non_char; [[fallthrough]];
							default:
								curr = bchar;
								ligstack = nullptr;
						}
					}
					if (t.cmd == letter || t.cmd == other_char || t.cmd == char_given || t.cmd == char_num)
					{
						adjust_space_factor(t.chr);
						curr = t.chr;
						ligstack = new LigatureNode(curFontNum(), curr, nullptr);
						if (curr == falsebchar)
							curr = non_char; // this prevents spurious ligatures
					}
					cycle = init_main;
					break;
				case move_lig: //! Move the cursor past a pseudo-ligature, then |goto main_loop_lookahead| or |main_lig_loop|
				{
					auto l = ligstack->lig_ptr;
					if (ligstack->lig_ptr)
						tail_append(ligstack->lig_ptr); // append a single character
					auto temp = ligstack;
					next(ligstack);
					delete temp;
					ligaturepresent = true;
					if (ligstack == nullptr && l)
					{
						cycle = lookahead;
						continue;
					}
					curr = ligstack == nullptr ? bchar : ligstack->character;
					cycle = init_main;
				}
			}
		}
		catch (...)
		{
			charwarning(cur_font(), t.chr);
			delete ligstack;
			ligstack = nullptr;
			t = getxtoken(); // big_switch
			return;
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
