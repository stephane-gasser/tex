#include "linebreak.h"
#include "noeud.h"
#include "deleteglueref.h"
#include "popnest.h"
#include "cesure.h"
#include "erreur.h"
#include "police.h"
#include "equivalent.h"
#include "noeud.h"
#include "badness.h"
#include "alignement.h"
#include "boite.h"

class PassiveNode : public LinkedNode
{
	public:
		LinkedNode *cur_break; //in passive node, points to position of this breakpoint
		LinkedNode *prev_break; //points to passive node that should precede this one
		LinkedNode* &next_break = prev_break; //new name for |prev_break| after links are reversed
//		halfword serial;
};

inline PassiveNode *passive;

enum
{
	very_loose_fit = 0, //!< fitness classification for lines stretching more than their stretchability
	loose_fit = 1, //!< fitness classification for lines stretching 0.5 to 1.0 of their stretchability
	decent_fit = 2, //!< fitness classification for all other lines
	tight_fit = 3 //!< fitness classification for lines shrinking 0.5 to 1.0 of their stretchability
};

enum
{
	unhyphenated = 0, //!< the \a type of a normal active break node
	hyphenated = 1 //!< the \a type of an active node that breaks at a \a disc_node
};

class ActiveNode : public LinkedNode
{
	public:
		quarterword fitness = decent_fit;
		PassiveNode *break_node = nullptr;
		halfword line_number;
		int total_demerits = 0;
		ActiveNode(int best, LinkedNode *l) : line_number(best+1)
		{
			type = unhyphenated;
			link = l;
		}
};

inline ActiveNode * const active = dynamic_cast<ActiveNode*>(&heads[7]); //!< head of active list in \a line_break, needs two words
	// initialisation active->type = hyphenated; active->line_number = empty_flag;
inline ActiveNode *bestbet;

static scaled activewidth[7]; // commence à 1
static scaled curactivewidth[7]; // commence à 1
static scaled background[7]; // commence à 1 
static scaled breakwidth[7]; // commence à 1

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
		void update_width(void)
		{
			for (int i = 1; i <= 6; i++)
				curactivewidth[i] += width[i-1];
		}
		void update_active(void)
		{
			for (int i = 1; i <= 6; i++)
				activewidth[i] += width[i-1];
		}
		void convert_to_break_width(void)
		{
			for (int i = 1; i <= 6; i++)
				width[i-1] += breakwidth[i]-curactivewidth[i];
		}
		void downdate_width(void)
		{
			for (int i = 1; i <= 6; i++)
				curactivewidth[i] -= width[i-1];
		}
		void combine_two_deltas(DeltaNode *r)
		{
			for (int i = 0; i < 6; i++)
				width[i] += r->width[i];
		}
};

static LinkedNode *curp;
static scaled firstwidth;
static scaled firstindent;
static scaled secondwidth;
static scaled secondindent;
static halfword bestline;
static halfword lastspecialline;

