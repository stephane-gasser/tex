#include "fincol.h"
#include "noeud.h"
#include "impression.h"
#include "erreur.h"
#include "unsave.h"
#include "boite.h"
#include "initspan.h"
#include "popnest.h"
#include "lecture.h"
#include "initcol.h"
#include "texte.h"

bool fincol(Token t, halfword &loop)
{
	halfword s;
	BoxNode *u;
	LinkedNode *q;
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
			q->link = new BoxNode;
			p = q->link;
			info(p->num) = end_span->num;
			width(p->num) = null_flag;
			loop = link(loop);
			q = hold_head;
			auto r = u_part(loop);
			while (r)
			{
				q->link = new TokenNode(info(r));
				q = dynamic_cast<TokenNode*>(q->link);
				r = link(r);
			}
			q->link = nullptr;
			u_part(p->num) = hold_head->link->num;
			q = hold_head;
			r = v_part(loop);
			while (r)
			{
				q->link = new TokenNode(info(r));
				q = dynamic_cast<TokenNode*>(q->link);
				r = link(r);
			}
			q->link = nullptr;
			v_part(p->num) = hold_head->link->num;
			loop = link(loop);
			GlueNode *Loop;
			Loop->num = loop;
			p->link = new GlueNode(Loop->glue_ptr);
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
			u = hpack(head->link, 0, additional);
			w = u->width;
			curtail->num = adjusttail;
			adjusttail = 0;
		}
		else
		{
			u = vpackage(head->link, 0, additional, 0);
			w = u->height;
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
				q = q->link;
			if (q->link->link->num > n)
			{
				s = getnode(span_node_size);
				info(s) = info(q->num);
				link(s) = n;
				info(q->num) = s;
				width(s) = w;
			}
			else 
				if (width(info(q->num)) < w)
					width(info(q->num)) = w;
		}
		else 
			if (w > width(curalign))
				width(curalign) = w;
		u->type = unset_node;
		span_count(u->num) = n;
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
		u->glue_order = o;
		glue_stretch(u->num) = totalstretch[o];
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
		u->glue_sign = o;
		glue_shrink(u->num) = totalshrink[o];
		popnest();
		tail->link = u;
		tail = u;
		GlueNode *Curalign;
		Curalign->num = curalign;
		auto G = new GlueNode(Curalign->glue_ptr);
		G->subtype = tab_skip_code+1;
		tail_append(G);
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
