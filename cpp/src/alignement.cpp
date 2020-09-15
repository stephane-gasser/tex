#include "alignement.h"
#include "lecture.h"
#include "sauvegarde.h"
#include "normalparagraph.h"
#include "erreur.h"
#include "endgraf.h"
#include "offsave.h"
#include "deleteglueref.h"
#include "noeud.h"
#include "boite.h"
#include "popnest.h"
#include "impression.h"
#include "doassignments.h"
#include "resumeafterdisplay.h"
#include "buildpage.h"
#include "backinput.h"
#include <cmath>
#include "equivalent.h"
#include "flushmath.h" 
#include "pushnest.h"
#include "getnext.h"

static SpanNode *curspan = nullptr; 
static LinkedNode *curhead = nullptr;
static LinkedNode *curtail = nullptr;

class AlignStackNode : public LinkedNode
{
	public:
		AlignRecordNode *align;
		LinkedNode *preamble;
		SpanNode *span;
		AlignRecordNode *loop;
		int state;
		LinkedNode *head;
		LinkedNode *tail;
};

static AlignStackNode *alignptr = nullptr;

static void initspan(SpanNode *p)
{
	pushnest();
	if (mode == -hmode)
		space_factor = 1000;
	else
	{
		prev_depth = ignore_depth;
		normalparagraph();
	}
	curspan = p;
}

static void initcol(Token t)
{
	curalign->extra_info = t.cmd;
	if (t.cmd == omit)
		alignstate = 0;
	else
	{
		backinput(t);
		begintokenlist(dynamic_cast<TokenNode*>(curalign->u_part), u_template);
	}
}

static void initrow(void)
{
	pushnest();
	mode = (-hmode-vmode)-mode;
	if (mode == -hmode)
		space_factor = 0;
	else
		prev_depth = 0;
	auto G = new GlueNode(dynamic_cast<GlueNode*>(preamble)->glue_ptr);
	G->subtype = tab_skip_code+1;
	tail_append(G);
	curalign = dynamic_cast<AlignRecordNode*>(preamble->link);
	curtail = curhead;
	initspan(dynamic_cast<SpanNode*>(curalign));
}

static void popalignment(AlignRecordNode* &loop)
{
	delete curhead; 
	curtail = alignptr->tail;
	curhead = alignptr->head;
	alignstate = alignptr->state;
	loop = alignptr->loop;
	curspan = alignptr->span;
	preamble = alignptr->preamble;
	curalign = alignptr->align;
	auto p = alignptr;
	next(alignptr);
	delete p;
}

static void pushalignment(AlignRecordNode* loop)
{
	alignptr = new AlignStackNode;
	alignptr->link = alignptr;
	alignptr->align = curalign;
	alignptr->preamble = preamble;
	alignptr->span = curspan;
	alignptr->loop = loop;
	alignptr->state = alignstate;
	alignptr->head = curhead;
	alignptr->tail = curtail;
	curhead = new LinkedNode;
}

