#include "postlinebreak.h"
#include "deleteglueref.h"
#include "flushnodelist.h"
#include "newparamglue.h"
#include "hpack.h"
#include "appendtovlist.h"
#include "newpenalty.h"
#include "confusion.h"

void postlinebreak(int finalwidowpenalty)
{
	halfword q, r, s;
	bool discbreak, postdiscbreak;
	scaled curwidth, curindent;
	quarterword t;
	int pen;
	halfword curline;
	q = link(bestbet+1);
	curp = 0;
	do
	{
		r = q;
		q = info(q+1);
		info(r+1) = curp;
		curp = r;
	} while (q);
	curline = curlist.pgfield+1;
	do
	{
		q = link(curp+1);
		discbreak = false;
		postdiscbreak = false;
		if (q)
			if (type(q) == 10)
			{
				deleteglueref(info(q+1));
				info(q+1) = right_skip();
				subtype(q) = 9;
				link(right_skip())++;
			}
			else
			{
				if (type(q) == 7)
				{
					t = subtype(q);
					if (t == 0)
						r = link(q);
					else
					{
						r = q;
						while (t > 1)
						{
							r = link(r);
							t--;
						}
						s = link(r);
						r = link(s);
						link(s) = 0;
						flushnodelist(link(q));
						subtype(q) = 0;
					}
					if (link(q+1))
					{
						s = link(q+1);
						while (link(s))
							s = link(s);
						link(s) = r;
						r = link(q+1);
						link(q+1) = 0;
						postdiscbreak = true;
					}
					if (info(q+1))
					{
						s = info(q+1);
						link(q) = s;
						while (link(s))
							s = link(s);
						info(q+1) = 0;
						q = s;
					}
					link(q) = r;
					discbreak = true;
					}
					else 
						if (type(q) == 9 || type(q) == 11)
							mem[q+1].int_ = 0;
				r = newparamglue(8);
				link(r) = link(q);
				link(q) = r;
				q = r;
			}
		else
		{
			q = temp_head;
			while (link(q))
				q = link(q);
			r = newparamglue(8);
			link(r) = link(q);
			link(q) = r;
			q = r;
		}
		r = link(q);
		link(q) = 0;
		q = link(temp_head);
		link(temp_head) = r;
		if (left_skip())
		{
			r = newparamglue(7);
			link(r) = q;
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
		justbox = hpack(q, curwidth, 0);
		mem[justbox+4].int_ = curindent;
		appendtovlist(justbox);
		if (adjust_head != adjusttail)
		{
			link(curlist.tailfield) = link(adjust_head);
			curlist.tailfield = adjusttail;
		}
		adjusttail = 0;
		if (curline+1 != bestline)
		{
			pen = int_par(inter_line_penalty_code);
			if (curline == curlist.pgfield+1)
				pen += int_par(club_penalty_code);
			if (curline+2 == bestline)
				pen += finalwidowpenalty;
			if (discbreak)
				pen += int_par(broken_penalty_code);
			if (pen)
			{
				r = newpenalty(pen);
				link(curlist.tailfield) = r;
				curlist.tailfield = r;
			}
		}
		curline++;
		curp = info(curp+1);
		if (curp)
			if (not postdiscbreak)
			{
				r = temp_head;
				while (true)
				{
					q = link(r);
					if (q == link(curp+1))
						break;
					if (q >= himemmin)
						break;
					if (type(q) < 9)
						break;
					if (type(q) == 11)
						if (subtype(q) != 1)
							break;
					r = q;
				}
				if (r != temp_head)
				{
					link(r) = 0;
					flushnodelist(link(temp_head));
					link(temp_head) = q;
				}
			}
	} while (curp);
	if (curline != bestline || link(temp_head))
		confusion(938); //line breaking
	curlist.pgfield = bestline-1;
}