static void postlinebreak(int finalwidowpenalty)
{
	bool discbreak, postdiscbreak;
	scaled curwidth, curindent;
	quarterword t;
	int pen;
	halfword curline;
	LinkedNode *q, *r, *s;
	q = bestbet->break_node;
	curp = nullptr;
	do //Reverse the links of the relevant passive nodes, setting |cur_p| to the first breakpoint
	{
		r = q;
		q = dynamic_cast<PassiveNode*>(q)->prev_break;
		dynamic_cast<PassiveNode*>(r)->next_break = curp;
		curp = r;
	} while (q);
	curline = prev_graf+1;
	do //Justify the line ending at breakpoint |cur_p|, and append it to the current vertical list, together with associated penalties and other insertions
	{
		q = dynamic_cast<PassiveNode*>(curp)->cur_break;
		discbreak = false;
		postdiscbreak = false;
		if (q)
			if (q->type == glue_node)
			{
				auto Q = dynamic_cast<GlueNode*>(q);
				deleteglueref(Q->glue_ptr);
				Q->glue_ptr = right_skip();
				Q->glue_ptr->glue_ref_count++;
				Q->subtype = right_skip_code+1;
			}
			else
			{
				if (q->type == disc_node) //Change discretionary to compulsory and set |disc_break:=true|
				{
					auto Q = dynamic_cast<DiscNode*>(q);
					t = Q->replace_count;
					//Destroy the |t| nodes following |q|, and make |r| point to the following node@
					if (t == 0)
						r = q->link;
					else
					{
						r = q;
						while (t > 1)
						{
							next(r);
							t--;
						}
						s = r->link;
						r = s->link;
						s->link = nullptr;
						flushnodelist(q->link);
						Q->replace_count = 0;
					}
					if (Q->post_break)
					{
						s = Q->post_break;
						followUntilBeforeTarget(s);
						s->link = r;
						r = Q->post_break;
						Q->post_break = nullptr;
						postdiscbreak = true;
					}
					if (Q->pre_break)
					{
						s = Q->pre_break;
						q->link = s;
						followUntilBeforeTarget(s);
						Q->pre_break = nullptr;
						q = s;
					}
					q->link = r;
					discbreak = true;
				}
				else 
				{
					if (q->type == math_node)
						dynamic_cast<MathNode*>(q)->width = 0;
					if (q->type == kern_node)
						dynamic_cast<KernNode*>(q)->width = 0;
				}
				r = new GlueNode(right_skip_code);
				r->link = q->link;
				q->link = r;
				q = r;
			}
		else
		{
			q = temp_head;
			followUntilBeforeTarget(q);
			r = new GlueNode(right_skip_code);
			r->link = q->link;
			q->link = r;
			q = r;
		}
		r = q->link;
		q->link = 0;
		q = temp_head->link;
		temp_head->link = r;
		if (left_skip)
		{
			r = new GlueNode(left_skip());
			r->link = q;
			q = r;
		}
		if (curline > lastspecialline)
		{
			curwidth = secondwidth;
			curindent = secondindent;
		}
		else 
			if (par_shape_ptr() == nullptr)
			{
				curwidth = firstwidth;
				curindent = firstindent;
			}
			else
			{
				curwidth = par_shape_ptr()->values[2*curline-1];
				curindent = par_shape_ptr()->values[2*curline-2];
			}
		adjusttail = adjust_head;
		justbox = hpack(q, curwidth, 0);
		justbox->shift_amount = curindent;
		appendtovlist(justbox);
		if (adjust_head != adjusttail)
		{
			tail->link = adjust_head->link;
			tail = adjusttail;
		}
		adjusttail = nullptr;
		if (curline+1 != bestline)
		{
			pen = inter_line_penalty();
			if (curline == prev_graf+1)
				pen += club_penalty();
			if (curline+2 == bestline)
				pen += finalwidowpenalty;
			if (discbreak)
				pen += broken_penalty();
			if (pen)
			{
				r = new PenaltyNode(pen);
				tail_append(r);
			}
		}
		curline++;
		curp = dynamic_cast<PassiveNode*>(curp)->next_break;
		if (curp)
			if (!postdiscbreak)
			{
				r = temp_head;
				while (true)
				{
					q = r->link;
					if (q == dynamic_cast<PassiveNode*>(curp)->cur_break)
						break;
					if (q->is_char_node())
						break;
					if (q->type < math_node) // non_discardable
						break;
					if (q->type == kern_node)
						if (dynamic_cast<KernNode*>(q)->subtype != explicit_)
							break;
					r = q; //now |type(q)=glue_node|, |kern_node|, |math_node| or |penalty_node|
				}
				if (r != temp_head)
				{
					r->link = nullptr;
					flushnodelist(temp_head->link);
					temp_head->link = q;
				}
			}
	} while (curp);
	if (curline != bestline || temp_head->link)
		confusion("line breaking");
	prev_graf = bestline-1;
}

static LinkedNode *bestplace[4];
static int minimaldemerits[4];
static int minimumdemerits;
static halfword easyline;
static bool finalpass;
static scaled discwidth;
static halfword bestplline[4];
static int threshold;