void initalign(Token t, AlignRecordNode* &loop)
{
	auto savecsptr = t.cs;
	pushalignment(loop);
	alignstate = -1000000;
	if (mode == mmode && (tail != head || incompleat_noad)) //Check for improper alignment in displayed math
	{
		error("Improper "+esc("halign")+" inside $$'s", "Displays can use special alignments (like \\eqalignno)\nonly if nothing but the alignment itself is between $$'s.\nSo I've deleted the formulas that preceded this alignment.");
		flushmath();
	}
	pushnest();
	if (mode == mmode) // Change current mode to |-vmode| for \.{\\halign}, |-hmode| for \.{\\valign}
	{
		mode = -vmode;
		prev_depth = nest[nest.size()-3].auxfield.int_;
	}
	else 
		if (mode > 0)
		mode = -mode;
	t = scanspec(align_group);
	align_head->link = nullptr;
	curalign = dynamic_cast<AlignRecordNode*>(align_head);
	loop = 0;
	scannerstatus = aligning;
	warningindex = savecsptr;
	alignstate = -1000000;
	while (true)
	{
		appendAtEnd(curalign, new GlueNode(tab_skip_code));
		if (t.cmd == car_ret)
			break;
		hold_head->link = nullptr;
		auto p = hold_head;
		bool keepIn = true;
		for (t = getpreambletoken(); t.cmd != mac_param && keepIn; t = getpreambletoken())
		{
			switch (t.cmd)
			{
				case tab_mark:
					if (alignstate == -1000000)
						if (p == hold_head && loop == nullptr)
							loop = curalign;
						else
						{
							backerror(t, "Missing # inserted in alignment preamble", "There should be exactly one # between &'s, when an\n\\halign or \\valign is being set up. In this case you had\nnone, so I've put one in; maybe that will work.");
							keepIn = false;
						}
					break;
				case out_param:
					if (alignstate == -1000000)
					{
						backerror(t, "Missing # inserted in alignment preamble", "There should be exactly one # between &'s, when an\n\\halign or \\valign is being set up. In this case you had\nnone, so I've put one in; maybe that will work.");
						keepIn = false;
					}
					break;
				case spacer:
					if (p != hold_head)
						appendAtEnd(p, new TokenNode(t.tok));
					break;
				default:
					appendAtEnd(p, new TokenNode(t.tok));
			}
		}
		appendAtEnd(curalign, new BoxNode);
		curalign->info = end_span;
		curalign->width = null_flag;
		curalign->u_part = hold_head->link;
		hold_head->link = nullptr;
		for (p = hold_head; true; appendAtEnd(p, new TokenNode(t.tok)))
		{
			t = getpreambletoken();
			if (t.cmd <= out_param && t.cmd >= tab_mark && alignstate == -1000000)
				break;
			if (t.cmd == mac_param)
			{
				error("Only one # is allowed per tab", "There should be exactly one # between &'s, when an\n\\halign or \\valign is being set up. In this case you had\nmore than one, so I'm ignoring all but the first.");
				continue;
			}
		}
		appendAtEnd(p, new TokenNode(end_template_token));
		curalign->v_part = hold_head->link;
	}
	scannerstatus = normal;
	newsavelevel(align_group);
	if (every_cr())
		begintokenlist(every_cr(), every_cr_text);
	alignpeek(loop);
}

static void finrow(AlignRecordNode* &loop)
{
	BoxNode *p;
	if (mode == -hmode)
	{
		p = hpack(head->link, 0, additional);
		popnest();
		appendtovlist(p);
		if (curhead != curtail)
		{
			tail->link = curhead->link;
			tail = curtail;
		}
	}
	else
	{
		p = vpack(head->link, 0, additional);
		popnest();
		tail_append(p);
		space_factor = 1000;
	}
	p->type = unset_node;
	dynamic_cast<UnsetNode*>(p)->glue_stretch = 0;
	if (every_cr())
		begintokenlist(every_cr(), every_cr_text);
	alignpeek(loop);
}

static bool fincol(Token t, AlignRecordNode* &loop)
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
				appendAtEnd(q, new TokenNode(r->token));
			q->link = nullptr;
			p->u_part = hold_head->link;
			q = hold_head;
			for (auto r = dynamic_cast<TokenNode*>(loop->v_part); r; next(r))
				appendAtEnd(q, new TokenNode(r->token));
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
		appendAtEnd(tail, u);
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

