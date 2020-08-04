#include "finalign.h"
#include "unsave.h"
#include "deleteglueref.h"
#include "noeud.h"
#include "hpack.h"
#include "vpackage.h"
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
#include "texte.h"

void finalign(halfword &loop)
{
	LinkedNode *p, *u, *v;
	scaled t, w;
	halfword n;
	if (curgroup != 6)
		confusion("align1");
	unsave();
	if (curgroup != 6)
		confusion("align0"); 
	unsave();
	scaled o = nest[nestptr-1].modefield == mmode ? display_indent() : 0;
	auto q = preamble->link;
	do
	{
		flushlist(u_part(q->num)); 
		flushlist(v_part(q->num));
		p = q->link->link;
		if (is_running(width(q->num)))
		{
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
			t = width(q->num)+dynamic_cast<GlueNode*>(q->link)->glue_ptr->width;
			LinkedNode *r, *s;
			r->num = info(q->num);
			s = end_span;
			info(s->num) = p->num;
			n = 1;
			do
			{
				width(r->num) -= t;
				u->num = info(r->num);
				while (r->link->num > n)
				{
					s->num = info(s->num);
					n = link(info(s->num))+1;
				}
				if (r->link->num < n)
				{
					info(r->num) = info(s->num);
					info(s->num) = r->num;
					r->link->num--;
					s = r;
				}
				else
				{
					if (width(r->num) > width(info(s->num)))
						width(info(s->num)) = width(r->num);
					freenode(r->num, span_node_size);
				}
				r = u;
			} while (r != end_span);
		}
		q->type = unset_node;
		span_count(q->num) = 0;
		height(q->num) = 0;
		depth(q->num) = 0;
		glue_order(q->num) = 0;
		glue_sign(q->num) = 0;
		glue_stretch(q->num) = 0;
		glue_shrink(q->num) = 0;
		q = p;
	} while (q);
	saveptr -= 2;
	packbeginline = -mode_line;
	if (mode == -vmode)
	{
		scaled rulesave = overfull_rule();
		overfull_rule() = 0;
		p->num = hpack(preamble->num, saved(1), saved(0));
		overfull_rule() = rulesave;
	}
	else
	{
		q = preamble->link;
		do
		{
			height(q->num) = width(q->num);
			width(q->num) = 0;
			q = q->link->link;
		} while (q);
		p->num = vpack(preamble->num, saved(1), saved(0));
		q = preamble->link;
		do
		{
			width(q->num) = height(q->num);
			height(q->num) = 0;
			q = q->link->link;
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
				if (mode == -vmode)
				{
					q->type = hlist_node;
					width(q->num) = width(p->num);
				}
				else
				{
					q->type = vlist_node;
					height(q->num) = height(p->num);
				}
				glue_order(q->num) = glue_order(p->num);
				glue_sign(q->num) = glue_sign(p->num);
				glue_set(q->num) = glue_set(p->num);
				shift_amount(q->num) = o;
				LinkedNode *r;
				r->num = link(list_ptr(q->num));
				s->num = link(list_ptr(p->num));
				do
				{
					n = span_count(r->num);
					t = width(s->num);
					w = t;
					u = hold_head;
					while (n > 0)
					{
						n--;
						s = s->link;
						auto V = dynamic_cast<GlueNode*>(s)->glue_ptr;
						auto g = new GlueNode(V);
						g->subtype = tab_skip_code+1;
						u->link = g;
						u = u->link;
						t += V->width;
						if (glue_sign(p->num) == stretching)
						{
							if (V->stretch_order == glue_order(p->num))
								t += round(glue_set(p->num)*V->stretch);
						}
						else 
							if (glue_sign(p->num) == shrinking && V->shrink_order == glue_order(p->num))
								t -= round(glue_set(p->num)*V->shrink);
						s = s->link;
						u->link = new BoxNode;
						u = u->link;
						t += width(s->num);
						if (mode == -vmode)
							width(u->num) = width(s->num);
						else
						{
							u->type = vlist_node;
							height(u->num) = height(s->num);
						}
					}
					if (mode == -vmode)
					{
						height(r->num) = height(q->num);
						depth(r->num) = depth(q->num);
						if (t == width(r->num))
						{
							glue_sign(r->num) = 0;
							glue_order(r->num) = 0;
							glue_set(r->num) = 0.0;
						}
						else 
							if (t > width(r->num))
							{
								glue_sign(r->num) = stretching;
								if (glue_stretch(r->num) == 0)
									glue_set(r->num) = 0.0;
								else
									glue_set(r->num) = (t-width(r->num))/glue_stretch(r->num);
							}
							else
							{
								glue_order(r->num) = glue_sign(r->num);
								glue_sign(r->num) = shrinking;
								if (glue_shrink(r->num) == 0)
									glue_set(r->num) = 0.0;
								else 
									if (glue_order(r->num) == 0 && width(r->num)-t > glue_shrink(r->num))
										glue_set(r->num) = 1.0;
									else
										glue_set(r->num) = (width(r->num)-t) / glue_shrink(r->num);
							}
						width(r->num) = w;
						r->type = 0;
					}
					else
					{
						width(r->num) = width(q->num);
						if (t == height(r->num))
						{
							glue_sign(r->num) = 0;
							glue_order(r->num) = 0;
							glue_set(r->num) = 0.0;
						}
						else 
							if (t > height(r->num))
							{
								glue_sign(r->num) = stretching;
								if (glue_stretch(r->num) == 0)
									glue_set(r->num) = 0.0;
								else
									glue_set(r->num) = (t-height(r->num)) / glue_stretch(r->num);
							}
							else
							{
								glue_order(r->num) = glue_sign(r->num);
								glue_sign(r->num) = shrinking;
								if (glue_shrink(r->num) == 0)
									glue_set(r->num) = 0.0;
								else 
									if (glue_order(r->num) == 0 && height(r->num)-t > glue_shrink(r->num))
										glue_set(r->num) = 1.0;
									else
										glue_set(r->num) = (height(r->num)-t) / glue_shrink(r->num);
							}
						height(r->num) = w;
						type(r->num) = vlist_node;
					}
					shift_amount(r->num) = 0;
					if (u != hold_head)
					{
						u->link = r->link;
						r->link = hold_head->link;
						r = u;
					}
					r = r->link->link;
					s = s->link->link;
				} while (r);
			}
			else 
				if (q->type == rule_node)
				{
					if (is_running(width(q->num)))
						width(q->num) = width(p->num);
					if (is_running(height(q->num)))
						height(q->num) = height(p->num);
					if (is_running(depth(q->num)))
						depth(q->num) = depth(p->num);
					if (o)
					{
						auto r = q->link;
						q->link = nullptr;
						q->num = hpack(q->num, 0, additional);
						shift_amount(q->num) = o;
						q->link = r;
						s->link = q;
					}
				}
		s = q;
		q = q->link;
	}
	flushnodelist(p);
	popalignment(loop);
	auto auxsave = aux;
	p = head->link;
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
		tail->link = p;
		if (p)
			tail = q;
		tail_append(new PenaltyNode(post_display_penalty()));
		tail_append(new GlueNode(below_display_skip_code));
		aux = auxsave;
		resumeafterdisplay(tk);
	}
	else
	{
		aux = auxsave;
		tail->link = p;
		if (p)
			tail = q;
		if (mode == vmode)
			buildpage();
	}
}
