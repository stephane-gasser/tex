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
	halfword s, u;
	#warning pas le bon type ??
	TokenNode *q;
	scaled w;
	glueord o;
	halfword n;
	if (curalign == 0)
		confusion("endv");
	q->num = link(curalign);
	if (q == nullptr)
		confusion("endv");
	if (alignstate < 500000)
		fatalerror("(interwoven alignment preambles are not allowed)");
	auto p = q->link;
	if (p == nullptr && extra_info(curalign) < cr_code)
		if (loop)
		{
			q->link->num = newnullbox();
			p = q->link;
			info(p->num) = end_span;
			width(p->num) = null_flag;
			loop = link(loop);
			q->num = hold_head;
			auto r = u_part(loop);
			while (r)
			{
				q->link = new TokenNode(info(r));
				q = dynamic_cast<TokenNode*>(q->link);
				r = link(r);
			}
			q->link = 0;
			u_part(p->num) = link(hold_head);
			q->num = hold_head;
			r = v_part(loop);
			while (r)
			{
				q->link = new TokenNode(info(r));
				q = dynamic_cast<TokenNode*>(q->link);
				r = link(r);
			}
			q->link = nullptr;
			v_part(p->num) = link(hold_head);
			loop = link(loop);
			p->link->num = newglue(glue_ptr(loop));
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
			adjusttail = curtail->num;
			u = hpack(head->link->num, 0, additional);
			w = width(u);
			curtail->num = adjusttail;
			adjusttail = 0;
		}
		else
		{
			u = vpackage(head->link->num, 0, additional, 0);
			w = height(u);
		}
		n = 0;
		if (curspan != curalign)
		{
			q->num = curspan;
			do
			{
				n++;
				q = dynamic_cast<TokenNode*>(q->link->link);
			} while (q->num != curalign);
			if (n > 255)
				confusion("256 spans");
			q->num = curspan;
			while (q->link->link->num < n)
				q = dynamic_cast<TokenNode*>(q->link);
			if (q->link->link->num > n)
			{
				s = getnode(span_node_size);
				info(s) = q->token;
				link(s) = n;
				q->token = s;
				width(s) = w;
			}
			else 
				if (width(q->token) < w)
					width(q->token) = w;
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
		tail->link->num = u;
		tail->num = u;
		tail_append(newglue(glue_ptr(link(curalign))));
		subtype(tail->num) = tab_skip_code+1;
		if (extra_info(curalign) >= cr_code)
			return true;
		initspan(p->num);
	}
	alignstate = 1000000;
	t = getXTokenSkipSpace();
	curalign = p->num;
	initcol(t);
	return false;
}
