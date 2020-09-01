#include "finalign.h"
#include "sauvegarde.h"
#include "deleteglueref.h"
#include "noeud.h"
#include "boite.h"
#include "popalignment.h"
#include "popnest.h"
#include "impression.h"
#include "doassignments.h"
#include "erreur.h"
#include "lecture.h"
#include "resumeafterdisplay.h"
#include "buildpage.h"
#include "noeud.h"
#include <cmath>

void finalign(AlignRecordNode* &loop)
{
	scaled t, w; // width of column
	halfword n; // matching span amount
	if (curgroup != 6)
		confusion("align1");
	unsave();
	if (curgroup != 6)
		confusion("align0"); 
	unsave();
	scaled o = nest[nestptr-1].modefield == mmode ? display_indent() : 0; // shift offset for unset boxes
	auto q = preamble->link;
	do
	{
		// q: AlignNode ??
		LinkedNode *l;
		l->num = u_part(q->num);
		flushnodelist(l);
		l->num = v_part(q->num);
		flushnodelist(l);
		auto p = q->link->link;
		if (is_running(width(q->num)))
		{
			//Nullify |width(q)| and the tabskip glue following this column
			width(q->num) = 0;
			auto r = dynamic_cast<GlueNode*>(q->link);
			auto s = r->glue_ptr;
			if (s)
			{
				zero_glue->glue_ref_count++;
				deleteglueref(s);
				r->glue_ptr = zero_glue;
			}
		}
		if (info(q->num) != end_span->num)
		{
			//Merge the widths in the span nodes of |q| with those of |p|, destroying the span nodes of |q|
			t = width(q->num)+dynamic_cast<GlueNode*>(q->link)->glue_ptr->width;
			SpanNode *r;
			SpanNode *s;
			r->num = info(q->num);
			s = end_span;
			s->info->num = p->num;
			n = 1;
			do
			{
				r->width -= t;
				SpanNode *u;
				u = r->info;
				while (r->Link > n)
				{
					s = s->info;
					n = s->info->Link+1;
				}
				if (r->Link < n)
				{
					r->info = s->info;
					s->info = r;
					r->Link--;
					s = r;
				}
				else
				{
					if (r->width > s->info->width)
						s->info->width = r->width;
					delete r;
				}
				r = u;
			} while (r != end_span);
		}
		q->type = unset_node;
		auto Q = dynamic_cast<UnsetNode*>(q);
		Q->span_count = 0;
		Q->height = 0;
		Q->depth = 0;
		Q->glue_order = 0;
		Q->glue_sign = 0;
		Q->glue_stretch = 0;
		Q->glue_shrink = 0;
		q = p;
	} while (q);
	auto s1 = savestack.back()->int_;
	savestack.pop_back();
	auto s0 = savestack.back()->int_;
	savestack.pop_back();
	packbeginline = -mode_line;
	BoxNode *p;
	if (mode == -vmode)
	{
		scaled rulesave = overfull_rule();
		overfull_rule() = 0;
		p = hpack(preamble, s1, s0);
		overfull_rule() = rulesave;
	}
	else
	{
		q = preamble->link;
		auto Q = dynamic_cast<UnsetNode*>(q);
		do
		{
			Q->height = Q->width;
			Q->width = 0;
			next(q);
			next(q);
		} while (q);
		p = vpack(preamble, s1, s0);
		q = preamble->link;
		do
		{
			Q->width = Q->height;
			Q->height = 0;
			next(q);
			next(q);
		} while (q);
	}
	packbeginline = 0;
	q = head->link;
	auto s = head;
	while (q)
	{
		if (!q->is_char_node())
			if (q->type == unset_node)
			{
				auto Q = dynamic_cast<UnsetNode*>(q);
				if (mode == -vmode)
				{
					Q->type = hlist_node;
					Q->width = p->width;
				}
				else
				{
					Q->type = vlist_node;
					Q->height = p->height;
				}
				//q : BoxNode
				Q->glue_order = p->glue_order;
				Q->glue_sign = p->glue_sign;
				Q->glue_set = p->glue_set;
				Q->shift_amount = o;
				auto r = Q->list_ptr->link;
				s = Q->list_ptr->link;
				do
				{
					auto R = dynamic_cast<UnsetNode*>(r);
					auto S = dynamic_cast<BoxNode*>(s);
					auto P = dynamic_cast<BoxNode*>(p);
					n = R->span_count;
					t = S->width;
					w = t;
					auto u = hold_head;
					while (n > 0)
					{
						n--;
						next(s);
						auto V = dynamic_cast<GlueNode*>(s)->glue_ptr;
						auto g = new GlueNode(V);
						g->subtype = tab_skip_code+1;
						u->link = g;
						u = u->link;
						t += V->width;
						if (P->glue_sign == stretching)
						{
							if (V->stretch_order == P->glue_order)
								t += round(P->glue_set*V->stretch);
						}
						else 
							if (P->glue_sign == shrinking && V->shrink_order == P->glue_order)
								t -= round(P->glue_set*V->shrink);
						next(s);
						S = dynamic_cast<BoxNode*>(s);
						u->link = new BoxNode;
						u = u->link;
						t += S->width;
						auto U = dynamic_cast<BoxNode*>(u);
						if (mode == -vmode)
							U->width = S->width;
						else
						{
							u->type = vlist_node;
							U->height = S->height;
						}
					}
					if (mode == -vmode)
					{
						R->height = Q->height;
						R->depth = Q->depth;
						if (t == R->width)
						{
							R->glue_sign = 0;
							R->glue_order = 0;
							R->glue_set = 0.0;
						}
						else 
							if (t > R->width)
							{
								R->glue_sign = stretching;
								if (R->glue_stretch == 0)
									R->glue_set = 0.0;
								else
									R->glue_set = (t-R->width)/R->glue_stretch;
							}
							else
							{
								R->glue_order = R->glue_sign;
								R->glue_sign = shrinking;
								if (R->glue_shrink == 0)
									R->glue_set = 0.0;
								else 
									if (R->glue_order == 0 && R->width-t > R->glue_shrink)
										R->glue_set = 1.0;
									else
										R->glue_set = (R->width-t)/R->glue_shrink;
							}
						R->width = w;
						r->type = hlist_node;
					}
					else
					{
						R->width = Q->width;
						if (t == R->height)
						{
							R->glue_sign = 0;
							R->glue_order = 0;
							R->glue_set = 0.0;
						}
						else 
							if (t > R->height)
							{
								R->glue_sign = stretching;
								if (R->glue_stretch == 0)
									R->glue_set = 0.0;
								else
									R->glue_set = (t-R->height)/R->glue_stretch;
							}
							else
							{
								R->glue_order = R->glue_sign;
								R->glue_sign = shrinking;
								if (R->glue_shrink == 0)
									R->glue_set = 0.0;
								else 
									if (R->glue_order == 0 && R->height-t > R->glue_shrink)
										R->glue_set = 1.0;
									else
										R->glue_set = (R->height-t)/R->glue_shrink;
							}
						R->height = w;
						r->type = vlist_node;
					}
					dynamic_cast<BoxNode*>(r)->shift_amount = 0;
					if (u != hold_head)
					{
						u->link = r->link;
						r->link = hold_head->link;
						r = u;
					}
					next(r);
					next(r);
					next(s);
					next(s);
				} while (r);
			}
			else 
				if (q->type == rule_node)
				{
					auto Q = dynamic_cast<RuleNode*>(q);
					auto P = dynamic_cast<RuleNode*>(p);
					if (is_running(Q->width))
						Q->width = P->width;
					if (is_running(Q->height))
						Q->height = P->height;
					if (is_running(Q->depth))
						Q->depth = P->depth;
					if (o)
					{
						auto r = q->link;
						q->link = nullptr;
						q = hpack(q, 0, additional);
						dynamic_cast<BoxNode*>(q)->shift_amount = o;
						q->link = r;
						s->link = q;
					}
				}
		s = q;
		next(q);
	}
	flushnodelist(p);
	popalignment(loop);
	auto auxsave = aux;
	auto pp = head->link;
	q = tail;
	popnest(); 
	if (mode == mmode)
	{
		auto tk = doassignments();
		if (tk.cmd != math_shift)
			backerror(tk, "Missing $$ inserted", "Displays can use special alignments (like \\eqalignno)\nonly if nothing but the alignment itself is between $$'s.");
		else
		{
			tk = getxtoken();
			if (tk.cmd != math_shift)
				backerror(tk, "Display math should end with $$", "The `$' that I just saw supposedly matches a previous `$$'.\nSo I shall assume that you typed `$$' both times.");
		}
		popnest();
		tail_append(new PenaltyNode(pre_display_penalty()));
		tail_append(new GlueNode(above_display_skip_code));
		tail->link = pp;
		if (pp)
			tail = q;
		tail_append(new PenaltyNode(post_display_penalty()));
		tail_append(new GlueNode(below_display_skip_code));
		aux = auxsave;
		resumeafterdisplay(tk);
	}
	else
	{
		aux = auxsave;
		tail->link = pp;
		if (pp)
			tail = q;
		if (mode == vmode)
			buildpage();
	}
}
