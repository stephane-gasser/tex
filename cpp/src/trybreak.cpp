#include "trybreak.h"
#include "erreur.h"
#include "noeud.h"
#include "badness.h"
#include "police.h"
#include "equivalent.h"

static void copy_to_cur_active(void) 
{
	for (int i = 1; i <= 6; i++)
		curactivewidth[i] = activewidth[i];
}

static void update_width(halfword r)
{
	for (int i = 1; i <= 6; i++)
		curactivewidth[i] += mem[r+i].int_;
}

static void set_break_width_to_background(void)
{
	for (int i = 1; i <= 6; i++)
		breakwidth[i] = background[i];
}

static void convert_to_break_width(halfword prev_r)
{
	for (int i = 1; i <= 6; i++)
		mem[prev_r+i].int_ += -curactivewidth[i]+breakwidth[i];
}

static void store_break_width(void)
{
	for (int i = 1; i <= 6; i++)
		activewidth[i] = breakwidth[i];
}

static void combine_two_deltas(halfword prev_r, halfword r)
{
	for (int i = 1; i <= 6; i++)
		mem[prev_r+i].int_ += mem[r+i].int_;
}

static void downdate_width(halfword prev_r)
{
	for (int i = 1; i <= 6; i++)
		curactivewidth[i] -= mem[prev_r+i].int_;
}

static void update_active(halfword r)
{
	for (int i = 1; i <= 6; i++)
		activewidth[i] += mem[r+i].int_;
}

class DeltaNode : public LinkedNode
{
	public:
		quarterword subtype = 0;
		int width[6];
		DeltaNode(LinkedNode *r)
		{
			link = r;
			type = delta_node;
		}
		void new_delta_to_break_width(void)
		{
			for (int i = 1; i <= 6; i++)
				width[i-1] = breakwidth[i]-curactivewidth[i];
		}
		void new_delta_from_break_width(void)
		{
			for (int i = 1; i <= 6; i++)
				width[i-1] = curactivewidth[i]-breakwidth[i];
		}
};

void trybreak(int pi, smallnumber breaktype)
{
	if (pi >= 10000)
		return;
	pi = std::max(pi, -10000);
	auto nobreakyet = true;
	auto prevr = active;
	halfword oldl = 0;
	copy_to_cur_active();
	LinkedNode* prevprevr;
	while (true)
	{
		auto r = prevr->link;
		if (r->type == delta_node)
		{
			update_width(r->num);
			prevprevr = prevr;
			prevr = r;
			continue;
		}
		char fitclass;
		auto l = line_number(r->num);
		scaled linewidth;
		halfword b;
		if (l > oldl)
		{
			if (minimumdemerits < awful_bad && (oldl != easyline || r == active))
			{
				if (nobreakyet)
				{
					nobreakyet = false;
					set_break_width_to_background();
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
											breakwidth[1] -= width(v->num);
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
											breakwidth[1] += width(s->num);
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
								breakwidth[1] -= width(s->num);
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
					convert_to_break_width(prevr->num);
				else 
					if (prevr == active)
						store_break_width();
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
						auto q = getnode(passive_node_size);
						link(q) = passive;
						passive = q;
						break_node(q) = curp->num;
						line_number(q) = bestplace[fitclass];
						q = getnode(active_node_size);
						break_node(q) = passive;
						line_number(q) = bestplline[fitclass]+1;
						fitness(q) = fitclass;
						type(q) = breaktype;
						total_demerits(q) = minimaldemerits[fitclass];
						link(q) = r->num;
						prevr->link->num = q;
						prevr->num = q;
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
							update_active(r->num);
							copy_to_cur_active();
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
								downdate_width(prevr->num);
								prevprevr->link = active;
								delete prevr;
								prevr = prevprevr;
							}
							else 
								if (r->type == delta_node)
								{
									update_width(r->num);
									combine_two_deltas(prevr->num, r->num);
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
			if (abs(fitclass-subtype(r->num)) > 1)
				d += adj_demerits();
		}
		d += depth(r->num);
		if (d <= minimaldemerits[fitclass])
		{
			minimaldemerits[fitclass] = d;
			bestplace[fitclass] = break_node(r->num);
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
				update_active(r->num);
				copy_to_cur_active();
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
					downdate_width(prevr->num);
					prevprevr->link = active;
					delete prevr;
					prevr = prevprevr;
				}
				else 
					if (r->type == delta_node)
					{
						update_width(r->num);
						combine_two_deltas(prevr->num, r->num);
						prevr->link = r->link;
						delete r;
					}
			}
	}
}