static void trybreak(int pi, smallnumber breaktype)
{
	if (pi >= 10000)
		return;
	pi = std::max(pi, -10000);
	auto nobreakyet = true;
	LinkedNode *prevr = active;
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
									breakwidth[1] += -fonts[V->font].char_width(V->character);
								}
								else
									switch (v->type)
									{
										case ligature_node:
										{
											auto V = dynamic_cast<LigatureNode*>(v)->lig_char;
											breakwidth[1] += -fonts[V.font].char_width(V.character);
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
									breakwidth[1] += fonts[S->font].char_width(S->character);
								}
								else
									switch (s->type)
									{
										case ligature_node:
										{
											auto S = dynamic_cast<LigatureNode*>(s)->lig_char;
											breakwidth[1] += fonts[S.font].char_width(S.character);
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

static bool noshrinkerroryet;

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

static auto &act_width = activewidth[1]; //!< length from first active node to current node

static void kern_break(bool autobreaking, int w)
{
	if (!curp->link->is_char_node() && autobreaking && curp->link->type == glue_node)
		trybreak(0, unhyphenated);
	act_width += w;
}

static void flushAfterActive(void)
{
	LinkedNode *q;
	for (q = active->link; q != active; )
	{
		curp = q->link;
		delete q;
		q = curp;
	}
	for (q = passive; q; )
	{
		curp = q->link;
		delete q;
		q = curp;
	}
}

static int fewestdemerits;
static bool secondpass;
static int actuallooseness;
static int linediff;

void linebreak(int finalwidowpenalty)
{
	bool autobreaking;
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
	ASCIIcode initcurlang = prev_graf%(1<<16);
	initlhyf = prev_graf>>22;
	initrhyf = (prev_graf>>16)%(1<<6);
	popnest();
	noshrinkerroryet = true;
	setLeftSkip(check_shrinkage(left_skip()));
	setRightSkip(check_shrinkage(right_skip()));
	auto q = left_skip();
	auto r = right_skip();
	background[1] = q->width+r->width;
	std::fill(background+2, background+6, 0);
	background[2+q->stretch_order] = q->stretch;
	background[2+r->stretch_order] += r->stretch;
	background[6] = q->shrink+r->shrink;
	minimumdemerits = max_dimen;
	std::fill(minimaldemerits, minimaldemerits+4, max_dimen);
	if (par_shape_ptr() == nullptr)
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
		lastspecialline = par_shape_ptr()->values.size()/2-1;
		secondwidth = par_shape_ptr()->values[2*lastspecialline+1];
		secondindent = par_shape_ptr()->values[2*lastspecialline];
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
		LinkedNode *q = new ActiveNode(prev_graf, active);
		active->link = q;
		std::copy(background, background+7, activewidth);
		passive = nullptr;
		fontinshortdisplay = null_font;
		curp = temp_head->link;
		autobreaking = true;
		auto prevp = curp;
		while (curp && active->link != active)
		{
			if (curp->is_char_node())
			{
				prevp = curp;
				for (; curp->is_char_node(); next(curp))
				{
					auto Curp = dynamic_cast<CharNode*>(curp);
					act_width += fonts[Curp->font].char_width(Curp->character);
				}
			}
			switch (curp->type)
			{
				case hlist_node:
				case vlist_node:
				case rule_node: 
					act_width += dynamic_cast<RuleNode*>(curp)->width;
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
							if (precedes_break(prevp))
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
									hf = S->font;
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
											hf = dynamic_cast<CharNode*>(q)->font;
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
										if (S->font != hf)
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
											if (S->lig_char.font != hf)
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
												next(q);
											}
											hb = s;
											hn = j;
											if (S->subtype%2)
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
									next(s);
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
									next(s);
								}
								if (!label31)
									hyphenate(curp);
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
						kern_break(autobreaking, Curp->width);
					else
						act_width += Curp->width;
					break;
				}
				case ligature_node:
				{
					auto C = dynamic_cast<LigatureNode*>(curp)->lig_char;
					act_width += fonts[C.font].char_width(C.character);
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
								discwidth += fonts[S->font].char_width(S->character);
							}
							else
								switch (s->type)
								{
									case ligature_node:
									{
										auto S = dynamic_cast<LigatureNode*>(s)->lig_char;
										discwidth += fonts[S.font].char_width(S.character);
										break;
									}
									case hlist_node:
									case vlist_node:
									case rule_node:
										discwidth += dynamic_cast<RuleNode*>(s)->width;
										break;
									case kern_node: 
										discwidth += dynamic_cast<KernNode*>(s)->width;
										break;
									default: 
										confusion("disc3");
								}
							next(s);
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
							act_width += fonts[S->font].char_width(S->character);
						}
						else
							switch (s->type)
							{
								case ligature_node:
								{
									auto S = dynamic_cast<LigatureNode*>(s)->lig_char;
									act_width += fonts[S.font].char_width(S.character);
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
						next(s);
					}
					prevp = curp;
					curp = s;
					continue;
				}
				case math_node:
				{
					auto Curp = dynamic_cast<MathNode*>(curp);
					autobreaking = Curp->subtype == after;
					kern_break(autobreaking, Curp->width);
					break;
				}
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
				fewestdemerits = max_dimen;
				for (auto r = active->link; r != active; next(r))
					if (r->type != rule_node && dynamic_cast<ActiveNode*>(r)->total_demerits < fewestdemerits)
					{
						bestbet = dynamic_cast<ActiveNode*>(r);
						fewestdemerits = bestbet->total_demerits;
					}
				bestline = bestbet->line_number;
				if (looseness() == 0)
				{
					postlinebreak(finalwidowpenalty);
					flushAfterActive();
					packbeginline = 0;
					return;
				}
				actuallooseness = 0;
				auto r = active->link;
				do
				{
					if (r->type != delta_node)
					{
						auto R = dynamic_cast<ActiveNode*>(r);
						linediff = R->line_number-bestline;
						if ((linediff < actuallooseness && looseness() <= linediff) || (linediff > actuallooseness && looseness() >= linediff))
						{
							bestbet = R;
							actuallooseness = linediff;
							fewestdemerits = R->total_demerits;
						}
						else 
							if (linediff == actuallooseness && R->total_demerits < fewestdemerits)
							{
								bestbet = R;
								fewestdemerits = R->total_demerits;
							}
					}
					next(r);
				} while (r != active);
				bestline = bestbet->line_number;
				if (actuallooseness == looseness() || finalpass)
				{
					postlinebreak(finalwidowpenalty);
					flushAfterActive();
					packbeginline = 0;
					return;
				}
			}
		}
		flushAfterActive();
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
	flushAfterActive();
	packbeginline = 0;
}
