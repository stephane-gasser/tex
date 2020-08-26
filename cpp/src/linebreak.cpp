#include "linebreak.h"
#include "noeud.h"
#include "deleteglueref.h"
#include "popnest.h"
#include "cesure.h"
#include "trybreak.h"
#include "erreur.h"
#include "police.h"
#include "postlinebreak.h"

static GlueSpec *finiteshrink(GlueSpec *p)
{
	if (noshrinkerroryet)
		error("Infinite glue shrinkage found in a paragraph", "The paragraph just ended includes some glue that has\ninfinite shrinkability, e.g., `\\hskip 0pt minus 1fil'.\nSuch glue doesn't belong there---it allows a paragraph\nof any length to fit on one line. But it's safe to proceed,\nsince the offensive shrinkability has been made finite.");
	noshrinkerroryet = false;
	auto q = new GlueSpec(p);
	q->shrink_order = normal;
	deleteglueref(p);
	return q;
}

static GlueSpec *check_shrinkage(GlueSpec *p)
{
	if (p->shrink_order != normal && p->shrink)
		p = finiteshrink(p);
	return p;
}

static void kern_break(bool autobreaking)
{
	if (!curp->link->is_char_node() && autobreaking && curp->link->type == glue_node)
		trybreak(0, unhyphenated);
	act_width += width(curp->num);
}

static void store_background(void)
{
	for (int i = 1; i <= 6; i++)
		activewidth[i] = background[i];
}

static int emergency_stretch(void) { return dimen_par(emergency_stretch_code); }
static int hyphen_penalty(void) { return int_par(hyphen_penalty_code); }
static int pretolerance(void) { return int_par(pretolerance_code); }
static int uc_hyph(void) { return int_par(uc_hyph_code); }

