#include "fincol.h"
#include "noeud.h"
#include "impression.h"
#include "erreur.h"
#include "unsave.h"
#include "hpack.h"
#include "vpackage.h"
#include "initspan.h"
#include "popnest.h"
#include "lecture.h"
#include "initcol.h"
#include "texte.h"

bool fincol(Token t, halfword &loop)
{
	halfword p, q, r, s, u;
	scaled w;
	glueord o;
	halfword n;
	if (curalign == 0)
		confusion("endv");
	q = link(curalign);
	if (q == 0)
		confusion("endv");
	if (alignstate < 500000)
		fatalerror("(interwoven alignment preambles are not allowed)");
	p = link(q);
	if (p == 0 && extra_info(curalign) < cr_code)
		if (loop)
		{
			link(q) = newnullbox();
			p = link(q);
			info(p) = end_span;
			width(p) = null_flag;
			loop = link(loop);
			q = hold_head;
			r = u_part(loop);
			while (r)
			{
				link(q) = getavail();
				q = link(q);
				info(q) = info(r);
				r = link(r);
			}
			link(q) = 0;
			u_part(p) = link(hold_head);
			q = hold_head;
			r = v_part(loop);
			while (r)
			{
				link(q) = getavail();
				q = link(q);
				info(q) = info(r);
				r = link(r);
			}
			link(q) = 0;
			v_part(p) = link(hold_head);
			loop = link(loop);
			link(p) = newglue(glue_ptr(loop));
		}
		else
		{
			error("Extra alignment tab has been changed to "+esc("cr"), "You have given more \\span or & marks than there were\nin the preamble to the \\halign or \\valign now in progress.\nSo I'll assume that you meant to type \\cr instead.");
			extra_info(curalign) = cr_code;
		}
	if (extra_info(curalign) != span_code)
	{
		unsave();
		newsavelevel(6);
		if (mode == -hmode)
		{
			adjusttail = curtail;
			u = hpack(link(head), 0, additional);
			w = width(u);
			curtail = adjusttail;
			adjusttail = 0;
		}
		else
		{
			u = vpackage(link(head), 0, additional, 0);
			w = height(u);
		}
		n = 0;
		if (curspan != curalign)
		{
			q = curspan;
			do
			{
				n++;
				q = link(link(q));
			} while (q != curalign);
			if (n > 255)
				confusion("256 spans");
			q = curspan;
			while (link(link(q)) < n)
				q = link(q);
			if (link(link(q)) > n)
			{
				s = getnode(span_node_size);
				info(s) = info(q);
				link(s) = n;
				info(q) = s;
				width(s) = w;
			}
			else 
				if (width(info(q)) < w)
					width(info(q)) = w;
		}
		else 
			if (w > width(curalign))
				width(curalign) = w;
		type(u) = unset_node;
		span_count(u) = n;
		if (totalstretch[3])
			o = 3;
			else 
				if (totalstretch[2])
					o = 2;
				else 
					if (totalstretch[1])
						o = 1;
					else
						o = 0;
		glue_order(u) = o;
		glue_stretch(u) = totalstretch[o];
		if (totalshrink[3])
			o = 3;
		else 
			if (totalshrink[2])
				o = 2;
			else 
				if (totalshrink[1])
					o = 1;
				else
					o = 0;
		glue_sign(u) = o;
		glue_shrink(u) = totalshrink[o];
		popnest();
		link(tail) = u;
		tail = u;
		tail_append(newglue(glue_ptr(link(curalign))));
		subtype(tail) = tab_skip_code+1;
		if (extra_info(curalign) >= cr_code)
			return true;
		initspan(p);
	}
	alignstate = 1000000;
	t = getXTokenSkipSpace();
	curalign = p;
	initcol(t);
	return false;
}
