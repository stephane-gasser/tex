#include "postlinebreak.h"
#include "deleteglueref.h"
#include "hpack.h"
#include "noeud.h"
#include "erreur.h"

static int broken_penalty(void) { return int_par(broken_penalty_code); }
static int club_penalty(void) { return int_par(club_penalty_code); }
static int inter_line_penalty(void) { return int_par(inter_line_penalty_code); }

auto prev_break = llink; //points to passive node that should precede this one
auto next_break = prev_break; //new name for |prev_break| after links are reversed
auto cur_break = rlink; //in passive node, points to position of this breakpoint

void postlinebreak(int finalwidowpenalty)
{
	bool discbreak, postdiscbreak;
	scaled curwidth, curindent;
	quarterword t;
	int pen;
	halfword curline;
	LinkedNode *q, *r, *s;
	q->num = break_node(bestbet);
	curp = 0;
	
	do //Reverse the links of the relevant passive nodes, setting |cur_p| to the first breakpoint
	{
		r = q;
		q->num = prev_break(q->num);
		next_break(r->num) = curp;
		curp = r->num;
	} while (q);
	curline = prev_graf+1;
	do //Justify the line ending at breakpoint |cur_p|, and append it to the current vertical list, together with associated penalties and other insertions
	{
		q->num = cur_break(curp);
		discbreak = false;
		postdiscbreak = false;
		if (q)
			if (type(q->num) == glue_node)
			{
				deleteglueref(glue_ptr(q->num));
				glue_ptr(q->num) = right_skip();
				subtype(q->num) = 9;
				add_glue_ref(right_skip());
			}
			else
			{
				if (type(q->num) == disc_node) //Change discretionary to compulsory and set |disc_break:=true|
				{
					t = replace_count(q->num);
					//Destroy the |t| nodes following |q|, and make |r| point to the following node@
					if (t == 0)
						r = q->link;
					else
					{
						r = q;
						while (t > 1)
						{
							r = r->link;
							t--;
						}
						s = r->link;
						r = s->link;
						s->link = nullptr;
						flushnodelist(q->link->num);
						replace_count(q->num) = 0;
					}
					if (post_break(q->num))
					{
						s->num = post_break(q->num);
						while (s->link)
							s = s->link;
						s->link = r;
						r->num = post_break(q->num);
						post_break(q->num) = 0;
						postdiscbreak = true;
					}
					if (pre_break(q->num))
					{
						s->num = pre_break(q->num);
						q->link = s;
						while (s->link)
							s = s->link;
						pre_break(q->num) = 0;
						q = s;
					}
					q->link = r;
					discbreak = true;
					}
					else 
						if (type(q->num) == math_node || type(q->num) == kern_node)
							width(q->num) = 0;
				r->num = newparamglue(right_skip_code);
				r->link = q->link;
				q->link = r;
				q = r;
			}
		else
		{
			q = temp_head;
			while (q->link)
				q = q->link;
			r->num = newparamglue(right_skip_code);
			r->link = q->link;
			q->link = r;
			q = r;
		}
		r = q->link;
		q->link = 0;
		q = temp_head->link;
		temp_head->link = r;
		if (left_skip())
		{
			r->num = newparamglue(left_skip_code);
			r->link = q;
			q = r;
		}
		if (curline > lastspecialline)
		{
			curwidth = secondwidth;
			curindent = secondindent;
		}
		else 
			if (par_shape_ptr() == 0)
			{
				curwidth = firstwidth;
				curindent = firstindent;
			}
			else
			{
				curwidth = mem[par_shape_ptr()+2*curline].int_;
				curindent = mem[par_shape_ptr()+2*curline-1].int_;
			}
		adjusttail = adjust_head;
		justbox = hpack(q->num, curwidth, 0);
		shift_amount(justbox) = curindent;
		appendtovlist(justbox);
		if (adjust_head != adjusttail)
		{
			link(tail) = link(adjust_head);
			tail = adjusttail;
		}
		adjusttail = 0;
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
				r->num = newpenalty(pen);
				tail_append(r->num);
			}
		}
		curline++;
		curp = next_break(curp);
		if (curp)
			if (!postdiscbreak)
			{
				r = temp_head;
				while (true)
				{
					q = r->link;
					if (q->num == cur_break(curp))
						break;
					if (q->is_char_node())
						break;
					if (type(q->num) < math_node) // non_discardable
						break;
					if (type(q->num) == kern_node)
						if (subtype(q->num) != explicit_)
							break;
					r = q; //now |type(q)=glue_node|, |kern_node|, |math_node| or |penalty_node|
				}
				if (r != temp_head)
				{
					r->link = nullptr;
					flushnodelist(temp_head->link->num);
					temp_head->link = q;
				}
			}
	} while (curp);
	if (curline != bestline || temp_head->link)
		confusion("line breaking");
	prev_graf = bestline-1;
}
