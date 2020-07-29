#include "macrocall.h"
#include "impression.h"
#include "noeud.h"
#include "runaway.h"
#include "backinput.h"
#include "erreur.h"
#include "lecture.h"
#include "texte.h"

void macrocall(Token t)
{
	auto savescannerstatus = scannerstatus;
	auto savewarningindex = warningindex;
	warningindex = t.cs;
	halfword refcount = t.chr;
	TokenNode *r;
	r->num = link(refcount);
	smallnumber n = 0;
	if (tracing_macros() > 0)
		diagnostic("\n"+cs(warningindex)+tokenshow(refcount));
	ASCIIcode matchchr;
	if (r->token != end_match_token) 
	{
		scannerstatus = matching;
		halfword unbalance = 0;
		longstate = type(t.cs);
		if (longstate >= outer_call)
			longstate -= 2;
		do
		{
			temp_head->link = nullptr;
			TokenNode *s, *p;
			halfword m;
			if (r->token > match_token+255 || r->token < match_token)
				s = nullptr;
			else
			{
				matchchr = r->token-match_token;
				s = dynamic_cast<TokenNode*>(r->link);
				r = s;
				p = dynamic_cast<TokenNode*>(temp_head);
				m = 0;
			}
			TokenNode *rbraceptr;
			while (true)
			{
				t = gettoken();
				if (t.tok = r->token)
				{
					r = dynamic_cast<TokenNode*>(r->link);
					if (r->token >= match_token && r->token <= end_match_token)
					{
						if (t.tok < left_brace_limit) 
							alignstate--;
						break;
					}
					else
						continue;
				}
				if (s != r)
					if (s == 0)
					{
						error("Use of "+scs(warningindex)+" doesn't match its definition", "If you say, e.g., `\\def\\a1{...}', then you must always\nput `1' after `\\a', since control sequence names are\nmade up of letters only. The macro here has not been\nfollowed by the required stuff, so I'm ignoring it.");
						scannerstatus = savescannerstatus;
						warningindex = savewarningindex;
						return;
					}
					else
					{
						auto tt = s;
						bool l22 = false;
						do
						{
							auto q = new TokenNode;
							p->link = q;
							q->token = tt->token;
							p = q;
							m++;
							auto u = dynamic_cast<TokenNode*>(tt->link);
							auto v = dynamic_cast<TokenNode*>(s);
							while(true)
							{
								if (u == r)
									if (t.tok != v->token)
										break;
									else
									{
										r = dynamic_cast<TokenNode*>(v->link);
										l22 = true;
										break;
									}
								if (u->token != v->token)
									break;
								u = dynamic_cast<TokenNode*>(u->link);
								v = dynamic_cast<TokenNode*>(v->link);
							}
							if (!l22)
								tt = dynamic_cast<TokenNode*>(tt->link);
						} while (tt != r && !l22);
						if (l22)
							continue;
						r = s;
					}
				if (t.tok == partoken)
					if (longstate != long_call)
					{
						if (longstate == call)
						{
							runaway();
							backerror(t, "Paragraph ended before "+scs(warningindex)+" was complete", "I suspect you've forgotten a `}', causing me to apply this\ncontrol sequence to too much text. How can we recover?\nMy plan is to forget the whole thing and hope for the best.");
						}
						pstack[n] = temp_head->link->num;
						alignstate -= unbalance;
						for (int m = 0; m <= n; m++)
							flushlist(pstack[m]);
						scannerstatus = savescannerstatus;
						warningindex = savewarningindex;
						return;
					}
				if (t.tok < right_brace_limit)
					if (t.tok < left_brace_limit)
					{
						unbalance = 1;
						while (true)
						{
							auto q = new TokenNode;
							p->link = q;
							q->token = t.tok;
							p = q;
							t = gettoken();
							if (t.tok == partoken)
								if (longstate != long_call)
								{
									if (longstate == call)
									{
										runaway();
										backerror(t, "Paragraph ended before "+scs(warningindex)+" was complete", "I suspect you've forgotten a `}', causing me to apply this\ncontrol sequence to too much text. How can we recover?\nMy plan is to forget the whole thing and hope for the best.");
									}
									pstack[n] = temp_head->link->num;
									alignstate -= unbalance;
									for (int m = 0; m <= n; m++)
										flushlist(pstack[m]);
									scannerstatus = savescannerstatus;
									warningindex = savewarningindex;
									return;
								}
							if (t.tok < right_brace_limit)
								if (t.tok < left_brace_limit)
									unbalance++;
								else
								{
									unbalance--;
									if (unbalance == 0)
										break;
								}
						}
						rbraceptr = dynamic_cast<TokenNode*>(p);
						auto q = new TokenNode;
						p->link = q;
						q->token = t.tok;
						p = q;
					}
					else
					{
						backinput(t);
						inserror(t, "Argument of "+scs(warningindex)+" has an extra }", "I've run across a `}' that doesn't seem to match anything.\nFor example, `\\def\\a#1{...}' and `\\a}' would produce\nthis error. If you simply proceed now, the `\\par' that\nI've just inserted will cause me to report a runaway\nargument that might be the root of the problem. But if\nyour `}' was spurious, just type `2' and it will go away.");
						alignstate++;
						longstate = call;
						t.tok = partoken;
						continue;
					}
				else
				{
					if (t.tok == space_token)
						if (r->token <= end_match_token && r->token >= match_token)
							continue;
					auto q = new TokenNode;
					p->link = q;
					q->token = t.tok;
					p = q;
				}
				m++;
				if (r->token > end_match_token || r->token < match_token)
					continue;
				break;
			}
			if (s)
			{
				if (m == 1 && p->token < right_brace_limit && p != temp_head)
				{
					rbraceptr->link = nullptr;
					p->link->num = avail;
					avail = p->num;
					p = dynamic_cast<TokenNode*>(temp_head->link);
					pstack[n] = p->link->num;
					p->link->num = avail;
					avail = p->num;
				}
				else
					pstack[n] = temp_head->link->num;
				n++;
				if (tracing_macros() > 0)
					diagnostic(std::string(1, matchchr)+"\n"+std::to_string(n)+"<-"+tokenlist(pstack[n-1], 0, 1000));
			}
		} while (r->token != end_match_token); 
	}
	while (state == 0 && loc == 0 && index != 2)
		endtokenlist();
	begintokenlist(refcount, macro);
	name = warningindex;
	loc = r->link->num;
	if (n > 0)
	{
		if (paramptr+n > maxparamstack)
		{
			maxparamstack =	paramptr+n;
			if (maxparamstack > paramsize)
				overflow("parameter stack size", paramsize);
		}
		for (int m = 0; m < n; m++)
			paramstack[paramptr+m] = pstack[m];
		paramptr += n;
	}
	scannerstatus = savescannerstatus;
	warningindex = savewarningindex;
}
