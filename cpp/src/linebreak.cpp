#include "linebreak.h"
#include "noeud.h"
#include "deleteglueref.h"
#include "flushnodelist.h"
#include "popnest.h"
#include "finiteshrink.h"
#include "inittrie.h"
#include "getnode.h"
#include "trybreak.h"
#include "hyphenate.h"
#include "erreur.h"
#include "postlinebreak.h"
#include "freenode.h"

static void check_shrinkage(halfword &p)
{
	if (shrink_order(p) != normal && shrink(p))
		p = finiteshrink(p);
}

static void kern_break(bool autobreaking)
{
	if (!is_char_node(link(curp)) && autobreaking && type(link(curp)) == glue_node)
		trybreak(0, unhyphenated);
	act_width += width(curp);
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
	halfword prevp, q, r, s, prevs;
	internalfontnumber f;
	smallnumber j;
	unsigned char c;
	packbeginline = mode_line;
	link(temp_head) = link(head);
	if ((tail >= himemmin))
		tail_append(newpenalty(inf_penalty));
	else 
		if (type(tail) != glue_node)
			tail_append(newpenalty(inf_penalty));
		else
		{
			type(tail) = penalty_node;
			deleteglueref(glue_ptr(tail));
			flushnodelist(leader_ptr(tail));
			penalty(tail) = inf_penalty;
		}
	link(tail) = newparamglue(par_fill_skip_code);
	initcurlang = prev_graf%0x1'00'00;
	initlhyf = prev_graf>>22;
	initrhyf = (prev_graf>>16)%0x40;
	popnest();
	noshrinkerroryet = true;
	check_shrinkage(left_skip());
	check_shrinkage(right_skip());
	q = left_skip();
	r = right_skip();
	background[1] = width(q)+width(r);
	background[2] = 0;
	background[3] = 0;
	background[4] = 0;
	background[5] = 0;
	background[2+stretch_order(q)] = stretch(q);
	background[2+stretch_order(r)] += stretch(r);
	background[6] = shrink(q)+shrink(r);
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
		q = getnode(active_node_size);
		type(q) = unhyphenated;
		fitness(q) = decent_fit;
		link(q) = active;
		break_node(q) = 0;
		line_number(q) = prev_graf+1;
		total_demerits(q) = 0;
		link(active) = q;
		store_background();
		passive = 0;
		printednode = temp_head;
		passnumber = 0;
		fontinshortdisplay = null_font;
		curp = link(temp_head);
		autobreaking = true;
		prevp = curp;
		while (curp && link(active) != active)
		{
			if ((curp >= himemmin))
			{
				prevp = curp;
				do
				{
					f = type(curp);
					act_width += char_width(f, char_info(f, character(curp)));
					curp = link(curp);
				} while (curp >= himemmin);
			}
			switch (type(curp))
			{
				case hlist_node:
				case vlist_node:
				case rule_node: 
					act_width += width(curp);
					break;
				case whatsit_node:
					if (subtype(curp) == 4)
					{
						curlang = link(curp+1);
						lhyf = type(curp+1);
						rhyf = subtype(curp+1);
					}
					break;
				case glue_node:
					if (autobreaking)
						if (is_char_node(prevp))
							trybreak(0, unhyphenated);
						else 
							if (precedes_break(prevp))
								trybreak(0, unhyphenated);
							else 
								if (type(prevp) == kern_node && subtype(prevp) != explicit_)
									trybreak(0, unhyphenated);
					check_shrinkage(glue_ptr(curp));
					q = glue_ptr(curp);
					act_width += width(q);
					activewidth[2+stretch_order(q)] += stretch(q);
					activewidth[6] += shrink(q);
					if (secondpass && autobreaking)
					{
						prevs = curp;
						s = link(prevs);
						if (s)
						{
							bool label31 = false;
							while (true)
							{
								if (s >= himemmin)
								{
									c = subtype(s);
									hf = type(s);
								}
								else 
									if (type(s) == 6)
										if (link(s+1) == 0)
										{
											prevs = s;
											s = link(prevs);
											continue;
										}
										else
										{
											q = link(s+1);
											c = subtype(q);
											hf = type(q);
										}
									else 
										if (type(s) == 11 && subtype(s) == 0)
										{
											prevs = s;
											s = link(prevs);
											continue;
										}
										else 
											if (type(s) == 8)
											{
												if (subtype(s) == 4)
												{
													curlang = link(s+1);
													lhyf = type(s+1);
													rhyf = subtype(s+1);
												}
												prevs = s;
												s = link(prevs);
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
								s = link(prevs);
							}
							while (!label31)
							{
								hyfchar = hyphenchar[hf];
								if (hyfchar < 0)
									break;
								if (hyfchar > 255)
									break;
								ha = prevs;
								if (lhyf+rhyf > 63)
									break;
								hn = 0;
								while (true)
								{
									if (s >= himemmin)
									{
										if (type(s) != hf)
											break;
										hyfbchar = subtype(s);
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
										if (type(s) == 6)
										{
											if (type(s+1) != hf)
												break;
											j = hn;
											q = link(s+1);
											if (q > 0)
												hyfbchar = subtype(q);
											while (q > 0)
											{
												c = subtype(q);
												if (lc_code(c) == 0)
													break;
												if (j == 63)
													break;
												j++;
												hu[j] = c;
												hc[j] = lc_code(c);
												q = link(q);
											}
											hb = s;
											hn = j;
											if (subtype(s)%2)
												hyfbchar = fontbchar[hf];
											else
												hyfbchar = 256;
										}
										else 
											if (type(s) == 11 && subtype(s) == 0)
											{
												hb = s;
												hyfbchar = fontbchar[hf];
											}
											else
												break;
									s = link(s);
								}
								if (hn < lhyf+rhyf)
									break;
								bool label34 = true;
								while (label34)
								{
									if (s < himemmin)
										switch (type(s))
										{
											case 6: 
												break;
											case 11: 
												if (subtype(s))
												{
													label34 = false;
													continue;
												}
												break;
											case 8:
											case 10:
											case 12:
											case 3:
											case 5:
											case 4: 
												label34 = false;
												continue;
											default: 
												label31 = true;
												break;
										}
									s = link(s);
								}
								if (!label31)
									hyphenate();
								break;
							}
						}
					}
					break;
				case kern_node: 
					if (subtype(curp) == explicit_)
						kern_break(autobreaking);
					else
						act_width += width(curp);
					break;
				case ligature_node:
					f = type(lig_char(curp));
					act_width += char_width(f, char_info(f, character(lig_char(curp))));
					break;
				case disc_node:
					s = pre_break(curp);
					discwidth = 0;
					if (s == 0)
						trybreak(ex_hyphen_penalty(), hyphenated);
					else
					{
						do
						{
							if (s >= himemmin)
							{
								f = type(s);
								discwidth += char_width(f, char_info(f, character(s)));
							}
							else
								switch (type(s))
								{
									case ligature_node:
										f = type(lig_char(s));
										discwidth += char_width(f, char_info(f, character(lig_char(s))));
										break;
									case hlist_node:
									case vlist_node:
									case rule_node:
									case kern_node: 
										discwidth += width(s);
										break;
									default: 
										confusion("disc3");
								}
							s = link(s);
						} while (s);
						act_width += discwidth;
						trybreak(hyphen_penalty(), 1);
						act_width -= discwidth;
					}
					r = subtype(curp);
					s = link(curp);
					while (r > 0)
					{
						if (s >= himemmin)
						{
							f = font(s);
							act_width += char_width(f, char_info(f, character(s)));
						}
						else
							switch (type(s))
							{
								case ligature_node:
									f = font(lig_char(s));
									act_width += char_width(f, char_info(f, character(lig_char(s))));
									break;
								case hlist_node:
								case vlist_node:
								case rule_node:
								case kern_node: 
									act_width += width(s);
									break;
								default: 
									confusion("disc4");
							}
						r--;
						s = link(s);
					}
					prevp = curp;
					curp = s;
					continue;
				case math_node:
					autobreaking = subtype(curp) == after;
					kern_break(autobreaking);
					break;
				case penalty_node: 
					trybreak(penalty(curp), unhyphenated);
					break;
				case mark_node:
				case ins_node:
				case adjust_node:
					break;
				default: 
					confusion("paragraph");
			}
			prevp = curp;
			curp = link(curp);
		}
		if (curp == 0)
		{
			trybreak(eject_penalty, hyphenated);
			if (link(active) != active)
			{
				r = link(active);
				fewestdemerits = max_dimen;
				do
				{
					if (type(r) != rule_node && total_demerits(r) < fewestdemerits)
					{
						fewestdemerits = total_demerits(r);
						bestbet = r;
					}
					r = link(r);
				} while (r != active);
				bestline = info(bestbet+1);
				if (looseness() == 0)
				{
					postlinebreak(finalwidowpenalty);
					q = link(active);
					while (q != active)
					{
						curp = link(q);
						if (type(q) == delta_node)
							freenode(q, delta_node_size);
						else
							freenode(q, active_node_size);
						q = curp;
					}
					q = passive;
					while (q)
					{
						curp = link(q);
						freenode(q, passive_node_size);
						q = curp;
					}
					packbeginline = 0;
					return;
				}
				r = link(active);
				actuallooseness = 0;
				do
				{
					if (type(r) != 2)
					{
						linediff = info(r+1)-bestline;
						if ((linediff < actuallooseness && looseness() <= linediff) || (linediff > actuallooseness && looseness() >= linediff))
						{
							bestbet = r;
							actuallooseness = linediff;
							fewestdemerits = total_demerits(r);
						}
						else 
							if (linediff == actuallooseness && total_demerits(r) < fewestdemerits)
							{
								bestbet = r;
								fewestdemerits = total_demerits(r);
							}
					}
					r = link(r);
				} while (r != active);
				bestline = info(bestbet+1);
				if (actuallooseness == looseness() || finalpass)
				{
					postlinebreak(finalwidowpenalty);
					q = link(active);
					while (q != active)
					{
						curp = link(q);
						if (type(q) == delta_node)
							freenode(q, delta_node_size);
						else
							freenode(q, active_node_size);
						q = curp;
					}
					q = passive;
					while (q)
					{
						curp = link(q);
						freenode(q, passive_node_size);
						q = curp;
					}
					packbeginline = 0;
					return;
				}
			}
		}
		q = link(active);
		while (q != active)
		{
			curp = link(q);
			if (type(q) == delta_node)
				freenode(q, delta_node_size);
			else
				freenode(q, active_node_size);
			q = curp;
		}
		q = passive;
		while (q)
		{
			curp = link(q);
			freenode(q, passive_node_size);
			q = curp;
		}
		;
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
	q = link(active);
	while (q != active)
	{
		curp = link(q);
		if (type(q) == delta_node)
			freenode(q, delta_node_size);
		else
			freenode(q, active_node_size);
		q = curp;
	}
	q = passive;
	while (q)
	{
		curp = link(q);
		freenode(q, passive_node_size);
		q = curp;
	}
	packbeginline = 0;
}
