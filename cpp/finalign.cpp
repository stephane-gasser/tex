#include "finalign.h"
#include "confusion.h"
#include "unsave.h"
#include "flushlist.h"
#include "deleteglueref.h"
#include "freenode.h"
#include "hpack.h"
#include "vpackage.h"
#include "newglue.h"
#include "newnullbox.h"
#include "flushnodelist.h"
#include "popalignment.h"
#include "popnest.h"
#include "printnl.h"
#include "doassignments.h"
#include "backerror.h"
#include "print.h"
#include "getxtoken.h"
#include "resumeafterdisplay.h"
#include "buildpage.h"
#include "newpenalty.h"
#include "newparamglue.h"
#include <cmath>
#include "texte.h"

void finalign(void)
{
	halfword p, q, r, s, u, v;
	scaled t, w;
	scaled o;
	halfword n;
	scaled rulesave;
	memoryword auxsave;
	if (curgroup != 6)
		confusion("align1");
	unsave();
	if (curgroup != 6)
		confusion("align0"); 
	unsave();
	if (nest[nestptr-1].modefield == mmode)
		o = display_indent();
	else
		o = 0;
	q = link(preamble());
	do
	{
		flushlist(u_part(q));
		flushlist(v_part(q));
		p = link(link(q));
		if (is_running(width(q)))
		{
			width(q) = 0;
			r = link(q);
			s = info(r+1);
			if (s)
			{
				link(zero_glue)++;
				deleteglueref(s);
				info(r+1) = 0;
			}
		}
		if (info(q) != end_span)
		{
			t = width(q)+width(info(link(q)+1));
			r = info(q);
			s = end_span;
			info(s) = p;
			n = 1;
			do
			{
				width(r) -= t;
				u = info(r);
				while (link(r) > n)
				{
					s = info(s);
					n = link(info(s))+1;
				}
				if (link(r) < n)
				{
					info(r) = info(s);
					info(s) = r;
					link(r)--;
					s = r;
				}
				else
				{
					if (width(r) > width(info(s)+1))
						width(info(s)+1) = width(r);
					freenode(r, span_node_size);
				}
				r = u;
			} while (r != end_span);
		}
		type(q) = unset_node;
		span_count(q) = 0;
		height(q) = 0;
		depth(q) = 0;
		glue_order(q) = 0;
		glue_sign(q) = 0;
		glue_stretch(q) = 0;
		glue_shrink(q) = 0;
		q = p;
	} while (q);
	saveptr -= 2;
	packbeginline = -mode_line;
	if (mode == -vmode)
	{
		rulesave = overfull_rule();
		overfull_rule() = 0;
		p = hpack(preamble(), savestack[saveptr+1].int_, savestack[saveptr].int_);
		overfull_rule() = rulesave;
	}
	else
	{
		q = link(preamble());
		do
		{
			height(q) = width(q);
			width(q) = 0;
			q = link(link(q));
		} while (q);
		p = vpack(preamble(), savestack[saveptr+1].int_, savestack[saveptr+0].int_);
		q = link(preamble());
		do
		{
			width(q) = height(q);
			height(q) = 0;
			q = link(link(q));
		} while (q);
	}
	packbeginline = 0;
	q = link(head);
	s = head;
	while (q)
	{
		if (q < himemmin)
			if (type(q) == unset_node)
			{
				if (mode == -vmode)
				{
					type(q) = hlist_node;
					width(q) = width(p);
				}
				else
				{
					type(q) = vlist_node;
					height(q) = height(p);
				}
				glue_order(q) = glue_order(p);
				glue_sign(q) = glue_sign(p);
				glue_set(q) = glue_set(p);
				shift_amount(q) = o;
				r = link(list_ptr(q));
				s = link(list_ptr(p));
				do
				{
					n = span_count(r);
					t = width(s);
					w = t;
					u = hold_head;
					while (n > 0)
					{
						n--;
						s = link(s);
						v = info(s+1);
						link(u) = newglue(v);
						u = link(u);
						subtype(u) = 12;
						t += width(v);
						if (glue_sign(p) == stretching)
						{
							if (type(v) == glue_order(p))
								t += round(glue_set(p)*depth(v));
						}
						else 
							if (glue_sign(p) == shrinking && subtype(v) == glue_order(p))
								t -= round(glue_set(p)*height(v));
						s = link(s);
						link(u) = newnullbox();
						u = link(u);
						t += width(s);
						if (mode == -vmode)
							width(u) = width(s);
						else
						{
							type(u) = vlist_node;
							height(u) = height(s);
						}
					}
					if (mode == -vmode)
					{
						height(r) = height(q);
						depth(r) = depth(q);
						if (t == width(r))
						{
							glue_sign(r) = 0;
							glue_order(r) = 0;
							glue_set(r) = 0.0;
						}
						else 
							if (t > width(r))
							{
								glue_sign(r) = stretching;
								if (glue_stretch(r) == 0)
									glue_set(r) = 0.0;
								else
									glue_set(r) = (t-width(r))/glue_stretch(r);
							}
							else
							{
								glue_order(r) = glue_sign(r);
								glue_sign(r) = shrinking;
								if (glue_shrink(r) == 0)
									glue_set(r) = 0.0;
								else 
									if (glue_order(r) == 0 && width(r)-t > glue_shrink(r))
										glue_set(r) = 1.0;
									else
										glue_set(r) = (width(r)-t) / glue_shrink(r);
							}
						width(r) = w;
						type(r) = 0;
					}
					else
					{
						width(r) = width(q);
						if (t == height(r))
						{
							glue_sign(r) = 0;
							glue_order(r) = 0;
							glue_set(r) = 0.0;
						}
						else 
							if (t > height(r))
							{
								glue_sign(r) = stretching;
								if (glue_stretch(r) == 0)
									glue_set(r) = 0.0;
								else
									glue_set(r) = (t-height(r)) / glue_stretch(r);
							}
							else
							{
								glue_order(r) = glue_sign(r);
								glue_sign(r) = shrinking;
								if (glue_shrink(r) == 0)
									glue_set(r) = 0.0;
								else 
									if (glue_order(r) == 0 && height(r)-t > glue_shrink(r))
										glue_set(r) = 1.0;
									else
										glue_set(r) = (height(r)-t) / glue_shrink(r);
							}
						height(r) = w;
						type(r) = vlist_node;
					}
					shift_amount(r) = 0;
					if (u != hold_head)
					{
						link(u) = link(r);
						link(r) = link(hold_head);
						r = u;
					}
					r = link(link(r));
					s = link(link(s));
				} while (r);
			}
			else 
				if (type(q) == rule_node)
				{
					if (is_running(width(q)))
						width(q) = width(p);
					if (is_running(height(q)))
						height(q) = height(p);
					if (is_running(depth(q)))
						depth(q) = depth(p);
					if (o)
					{
						r = link(q);
						link(q) = 0;
						q = hpack(q, 0, additional);
						shift_amount(q) = o;
						link(q) = r;
						link(s) = q;
					}
				}
		s = q;
		q = link(q);
	}
	flushnodelist(p);
	popalignment();
	auxsave = aux;
	p = link(head);
	q = tail;
	popnest();
	if (mode == mmode)
	{
		doassignments();
		if (curcmd != math_shift)
		{
			printnl("! ");
			print("Missing $$ inserted"); 
			helpptr = 2;
			helpline[1] = "Displays can use special alignments (like \\eqalignno)";
			helpline[0] = "only if nothing but the alignment itself is between $$'s.";
			backerror();
		}
		else
		{
			getxtoken();
			if (curcmd != math_shift)
			{
				printnl("! ");
				print("Display math should end with $$");
				helpptr = 2;
				helpline[1] = "The `$' that I just saw supposedly matches a previous `$$'.";
				helpline[0] = "So I shall assume that you typed `$$' both times.";
				backerror();
			}
		}
		popnest();
		tail_append(newpenalty(pre_display_penalty()));
		tail_append(newparamglue(3));
		link(tail) = p;
		if (p)
			tail = q;
		tail_append(newpenalty(post_display_penalty()));
		tail_append(newparamglue(4));
		aux = auxsave;
		resumeafterdisplay();
	}
	else
	{
		aux = auxsave;
		link(tail) = p;
		if (p)
			tail = q;
		if (mode == vmode)
			buildpage();
	}
}