void linebreak(int finalwidowpenalty)
{
	bool autobreaking;
//	halfword s, prevs;
//	internalfontnumber f;
	smallnumber j;
	unsigned char c;
	packbeginline = mode_line;
	temp_head->link = head->link;
	if (tail->is_char_node() || tail->type != glue_node)
		tail_append(new PenaltyNode(inf_penalty));
	else 
	{
		auto Tail = dynamic_cast<GlueNode*>(tail);
		deleteglueref(Tail->glue_ptr);
		flushnodelist(Tail->leader_ptr);
		// delete tail ?
		tail->type = penalty_node;
		dynamic_cast<PenaltyNode*>(tail)->penalty = inf_penalty;
	}
	tail->link = new GlueNode(par_fill_skip_code);
	initcurlang = prev_graf%(1<<16);
	initlhyf = prev_graf>>22;
	initrhyf = (prev_graf>>16)%(1<<6);
	popnest();
	noshrinkerroryet = true;
	left_skip = check_shrinkage(left_skip);
	right_skip = check_shrinkage(right_skip);
	auto q = left_skip;
	auto r = right_skip;
	background[1] = q->width+r->width;
	background[2] = 0;
	background[3] = 0;
	background[4] = 0;
	background[5] = 0;
	background[2+q->stretch_order] = q->stretch;
	background[2+r->stretch_order] += r->stretch;
	background[6] = q->shrink+r->shrink;
	minimumdemerits = max_dimen;
	minimaldemerits[3] = max_dimen;
	minimaldemerits[2] = max_dimen;
	minimaldemerits[1] = max_dimen;
	minimaldemerits[0] = max_dimen;
	if (par_shape_ptr() == 0)
		if (hang_indent() == 0)
		{
			lastspecialline = 0;
			secondwidth = hsize();
			secondindent = 0;
		}
		else
		{
			lastspecialline = abs(hang_after());
			if (hang_after() < 0)
			{
				firstwidth = hsize()-abs(hang_indent());
				if (hang_indent() >= 0)
					firstindent = hang_indent();
				else
					firstindent = 0;
				secondwidth = hsize();
				secondindent = 0;
			}
			else
			{
				firstwidth = hsize();
				firstindent = 0;
				secondwidth = hsize()-abs(hang_indent());
				if (hang_indent() >= 0)
					secondindent = hang_indent();
				else
					secondindent = 0;
			}
		}
	else
	{
		lastspecialline = info(par_shape_ptr())-1;
		secondwidth = mem[par_shape_ptr()+2*(lastspecialline+1)].int_;
		secondindent = mem[par_shape_ptr()+2*lastspecialline+1].int_;
	}
	if (looseness() == 0)
		easyline = lastspecialline;
	else
		easyline = empty_flag;
	threshold = pretolerance();
	if (threshold >= 0)
	{
		secondpass = false;
		finalpass = false;
	}
	else
	{
		threshold = tolerance();
		secondpass = true;
		finalpass = emergency_stretch() <= 0;
	}
	while (true)
	{
		if (threshold > 10000)
			threshold = 10000;
		if (secondpass)
		{
			if (trienotready)
				inittrie();
			curlang = initcurlang;
			lhyf = initlhyf;
			rhyf = initrhyf;
		}
		LinkedNode *q;
		q->num = getnode(active_node_size);
		q->type = unhyphenated;
		fitness(q->num) = decent_fit;
		q->link = active;
		break_node(q->num) = 0;
		line_number(q->num) = prev_graf+1;
		total_demerits(q->num) = 0;
		active->link = q;
		store_background();
		passive = 0;
		printednode = temp_head->num;
		passnumber = 0;
		fontinshortdisplay = fonts[null_font];
		curp = temp_head->link;
		autobreaking = true;
		auto prevp = curp;
		while (curp && active->link != active)
		{
			if (curp->is_char_node())
			{
				prevp = curp;
				auto Curp = dynamic_cast<CharNode*>(curp);
				do
				{
					auto ft = Curp->font;
					act_width += ft.char_width(Curp->character);
					curp = curp->link;
				} while (curp->is_char_node());
			}
			switch (curp->type)
			{
				case hlist_node:
				case vlist_node:
				case rule_node: 
					act_width += width(curp->num);
					break;
				case whatsit_node:
					if (dynamic_cast<WhatsitNode*>(curp)->subtype == language_node)
					{
						auto Curp = dynamic_cast<LanguageWhatsitNode*>(curp);
						curlang = Curp->what_lang;
						lhyf = Curp->what_lhm;
						rhyf = Curp->what_rhm;
					}
					break;
				case glue_node:
				{
					if (autobreaking)
						if (prevp->is_char_node())
							trybreak(0, unhyphenated);
						else 
							if (precedes_break(prevp->num))
								trybreak(0, unhyphenated);
							else 
								if (prevp->type == kern_node && dynamic_cast<KernNode*>(prevp)->subtype != explicit_)
									trybreak(0, unhyphenated);
					auto Q = dynamic_cast<GlueNode*>(curp)->glue_ptr;
					Q = check_shrinkage(Q);
					act_width += Q->width;
					activewidth[2+Q->stretch_order] += Q->stretch;
					activewidth[6] += Q->shrink;
					if (secondpass && autobreaking)
					{
						auto prevs = curp;
						auto s = prevs->link;
						if (s)
						{
							bool label31 = false;
							while (true)
							{
								if (s->is_char_node())
								{
									auto S = dynamic_cast<CharNode*>(s);
									c = S->character;
									fonts[hf] = S->font;
								}
								else 
									if (s->type == ligature_node)
										if (dynamic_cast<LigatureNode*>(s)->lig_ptr == nullptr)
										{
											prevs = s;
											s = prevs->link;
											continue;
										}
										else
										{
											q = dynamic_cast<LigatureNode*>(s)->lig_ptr;
											c = dynamic_cast<CharNode*>(q)->character;
											fonts[hf] = dynamic_cast<CharNode*>(q)->font;
										}
									else 
										if (s->type == kern_node && dynamic_cast<KernNode*>(s)->subtype == normal)
										{
											prevs = s;
											s = prevs->link;
											continue;
										}
										else 
											if (s->type == whatsit_node)
											{
												if (dynamic_cast<WhatsitNode*>(s)->subtype == language_node)
												{
													auto S = dynamic_cast<LanguageWhatsitNode*>(s);
													curlang = S->what_lang;
													lhyf = S->what_lhm;
													rhyf = S->what_rhm;
												}
												prevs = s;
												s = prevs->link;
												continue;
											}
											else
											{
												label31 = true;
												break;
											}
								if (lc_code(c))
									if (lc_code(c) == c && uc_hyph() > 0)
										break;
									else
									{
										label31 = true;
										break;
									}
								prevs = s;
								s = prevs->link;
							}
							while (!label31)
							{
								hyfchar = fonts[hf].hyphenchar;
								if (hyfchar < 0 || hyfchar > 255)
									break;
								ha = dynamic_cast<LigatureNode*>(prevs);
								if (lhyf+rhyf > 63)
									break;
								hn = 0;
								while (true)
								{
									if (s->is_char_node())
									{
										auto S = dynamic_cast<CharNode*>(s);
										if (S->font != fonts[hf])
											break;
										hyfbchar = S->character;
										c = hyfbchar;
										if (lc_code(c) == 0)
											break;
										if (hn == 63)
											break;
										hb = s;
										hn++;
										hu[hn] = c;
										hc[hn] = lc_code(c);
										hyfbchar = 256;
									}
									else 
										if (s->type == ligature_node)
										{
											auto S = dynamic_cast<LigatureNode*>(s);
											if (S->lig_char.font != fonts[hf])
												break;
											j = hn;
											q = S->lig_ptr;
											if (q)
												hyfbchar = dynamic_cast<CharNode*>(q)->character;
											while (q > 0)
											{
												c = dynamic_cast<CharNode*>(q)->character;
												if (lc_code(c) == 0)
													break;
												if (j == 63)
													break;
												j++;
												hu[j] = c;
												hc[j] = lc_code(c);
												q = q->link;
											}
											hb = s;
											hn = j;
											if (subtype(s->num)%2)
												hyfbchar = fonts[hf].bchar;
											else
												hyfbchar = 256;
										}
										else 
											if (s->type == kern_node && dynamic_cast<KernNode*>(s)->subtype == normal)
											{
												hb = s;
												hyfbchar = fonts[hf].bchar;
											}
											else
												break;
									s = s->link;
								}
								if (hn < lhyf+rhyf)
									break;
								bool label34 = true;
								while (label34)
								{
									if (!s->is_char_node())
										switch (s->type)
										{
											case ligature_node: 
												break;
											case kern_node: 
												if (dynamic_cast<KernNode*>(s)->subtype != normal)
												{
													label34 = false;
													continue;
												}
												break;
											case whatsit_node:
											case glue_node:
											case penalty_node:
											case ins_node:
											case adjust_node:
											case mark_node: 
												label34 = false;
												continue;
											default: 
												label31 = true;
												break;
										}
									s = s->link;
								}
								if (!label31)
									hyphenate();
								break;
							}
						}
					}
					break;
				}
				case kern_node: 
				{
					auto Curp = dynamic_cast<KernNode*>(curp);
					if (Curp->subtype == explicit_)
						kern_break(autobreaking);
					else
						act_width += Curp->width;
					break;
				}
				case ligature_node:
				{
					auto Curp = dynamic_cast<LigatureNode*>(curp);
					auto ft = Curp->lig_char.font;
					act_width += ft.char_width(Curp->lig_char.character);
					break;
				}
				case disc_node:
				{
					auto d = dynamic_cast<DiscNode*>(curp);
					auto s = d->pre_break;
					discwidth = 0;
					if (s == nullptr)
						trybreak(ex_hyphen_penalty(), hyphenated);
					else
					{
						do
						{
							if (s->is_char_node())
							{
								auto S = dynamic_cast<CharNode*>(s);
								auto ft = S->font;
								discwidth += ft.char_width(S->character);
							}
							else
								switch (s->type)
								{
									case ligature_node:
									{
										auto S = dynamic_cast<LigatureNode*>(s);
										auto ft = S->lig_char.font;
										discwidth += ft.char_width(S->lig_char.character);
										break;
									}
									case hlist_node:
									case vlist_node:
									case rule_node:
										discwidth += width(s->num);
										break;
									case kern_node: 
										discwidth += dynamic_cast<KernNode*>(s)->width;
										break;
									default: 
										confusion("disc3");
								}
							s = s->link;
						} while (s);
						act_width += discwidth;
						trybreak(hyphen_penalty(), 1);
						act_width -= discwidth;
					}
					auto r = d->replace_count;
					s = curp->link;
					while (r > 0)
					{
						if (s->is_char_node())
						{
							auto S = dynamic_cast<CharNode*>(s);
							auto ft = S->font;
							act_width += ft.char_width(S->character);
						}
						else
							switch (s->type)
							{
								case ligature_node:
								{
									auto S = dynamic_cast<LigatureNode*>(s);
									auto ft = S->lig_char.font;
									act_width += ft.char_width(S->lig_char.character);
									break;
								}
								case hlist_node:
								case vlist_node:
								case rule_node:
									act_width += dynamic_cast<RuleNode*>(s)->width;
									break;
								case kern_node: 
									act_width += dynamic_cast<KernNode*>(s)->width;
									break;
								default: 
									confusion("disc4");
							}
						r--;
						s = s->link;
					}
					prevp = curp;
					curp = s;
					continue;
				}
				case math_node:
					autobreaking = subtype(curp->num) == after;
					kern_break(autobreaking);
					break;
				case penalty_node: 
					trybreak(dynamic_cast<PenaltyNode*>(curp)->penalty, unhyphenated);
					break;
				case mark_node:
				case ins_node:
				case adjust_node:
					break;
				default: 
					confusion("paragraph");
			}
			prevp = curp;
			curp = curp->link;
		}
		if (curp == nullptr)
		{
			trybreak(eject_penalty, hyphenated);
			if (active->link != active)
			{
				auto r = active->link;
				fewestdemerits = max_dimen;
				do
				{
					if (r->type != rule_node && total_demerits(r->num) < fewestdemerits)
					{
						fewestdemerits = total_demerits(r->num);
						bestbet = r->num;
					}
					r = r->link;
				} while (r != active);
				bestline = line_number(bestbet);
				if (looseness() == 0)
				{
					postlinebreak(finalwidowpenalty);
					auto q = active->link;
					while (q != active)
					{
						curp = q->link;
						if (q->type == delta_node)
							freenode(q->num, delta_node_size);
						else
							freenode(q->num, active_node_size);
						q = curp;
					}
					q->num = passive;
					while (q)
					{
						curp = q->link;
						freenode(q->num, passive_node_size);
						q = curp;
					}
					packbeginline = 0;
					return;
				}
				r = active->link;
				actuallooseness = 0;
				do
				{
					if (r->type != 2)
					{
						linediff = line_number(r->num)-bestline;
						if ((linediff < actuallooseness && looseness() <= linediff) || (linediff > actuallooseness && looseness() >= linediff))
						{
							bestbet = r->num;
							actuallooseness = linediff;
							fewestdemerits = total_demerits(r->num);
						}
						else 
							if (linediff == actuallooseness && total_demerits(r->num) < fewestdemerits)
							{
								bestbet = r->num;
								fewestdemerits = total_demerits(r->num);
							}
					}
					r = r->link;
				} while (r != active);
				bestline = line_number(bestbet);
				if (actuallooseness == looseness() || finalpass)
				{
					postlinebreak(finalwidowpenalty);
					auto q = active->link;
					while (q != active)
					{
						curp = q->link;
						if (q->type == delta_node)
							freenode(q->num, delta_node_size);
						else
							freenode(q->num, active_node_size);
						q = curp;
					}
					q->num = passive;
					while (q)
					{
						curp = q->link;
						freenode(q->num, passive_node_size);
						q = curp;
					}
					packbeginline = 0;
					return;
				}
			}
		}
		q = active->link;
		while (q != active)
		{
			curp = q->link;
			if (q->type == delta_node)
				freenode(q->num, delta_node_size);
			else
				freenode(q->num, active_node_size);
			q = curp;
		}
		q->num = passive;
		while (q)
		{
			curp = q->link;
			freenode(q->num, passive_node_size);
			q = curp;
		}
		if (!secondpass)
		{
			threshold = tolerance();
			secondpass = true;
			finalpass = emergency_stretch() <= 0;
		}
		else
		{
			background[2] += emergency_stretch();
			finalpass = true;
		}
	}
	postlinebreak(finalwidowpenalty);
	auto qq = active->link;
	while (qq != active)
	{
		curp = qq->link;
		if (qq->type == delta_node)
			freenode(qq->num, delta_node_size);
		else
			freenode(qq->num, active_node_size);
		qq = curp;
	}
	qq->num = passive;
	while (qq)
	{
		curp = qq->link;
		freenode(qq->num, passive_node_size);
		qq = curp;
	}
	packbeginline = 0;
}