static void finalign(AlignRecordNode* &loop)
{
	scaled t, w; // width of column
	halfword n; // matching span amount
	if (curgroup != align_group)
		confusion("align1");
	unsave();
	if (curgroup != align_group)
		confusion("align0"); 
	unsave();
	scaled o = nest[nest.size()-2].modefield == mmode ? display_indent() : 0; // shift offset for unset boxes
	auto q = preamble->link;
	do
	{
		// q: AlignNode ??
		auto Q = dynamic_cast<AlignRecordNode*>(q);
		flushnodelist(Q->u_part);
		flushnodelist(Q->v_part);
		if (is_running(Q->width))
		{
			//Nullify |width(q)| and the tabskip glue following this column
			Q->width = 0;
			if (Q->glue_ptr)
			{
				zero_glue->glue_ref_count++;
				deleteglueref(Q->glue_ptr);
				Q->glue_ptr = zero_glue;
			}
		}
		if (Q->info != end_span)
		{
			//Merge the widths in the span nodes of |q| with those of |p|, destroying the span nodes of |q|
			t = Q->width+dynamic_cast<GlueNode*>(q->link)->glue_ptr->width;
			SpanNode *r;
			SpanNode *s;
			r = Q->info;
			s = end_span;
			s->info = dynamic_cast<SpanNode*>(q->link->link);
			n = 1;
			do
			{
				r->width -= t;
				SpanNode *u;
				u = r->info;
				while (r->Link > n)
				{
					s = s->info;
					n = s->info->Link+1;
				}
				if (r->Link < n)
				{
					r->info = s->info;
					s->info = r;
					r->Link--;
					s = r;
				}
				else
				{
					if (r->width > s->info->width)
						s->info->width = r->width;
					delete r;
				}
				r = u;
			} while (r != end_span);
		}
		q->type = unset_node;
		auto QQ = dynamic_cast<UnsetNode*>(q);
		QQ->span_count = 0;
		QQ->height = 0;
		QQ->depth = 0;
		QQ->glue_order = 0;
		QQ->glue_sign = 0;
		QQ->glue_stretch = 0;
		QQ->glue_shrink = 0;
		next(q);
		next(q);
	} while (q);
	auto s1 = savestack.back()->int_;
	savestack.pop_back();
	auto s0 = savestack.back()->int_;
	savestack.pop_back();
	packbeginline = -mode_line;
	BoxNode *p;
	if (mode == -vmode)
	{
		scaled rulesave = overfull_rule();
		overfull_rule() = 0;
		p = hpack(preamble, s1, s0);
		overfull_rule() = rulesave;
	}
	else
	{
		q = preamble->link;
		auto Q = dynamic_cast<UnsetNode*>(q);
		do
		{
			Q->height = Q->width;
			Q->width = 0;
			next(q);
			next(q);
		} while (q);
		p = vpack(preamble, s1, s0);
		q = preamble->link;
		do
		{
			Q->width = Q->height;
			Q->height = 0;
			next(q);
			next(q);
		} while (q);
	}
	packbeginline = 0;
	q = head->link;
	auto s = head;
	while (q)
	{
		if (q->type != char_node)
			if (q->type == unset_node)
			{
				auto Q = dynamic_cast<UnsetNode*>(q);
				if (mode == -vmode)
				{
					Q->type = hlist_node;
					Q->width = p->width;
				}
				else
				{
					Q->type = vlist_node;
					Q->height = p->height;
				}
				//q : BoxNode
				Q->glue_order = p->glue_order;
				Q->glue_sign = p->glue_sign;
				Q->glue_set = p->glue_set;
				Q->shift_amount = o;
				auto r = Q->list_ptr->link;
				s = Q->list_ptr->link;
				do
				{
					auto R = dynamic_cast<UnsetNode*>(r);
					auto S = dynamic_cast<BoxNode*>(s);
					auto P = dynamic_cast<BoxNode*>(p);
					n = R->span_count;
					t = S->width;
					w = t;
					auto u = hold_head;
					while (n > 0)
					{
						n--;
						next(s);
						auto V = dynamic_cast<GlueNode*>(s)->glue_ptr;
						auto g = new GlueNode(V);
						g->subtype = tab_skip_code+1;
						appendAtEnd(u, g);
						t += V->width;
						if (P->glue_sign == stretching)
						{
							if (V->stretch_order == P->glue_order)
								t += round(P->glue_set*V->stretch);
						}
						else 
							if (P->glue_sign == shrinking && V->shrink_order == P->glue_order)
								t -= round(P->glue_set*V->shrink);
						next(s);
						S = dynamic_cast<BoxNode*>(s);
						appendAtEnd(u, new BoxNode);
						t += S->width;
						auto U = dynamic_cast<BoxNode*>(u);
						if (mode == -vmode)
							U->width = S->width;
						else
						{
							u->type = vlist_node;
							U->height = S->height;
						}
					}
					if (mode == -vmode)
					{
						R->height = Q->height;
						R->depth = Q->depth;
						if (t == R->width)
						{
							R->glue_sign = 0;
							R->glue_order = 0;
							R->glue_set = 0.0;
						}
						else 
							if (t > R->width)
							{
								R->glue_sign = stretching;
								if (R->glue_stretch == 0)
									R->glue_set = 0.0;
								else
									R->glue_set = (t-R->width)/R->glue_stretch;
							}
							else
							{
								R->glue_order = R->glue_sign;
								R->glue_sign = shrinking;
								if (R->glue_shrink == 0)
									R->glue_set = 0.0;
								else 
									if (R->glue_order == 0 && R->width-t > R->glue_shrink)
										R->glue_set = 1.0;
									else
										R->glue_set = (R->width-t)/R->glue_shrink;
							}
						R->width = w;
						r->type = hlist_node;
					}
					else
					{
						R->width = Q->width;
						if (t == R->height)
						{
							R->glue_sign = 0;
							R->glue_order = 0;
							R->glue_set = 0.0;
						}
						else 
							if (t > R->height)
							{
								R->glue_sign = stretching;
								if (R->glue_stretch == 0)
									R->glue_set = 0.0;
								else
									R->glue_set = (t-R->height)/R->glue_stretch;
							}
							else
							{
								R->glue_order = R->glue_sign;
								R->glue_sign = shrinking;
								if (R->glue_shrink == 0)
									R->glue_set = 0.0;
								else 
									if (R->glue_order == 0 && R->height-t > R->glue_shrink)
										R->glue_set = 1.0;
									else
										R->glue_set = (R->height-t)/R->glue_shrink;
							}
						R->height = w;
						r->type = vlist_node;
					}
					dynamic_cast<BoxNode*>(r)->shift_amount = 0;
					if (u != hold_head)
					{
						u->link = r->link;
						r->link = hold_head->link;
						r = u;
					}
					next(r);
					next(r);
					next(s);
					next(s);
				} while (r);
			}
			else 
				if (q->type == rule_node)
				{
					auto Q = dynamic_cast<RuleNode*>(q);
					auto P = dynamic_cast<RuleNode*>(p);
					if (is_running(Q->width))
						Q->width = P->width;
					if (is_running(Q->height))
						Q->height = P->height;
					if (is_running(Q->depth))
						Q->depth = P->depth;
					if (o)
					{
						auto r = q->link;
						q->link = nullptr;
						q = hpack(q, 0, additional);
						dynamic_cast<BoxNode*>(q)->shift_amount = o;
						q->link = r;
						s->link = q;
					}
				}
		s = q;
		next(q);
	}
	flushnodelist(p);
	popalignment(loop);
	auto auxsave = aux;
	auto pp = head->link;
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
		tail->link = pp;
		if (pp)
			tail = q;
		tail_append(new PenaltyNode(post_display_penalty()));
		tail_append(new GlueNode(below_display_skip_code));
		aux = auxsave;
		resumeafterdisplay(tk);
	}
	else
	{
		aux = auxsave;
		tail->link = pp;
		if (pp)
			tail = q;
		if (mode == vmode)
			buildpage();
	}
}

void alignpeek(AlignRecordNode* &loop)
{
	while (true)
	{
		alignstate = 1000000;
		auto t = getXTokenSkipSpace();
		if (t.cmd == no_align)
		{
			t = scanleftbrace();
			newsavelevel(no_align_group);
			if (mode == -vmode)
				normalparagraph();
		}
		else 
			if (t.cmd == right_brace)
				finalign(loop);
			else 
				if (t.cmd == car_ret && t.chr == 258)
					continue;
				else
				{
					initrow();
					initcol(t);
				}
		break;
	}
}

void doendv(Token t, AlignRecordNode* &loop)
{
	inputstack.back() = curinput;
	for (baseptr = inputstack.size()-1; inputstack[baseptr].indexfield != v_template && inputstack[baseptr].locfield == 0 && inputstack[baseptr].statefield == token_list; baseptr--);
	if (inputstack[baseptr].indexfield != v_template || inputstack[baseptr].locfield || inputstack[baseptr].statefield != token_list)
		fatalerror("(interwoven alignment preambles are not allowed)");
	if (curgroup == align_group)
	{
		endgraf();
		if (fincol(t, loop))
			finrow(loop);
	}
	else
		offsave(t);
}
