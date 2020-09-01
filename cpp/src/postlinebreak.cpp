#include "postlinebreak.h"
#include "deleteglueref.h"
#include "boite.h"
#include "noeud.h"
#include "erreur.h"
#include "equivalent.h"

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
