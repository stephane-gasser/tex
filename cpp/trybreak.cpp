#include "trybreak.h"
#include "confusion.h"
#include "getnode.h"
#include "badness.h"
#include "freenode.h"

void trybreak(int pi, smallnumber breaktype)
{
	halfword r, prevr, oldl;
	bool nobreakyet;
	halfword prevprevr, s, q, v;
	int t;
	internalfontnumber f;
	halfword l;
	bool noderstaysactive;
	scaled linewidth;
	char fitclass;
	halfword b;
	int d;
	bool artificialdemerits;
	halfword savelink;
	scaled shortfall;
	if (abs(pi) >= 10000)
		if (pi > 0)
			return;
		else
		pi = -10000;
	nobreakyet = true;
	prevr = active;
	oldl = 0;
	copy_to_cur_active();
	while (true)
	{
		r = link(prevr);
		if (type(r) == delta_node)
		{
			update_width(r);
			prevprevr = prevr;
			prevr = r;
			continue;
		}
		l = info(r+1);
		if (l > oldl)
		{
			if ((minimumdemerits < max_dimen) and ((oldl != easyline) or (r == active)))
			{
				if (nobreakyet)
				{
					nobreakyet = false;
					set_break_width_to_background();
					s = curp;
					if (breaktype > 0)
						if (curp)
						{
							t = subtype(curp);
							v = curp;
							s = link(curp+1);
							while (t > 0)
							{
								t--;
								v = link(v);
								if (v >= himemmin)
								{
									f = type(v);
									breakwidth[1] += -char_width(f, char_info(f, subtype(v)));
								}
								else
									switch (type(v))
									{
										case ligature_node:
											f = type(v+1);
											breakwidth[1] += -char_width(f, char_info(f, type(v+1)));
											break;
										case hlist_node:
										case vlist_node:
										case rule_node:
										case kern_node: 
											breakwidth[1] -= width(v);
											break;
										default: 
											confusion("disc1");
									}
							}
							while (s)
							{
								if (s >= himemmin)
								{
									f = type(s);
									breakwidth[1] += char_width(f, char_info(f, subtype(s)));
								}
								else
									switch (type(s))
									{
										case ligature_node:
											f = type(s+1);
											breakwidth[1] += char_width(f, char_info(f, subtype(s+1)));
											break;
										case hlist_node:
										case vlist_node:
										case rule_node:
										case kern_node: 
											breakwidth[1] += width(s);
											break;
										default: 
											confusion("disc2");
									}
								s = link(s);
							}
							breakwidth[1] += discwidth;
							if (link(curp+1) == 0)
								s = link(v);
						}
					while (s)
					{
						if (s >= himemmin)
							continue;
						switch (type(s))
						{
							case glue_node:
								v = glue_ptr(s);
								breakwidth[1] -= width(v);
								breakwidth[2+stretch_order(v)] -= stretch(v);
								breakwidth[6] -= shrink(v);
								break;
							case penalty_node: 
								break;
							case math_node: 
								breakwidth[1] -= width(s);
								break;
							case kern_node: 
								if (subtype(s) != explicit_)
									continue;
								else
									breakwidth[1] -= width(s);
								break;
							default: 
								continue;
						}
						s = link(s);
					}
				}
				if (type(prevr) == delta_node)
					convert_to_break_width(prevr);
				else 
					if (prevr == active)
						store_break_width();
					else
					{
						q = getnode(7);
						link(q) = r;
						type(q) = delta_node;
						subtype(q) = 0;
						new_delta_to_break_width(q);
						link(prevr) = q;
						prevprevr = prevr;
						prevr = q;
					}
				if (abs(int_par(adj_demerits_code)) >= max_dimen-minimumdemerits)
					minimumdemerits = 1073741822;
				else
					minimumdemerits += abs(int_par(adj_demerits_code));
				for (fitclass = very_loose_fit; fitclass <= tight_fit; fitclass++)
				{
					if (minimaldemerits[fitclass] <= minimumdemerits)
					{
						q = getnode(2);
						link(q) = passive;
						passive = q;
						break_node(q) = curp;
						line_number(q) = bestplace[fitclass];
						q = getnode(3);
						break_node(q) = passive;
						line_number(q) = bestplline[fitclass]+1;
						fitness(q) = fitclass;
						type(q) = breaktype;
						total_demerits(q) = minimaldemerits[fitclass];
						link(q) = r;
						link(prevr) = q;
						prevr = q;
					}
					minimaldemerits[fitclass] = max_dimen;
				}
				minimumdemerits = max_dimen;
				if (r != active)
				{
					q = getnode(7);
					link(q) = r;
					type(q) = delta_node;
					subtype(q) = 0;
					new_delta_from_break_width(q);
					link(prevr) = q;
					prevprevr = prevr;
					prevr = q;
				}
			}
			if (r == active)
				return;
			if (l > easyline)
			{
				linewidth = secondwidth;
				oldl = 65534;
			}
			else
			{
				oldl = l;
				if (l > lastspecialline)
					linewidth = secondwidth;
				else 
					if (par_shape_ptr() == 0)
						linewidth = firstwidth;
					else
						linewidth = mem[par_shape_ptr()+2*l].int_;
			}
		}
		artificialdemerits = false;
		shortfall = linewidth-curactivewidth[1];
		if (shortfall > 0)
			if (curactivewidth[3] || curactivewidth[4] || curactivewidth[5])
			{
				b = 0;
				fitclass = decent_fit;
			}
			else
			{
				if (shortfall > 7230584 && curactivewidth[2] < 1663497)
				{
					b = 10000;
					fitclass = very_loose_fit;
				}
				else
				{
					b = badness(shortfall, curactivewidth[2]);
					if (b > 12)
						if (b > 99)
							fitclass = very_loose_fit;
						else
							fitclass = loose_fit;
					else
						fitclass = decent_fit;
				}
			}
		else
		{
			if (-shortfall > curactivewidth[6])
				b = 10001;
			else
				b = badness(-shortfall, curactivewidth[6]);
			if (b > 12)
				fitclass = tight_fit;
			else
				fitclass = decent_fit;
		}
		if (b > 10000 || pi == -10000)
		{
			if (finalpass && minimumdemerits == max_dimen && link(r) == active &&prevr == active)
				artificialdemerits = true;
			else 
				if (b > threshold)
				{
					link(prevr) = link(r);
					freenode(r, 3);
					if (prevr == active)
					{
						r = link(active);
						if (type(r) == delta_node)
						{
							update_active(r);
							copy_to_cur_active();
							link(active) = link(r);
							freenode(r, 7);
						}
					}
					else 
						if (type(prevr) == delta_node)
						{
							r = link(prevr);
							if (r == active)
							{
								downdate_width(prevr);
								link(prevprevr) = active;
								freenode(prevr, 7);
								prevr = prevprevr;
							}
							else 
								if (type(r) == delta_node)
								{
									update_width(r);
									combine_two_deltas(prevr, r);
									link(prevr) = link(r);
									freenode(r, 7);
								}
						}
					continue;
				}
			noderstaysactive = false;
		}
		else
		{
			prevr = r;
			if (b > threshold)
				continue;
			noderstaysactive = true;
		}
		if (artificialdemerits)
			d = 0;
		else
		{
			d = int_par(line_penalty_code)+b;
			if (abs(d) >= 10000)
				d = 100000000;
			else
				d *= d;
			if (pi)
				if (pi > 0)
					d += pi*pi;
				else 
					if (pi > -10000)
						d -= pi*pi;
			if (breaktype == 1 && type(r) == vlist_node)
				if (curp)
					d += int_par(double_hyphen_demerits_code);
				else
				d += int_par(final_hyphen_demerits_code);
			if (abs(fitclass-subtype(r)) > 1)
				d += int_par(adj_demerits_code);
		}
		d += depth(r);
		if (d <= minimaldemerits[fitclass])
		{
			minimaldemerits[fitclass] = d;
			bestplace[fitclass] = link(r+1);
			bestplline[fitclass] = l;
			if (d < minimumdemerits)
				minimumdemerits = d;
		}
		if (noderstaysactive)
			continue;
		link(prevr) = link(r);
		freenode(r, 3);
		if (prevr == active)
		{
			r = link(active);
			if (type(r) == delta_node)
			{
				update_active(r);
				copy_to_cur_active();
				link(active) = link(r);
				freenode(r, 7);
			}
		}
		else 
			if (type(prevr) == delta_node)
			{
				r = link(prevr);
				if (r == active)
				{
					downdate_width(prevr);
					link(prevprevr) = active;
					freenode(prevr, 7);
					prevr = prevprevr;
				}
				else 
					if (type(r) == delta_node)
					{
						update_width(r);
						combine_two_deltas(prevr, r);
						link(prevr) = link(r);
						freenode(r, 7);
					}
			}
	}
}
