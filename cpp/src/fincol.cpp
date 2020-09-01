#include "fincol.h"
#include "noeud.h"
#include "impression.h"
#include "erreur.h"
#include "sauvegarde.h"
#include "boite.h"
#include "initspan.h"
#include "popnest.h"
#include "lecture.h"
#include "initcol.h"
#include "texte.h"

bool fincol(Token t, AlignRecordNode* &loop)
{
	BoxNode *u;
	scaled w;
	glueord o;
	halfword n;
	if (curalign == nullptr)
		confusion("endv");
	auto q = curalign->link;
	if (q == nullptr)
		confusion("endv");
	if (alignstate < 500000)
		fatalerror("(interwoven alignment preambles are not allowed)");
	auto p = dynamic_cast<AlignRecordNode*>(q->link);
	//If the preamble list has been traversed, check that the row has ended
	if (p == nullptr && curalign->extra_info < cr_code)
		if (loop) //Lengthen the preamble periodically
		{
			p = new AlignRecordNode;
			q->link = p;
			p->info = end_span;
			p->width = null_flag;
			next(loop);
			// Copy the templates from node |cur_loop| into node |p|
			q = hold_head;
			for (auto r = dynamic_cast<TokenNode*>(loop->u_part); r; next(r))
			{
				q->link = new TokenNode(r->token);
				next(q);
			}
			q->link = nullptr;
			p->u_part = hold_head->link;
			q = hold_head;
			for (auto r = dynamic_cast<TokenNode*>(loop->v_part); r; next(r))
			{
				q->link = new TokenNode(r->token);
				next(q);
			}
			q->link = nullptr;
			p->v_part = hold_head->link;
			next(loop);
			p->link = new GlueNode(loop->glue_ptr);
		}
		else
		{
			error("Extra alignment tab has been changed to "+esc("cr"), "You have given more \\span or & marks than there were\nin the preamble to the \\halign or \\valign now in progress.\nSo I'll assume that you meant to type \\cr instead.");
			curalign->extra_info = cr_code;
		}
	if (curalign->extra_info != span_code)
	{
		unsave();
		newsavelevel(align_group);
		if (mode == -hmode)
		{
			adjusttail = curtail;
			u = hpack(head->link, 0, additional);
			w = u->width;
			curtail = adjusttail;
			adjusttail = nullptr;
		}
		else
		{
			u = vpackage(head->link, 0, additional, 0);
			w = u->height;
		}
		n = 0;
		LinkedNode *q = curspan;
		if (q != curalign)
		{
			do
			{
				n++;
				next(q);
				next(q);
			} while (q != curalign);
			if (n > 255)
				confusion("256 spans");
			q = curspan;
			while (dynamic_cast<SpanNode*>(q->link)->Link < n)
				next(q);
			if (dynamic_cast<SpanNode*>(q->link)->Link > n)
			{
				auto s = new SpanNode;
				s->info = dynamic_cast<AlignRecordNode*>(q)->info;
				s->Link = n;
				dynamic_cast<AlignRecordNode*>(q)->info = s;
				s->width = w;
			}
			else 
				if (dynamic_cast<AlignRecordNode*>(q)->info->width < w)
					dynamic_cast<AlignRecordNode*>(q)->info->width = w;
		}
		else 
			curalign->width = std::max(w, curalign->width);
		u->type = unset_node;
		dynamic_cast<UnsetNode*>(u)->span_count = n;
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
		dynamic_cast<UnsetNode*>(u)->glue_stretch = totalstretch[o];
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
		dynamic_cast<UnsetNode*>(u)->glue_shrink = totalshrink[o];
		popnest();
		tail->link = u;
		tail = u;
		auto G = new GlueNode(curalign->glue_ptr);
		G->subtype = tab_skip_code+1;
		tail_append(G);
		if (curalign->extra_info >= cr_code)
			return true;
		initspan(dynamic_cast<SpanNode*>(p));
	}
	alignstate = 1000000;
	t = getXTokenSkipSpace();
	curalign = dynamic_cast<AlignRecordNode*>(p);
	initcol(t);
	return false;
}
