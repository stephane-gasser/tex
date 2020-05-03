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

void finalign(void)
{
	halfword p, q, r, s, u, v;
	scaled t, w;
	scaled o;
	halfword n;
	scaled rulesave;
	memoryword auxsave;
	if (curgroup != 6)
		confusion(914); //align1
	unsave();
	if (curgroup != 6)
		confusion(915); //align0
	unsave();
	if (nest[nestptr-1].modefield == mmode)
		o = dimen_par(display_indent_code);
	else
		o = 0;
	q = link(link(align_head));
	do
	{
		flushlist(mem[q+3].int_);
		flushlist(mem[q+2].int_);
		p = link(link(q));
		if (mem[q+1].int_ == -0x40'00'00'00)
		{
			mem[q+1].int_ = 0;
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
			t = mem[q+1].int_+mem[info(link(q)+1)+1].int_;
			r = info(q);
			s = end_span;
			info(s) = p;
			n = 1;
			do
			{
				mem[r+1].int_ -= t;
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
					if (mem[r+1].int_ > mem[info(s)+1].int_)
						mem[info(s)+1].int_ = mem[r+1].int_;
					freenode(r, 2);
				}
				r = u;
			} while (r != end_span);
		}
		type(q) = 13;
		subtype(q) = 0;
		mem[q+3].int_ = 0;
		mem[q+2].int_ = 0;
		subtype(q+5) = 0;
		type(q+5) = 0;
		mem[q+6].int_ = 0;
		mem[q+4].int_ = 0;
		q = p;
	} while (q);
	saveptr -= 2;
	packbeginline = -mode_line;
	if (mode == -vmode)
	{
		rulesave = dimen_par(overfull_rule_code);
		dimen_par(overfull_rule_code) = 0;
		p = hpack(link(align_head), savestack[saveptr+1].int_, savestack[saveptr].int_);
		dimen_par(overfull_rule_code) = rulesave;
	}
	else
	{
		q = link(link(align_head));
		do
		{
			mem[q+3].int_ = mem[q+1].int_;
			mem[q+1].int_ = 0;
			q = link(link(q));
		} while (q);
		p = vpackage(link(align_head), savestack[saveptr+1].int_, savestack[saveptr+0].int_, max_dimen);
		q = link(link(align_head));
		do
		{
			mem[q+1].int_ = mem[q+3].int_;
			mem[q+3].int_ = 0;
			q = link(link(q));
		} while (q);
	}
	packbeginline = 0;
	q = link(head);
	s = head;
	while (q)
	{
		if (q < himemmin)
			if (type(q) == 13)
			{
				if (mode == -vmode)
				{
					type(q) = 0;
					mem[q+1].int_ = mem[p+1].int_;
				}
				else
				{
					type(q) = 1;
					mem[q+3].int_ = mem[p+3].int_;
				}
				subtype(q+5) = subtype(p+5);
				type(q+5) = type(p+5);
				mem[q+6].gr = mem[p+6].gr;
				mem[q+4].int_ = o;
				r = link(link(q+5));
				s = link(link(p+5));
				do
				{
					n = subtype(r);
					t = mem[s+1].int_;
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
						t += mem[v+1].int_;
						if (type(p+5) == 1)
						{
							if (type(v) == subtype(p+5))
								t += round(mem[p+6].gr*mem[v+2].int_);
						}
						else 
							if (type(p+5) == 2 && subtype(v) == subtype(p+5))
								t -round(mem[p+6].gr*mem[v+3].int_);
						s = link(s);
						link(u) = newnullbox();
						u = link(u);
						t += mem[s+1].int_;
						if (mode == -vmode)
							mem[u+1].int_ = mem[s+1].int_;
						else
						{
							type(u) = 1;
							mem[u+3].int_ = mem[s+1].int_;
						}
					}
					if (mode == -vmode)
					{
						mem[r+3].int_ = mem[q+3].int_;
						mem[r+2].int_ = mem[q+2].int_;
						if (t == mem[r+1].int_)
						{
							type(r+5) = 0;
							subtype(r+5) = 0;
							mem[r+6].gr = 0.0;
						}
						else 
							if (t > mem[r+1].int_)
							{
								type(r+5) = 1;
								if (mem[r+6].int_ == 0)
									mem[r+6].gr = 0.0;
								else
									mem[r+6].gr = (t-mem[r+1].int_) / mem[r+6].int_;
							}
							else
							{
							subtype(r+5) = type(r+5);
							type(r+5) = 2;
							if (mem[r+4].int_ == 0)
								mem[r+6].gr = 0.0;
							else 
								if (subtype(r+5) == 0 && mem[r+1].int_-t > mem[r+4].int_)
									mem[r+6].gr = 1.0;
								else
									mem[r+6].gr = (mem[r+1].int_-t) / mem[r+4].int_;
							}
						mem[r+1].int_ = w;
						type(r) = 0;
					}
					else
					{
						mem[r+1].int_ = mem[q+1].int_;
						if (t == mem[r+3].int_)
						{
							type(r+5) = 0;
							subtype(r+5) = 0;
							mem[r+6].gr = 0.0;
						}
						else 
							if (t > mem[r+3].int_)
							{
								type(r+5) = 1;
								if (mem[r+6].int_ == 0)
									mem[r+6].gr = 0.0;
								else
									mem[r+6].gr = (t-mem[r+3].int_) / mem[r+6].int_;
							}
							else
							{
								subtype(r+5) = type(r+5);
								type(r+5) = 2;
								if (mem[r+4].int_ == 0)
									mem[r+6].gr = 0.0;
								else 
									if (subtype(r+5) == 0 && mem[r+3].int_-t > mem[r+4].int_)
										mem[r+6].gr = 1.0;
									else
										mem[r+6].gr = (mem[r+3].int_-t) / mem[r+4].int_;
							}
						mem[r+3].int_ = w;
						type(r) = 1;
					}
					mem[r+4].int_ = 0;
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
				if (type(q) == 2)
				{
					if ((mem[q+1].int_ == -0x40'00'00'00))
						mem[q+1].int_ = mem[p+1].int_;
					if ((mem[q+3].int_ == -0x40'00'00'00))
						mem[q+3].int_ = mem[p+3].int_;
					if ((mem[q+2].int_ == -0x40'00'00'00))
						mem[q+2].int_ = mem[p+2].int_;
					if (o != 0)
					{
						r = link(q);
						link(q) = 0;
						q = hpack(q, 0, 1);
						mem[q+4].int_ = o;
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
			printnl(262); //! 
			print(1169); //Missing $$ inserted
			helpptr = 2;
			helpline[1] = 894; //Displays can use special alignments (like \eqalignno)
			helpline[0] = 895; //only if nothing but the alignment itself is between $$'s.
			backerror();
		}
		else
		{
			getxtoken();
			if (curcmd != math_shift)
			{
				printnl(262); //! 
				print(1165); //Display math should end with $$
				helpptr = 2;
				helpline[1] = 1166; //The `$' that I just saw supposedly matches a previous `$$'.
				helpline[0] = 1167; //So I shall assume that you typed `$$' both times.
				backerror();
			}
		}
		popnest();
		tail_append(newpenalty(int_par(pre_display_penalty_code)));
		tail_append(newparamglue(3));
		link(tail) = p;
		if (p)
			tail = q;
		tail_append(newpenalty(int_par(post_display_penalty_code)));
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
