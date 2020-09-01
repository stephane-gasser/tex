#include "trybreak.h"
#include "erreur.h"
#include "noeud.h"
#include "badness.h"
#include "police.h"
#include "equivalent.h"

static LinkedNode *bestplace[4];

void trybreak(int pi, smallnumber breaktype)
{
	if (pi >= 10000)
		return;
	pi = std::max(pi, -10000);
	auto nobreakyet = true;
	auto prevr = active;
	halfword oldl = 0;
	std::copy(activewidth, activewidth+7, curactivewidth);
	LinkedNode* prevprevr;
	while (true)
	{
		auto r = prevr->link;
		if (r->type == delta_node)
		{
			dynamic_cast<DeltaNode*>(r)->update_width();
			prevprevr = prevr;
			prevr = r;
			continue;
		}
		char fitclass;
		auto l = dynamic_cast<ActiveNode*>(r)->line_number;
		scaled linewidth;
		halfword b;
		if (l > oldl)
		{
			if (minimumdemerits < awful_bad && (oldl != easyline || r == active))
			{
				if (nobreakyet)
				{
					nobreakyet = false;
					std::copy(background, background+7, breakwidth);
					auto s = curp;
					if (breaktype > unhyphenated)
						if (curp)
						{
							auto Curp = dynamic_cast<DiscNode*>(curp);
							auto t = Curp->replace_count;
							auto v = curp;
							s = Curp->post_break;
							while (t > 0)
							{
								t--;
								v = v->link;
								if (v->is_char_node())
								{
									auto V = dynamic_cast<CharNode*>(v);
									auto ft = V->font;
									breakwidth[1] += -ft.char_width(V->character);
								}
								else
									switch (v->type)
									{
										case ligature_node:
										{
											auto V = dynamic_cast<LigatureNode*>(v);
											auto ft = V->lig_char.font;
											breakwidth[1] += -ft.char_width(V->lig_char.character);
											break;
										}
										case hlist_node:
										case vlist_node:
										case rule_node:
											breakwidth[1] -= dynamic_cast<RuleNode*>(v)->width;
											break;
										case kern_node: 
											breakwidth[1] -= dynamic_cast<KernNode*>(v)->width;
											break;
										default: 
											confusion("disc1");
									}
							}
							for ( ;s; next(s))
								if (s->is_char_node())
								{
									auto S = dynamic_cast<CharNode*>(s);
									auto ft = S->font;
									breakwidth[1] += ft.char_width(S->character);
								}
								else
									switch (s->type)
									{
										case ligature_node:
										{
											auto S = dynamic_cast<LigatureNode*>(s);
											auto ft = S->lig_char.font;
											breakwidth[1] += ft.char_width(S->lig_char.character);
											break;
										}
										case hlist_node:
										case vlist_node:
										case rule_node:
											breakwidth[1] += dynamic_cast<RuleNode*>(s)->width;
											break;
										case kern_node: 
											breakwidth[1] += dynamic_cast<KernNode*>(s)->width;
											break;
										default: 
											confusion("disc2");
									}
							breakwidth[1] += discwidth;
							if (Curp->post_break == nullptr)
								s = v->link;
						}
					while (s)
					{
						if (s->is_char_node())
							continue;
						switch (s->type)
						{
							case glue_node:
							{
								auto v = dynamic_cast<GlueNode*>(s)->glue_ptr;
								breakwidth[1] -= v->width;
								breakwidth[2+v->stretch_order] -= v->stretch;
								breakwidth[6] -= v->shrink;
								break;
							}
							case penalty_node: 
								break;
							case math_node: 
								breakwidth[1] -= dynamic_cast<MathNode*>(s)->width;
								break;
							case kern_node: 
							{
								auto S = dynamic_cast<KernNode*>(s);
								if (S->subtype != explicit_)
									continue;
								else
									breakwidth[1] -= S->width;
								break;
							}
							default: 
								continue;
						}
						next(s);
					}
				}
				if (prevr->type == delta_node)
					dynamic_cast<DeltaNode*>(prevr)->convert_to_break_width();
				else 
					if (prevr == active)
						std::copy(breakwidth, breakwidth+7, activewidth);
					else
					{
						auto q = new DeltaNode(r);
						q->new_delta_to_break_width();
						prevr->link = q;
						prevprevr = prevr;
						prevr = q;
					}
				if (abs(adj_demerits()) >= max_dimen-minimumdemerits)
					minimumdemerits = 1073741822;
				else
					minimumdemerits += abs(adj_demerits());
				for (fitclass = very_loose_fit; fitclass <= tight_fit; fitclass++)
				{
					if (minimaldemerits[fitclass] <= minimumdemerits)
					{
						auto q = new PassiveNode;
						q->link = passive;
						passive = q;
						q->cur_break = curp;
						q->prev_break = bestplace[fitclass];
						auto Q = new ActiveNode(bestplline[fitclass], r);
						Q->break_node = passive;
						Q->fitness = fitclass;
						Q->type = breaktype;
						Q->total_demerits = minimaldemerits[fitclass];
						prevr->link = Q;
						prevr = Q;
					}
					minimaldemerits[fitclass] = max_dimen;
				}
				minimumdemerits = max_dimen;
				if (r != active)
				{
					auto q = new DeltaNode(r);
					q->new_delta_from_break_width();
					prevr->link = q;
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
					if (par_shape_ptr() == nullptr)
						linewidth = firstwidth;
					else
						linewidth = par_shape_ptr()->values[2*l-1];
			}
		}
		auto artificialdemerits = false;
		scaled shortfall = linewidth-curactivewidth[1];
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
		bool noderstaysactive;
		if (b > 10000 || pi == -10000)
		{
			if (finalpass && minimumdemerits == max_dimen && r->link == active && prevr == active)
				artificialdemerits = true;
			else 
				if (b > threshold)
				{
					prevr->link = r->link;
					delete r;
					if (prevr == active)
					{
						r = active->link;
						if (r->type == delta_node)
						{
							dynamic_cast<DeltaNode*>(r)->update_active();
							std::copy(activewidth, activewidth+7, curactivewidth);
							active->link = r->link;
							delete r;
						}
					}
					else 
						if (prevr->type == delta_node)
						{
							r = prevr->link;
							if (r == active)
							{
								dynamic_cast<DeltaNode*>(prevr)->downdate_width();
								prevprevr->link = active;
								delete prevr;
								prevr = prevprevr;
							}
							else 
								if (r->type == delta_node)
								{
									dynamic_cast<DeltaNode*>(r)->update_width();
									dynamic_cast<DeltaNode*>(prevr)->combine_two_deltas(dynamic_cast<DeltaNode*>(r));
									prevr->link = r->link;
									delete r;
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
		int d = 0;
		if (!artificialdemerits)
		{
			d = line_penalty()+b;
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
			if (breaktype == 1 && r->type == vlist_node)
				if (curp)
					d += double_hyphen_demerits();
				else
				d += final_hyphen_demerits();
			if (abs(fitclass-dynamic_cast<ActiveNode*>(r)->fitness) > 1)
				d += adj_demerits();
		}
		d += dynamic_cast<ActiveNode*>(r)->total_demerits;
		if (d <= minimaldemerits[fitclass])
		{
			minimaldemerits[fitclass] = d;
			bestplace[fitclass] = dynamic_cast<ActiveNode*>(r)->break_node;
			bestplline[fitclass] = l;
			if (d < minimumdemerits)
				minimumdemerits = d;
		}
		if (noderstaysactive)
			continue;
		prevr->link = r->link;
		delete r;
		if (prevr == active)
		{
			r = active->link;
			if (r->type == delta_node)
			{
				dynamic_cast<DeltaNode*>(r)->update_active();
				std::copy(activewidth, activewidth+7, curactivewidth);
				active->link = r->link;
				delete r;
			}
		}
		else 
			if (prevr->type == delta_node)
			{
				r = prevr->link;
				if (r == active)
				{
					dynamic_cast<DeltaNode*>(prevr)->downdate_width();
					prevprevr->link = active;
					delete prevr;
					prevr = prevprevr;
				}
				else 
					if (r->type == delta_node)
					{
						dynamic_cast<DeltaNode*>(r)->update_width();
						dynamic_cast<DeltaNode*>(prevr)->combine_two_deltas(dynamic_cast<DeltaNode*>(r));
						prevr->link = r->link;
						delete r;
					}
			}
	}
}
