#include "macrocall.h"
#include "impression.h"
#include "getavail.h"
#include "runaway.h"
#include "flushlist.h"
#include "backinput.h"
#include "erreur.h"
#include "lecture.h"
#include "texte.h"

void macrocall(halfword chr, halfword cs_)
{
	auto savescannerstatus = scannerstatus;
	auto savewarningindex = warningindex;
	warningindex = cs_;
	halfword refcount = chr;
	halfword r = link(refcount);
	smallnumber n = 0;
	if (tracing_macros() > 0)
		diagnostic("\n"+cs(warningindex)+tokenshow(refcount));
	ASCIIcode matchchr;
	if (info(r) != end_match_token) 
	{
		scannerstatus = matching;
		halfword unbalance = 0;
		longstate = type(cs_);
		if (longstate >= outer_call)
			longstate -= 2;
		do
		{
			link(temp_head) = 0;
			halfword s;
			halfword p;
			halfword m;
			if (info(r) > match_token+255 || info(r) < match_token)
				s = 0;
			else
			{
				matchchr = info(r)-match_token;
				s = link(r);
				r = s;
				p = temp_head;
				m = 0;
			}
			halfword rbraceptr;
			while (true)
			{
				halfword tok;
				std::tie(std::ignore, std::ignore, tok, std::ignore) = gettoken();
				if (tok = info(r))
				{
					r = link(r);
					if (info(r) >= match_token && info(r) <= end_match_token)
					{
						if (tok < left_brace_limit) // cmd < right_brace
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
						auto t = s;
						bool l22 = false;
						do
						{
							auto q = getavail();
							link(p) = q;
							info(q) = info(t);
							p = q;
							m++;
							auto u = link(t);
							auto v = s;
							while(true)
							{
								if (u == r)
									if (tok != info(v))
										break;
									else
									{
										r = link(v);
										l22 = true;
										break;
									}
								if (info(u) != info(v))
									break;
								u = link(u);
								v = link(v);
							}
							if (!l22)
								t = link(t);
						} while (t != r && !l22);
						if (l22)
							continue;
						r = s;
					}
				if (tok == partoken)
					if (longstate != long_call)
					{
						if (longstate == call)
						{
							runaway();
							backerror(tok, "Paragraph ended before "+scs(warningindex)+" was complete", "I suspect you've forgotten a `}', causing me to apply this\ncontrol sequence to too much text. How can we recover?\nMy plan is to forget the whole thing and hope for the best.");
						}
						pstack[n] = link(temp_head);
						alignstate -= unbalance;
						for (int m = 0; m <= n; m++)
							flushlist(pstack[m]);
						scannerstatus = savescannerstatus;
						warningindex = savewarningindex;
						return;
					}
				if (tok < right_brace_limit)
					if (tok < left_brace_limit)
					{
						unbalance = 1;
						while (true)
						{
							auto q = avail;
							if (q == 0)
								q = getavail();
							else
							{
								avail = link(q);
								link(q) = 0;
							}
							link(p) = q;
							info(q) = tok;
							p = q;
							std::tie(std::ignore, std::ignore, tok, std::ignore) = gettoken();
							if (tok == partoken)
								if (longstate != long_call)
								{
									if (longstate == call)
									{
										runaway();
										backerror(tok, "Paragraph ended before "+scs(warningindex)+" was complete", "I suspect you've forgotten a `}', causing me to apply this\ncontrol sequence to too much text. How can we recover?\nMy plan is to forget the whole thing and hope for the best.");
									}
									pstack[n] = link(temp_head);
									alignstate -= unbalance;
									for (int m = 0; m <= n; m++)
										flushlist(pstack[m]);
									scannerstatus = savescannerstatus;
									warningindex = savewarningindex;
									return;
								}
							if (tok < right_brace_limit)
								if (tok < left_brace_limit)
									unbalance++;
								else
								{
									unbalance--;
									if (unbalance == 0)
										break;
								}
						}
						rbraceptr = p;
						auto q = getavail();
						link(p) = q;
						info(q) = tok;
						p = q;
					}
					else
					{
						backinput(tok);
						inserror(tok, "Argument of "+scs(warningindex)+" has an extra }", "I've run across a `}' that doesn't seem to match anything.\nFor example, `\\def\\a#1{...}' and `\\a}' would produce\nthis error. If you simply proceed now, the `\\par' that\nI've just inserted will cause me to report a runaway\nargument that might be the root of the problem. But if\nyour `}' was spurious, just type `2' and it will go away.");
						alignstate++;
						longstate = call;
						tok = partoken;
						continue;
					}
				else
				{
					if (tok == space_token)
						if (info(r) <= end_match_token && info(r) >= match_token)
							continue;
					auto q = getavail();
					link(p) = q;
					info(q) = tok;
					p = q;
				}
				m++;
				if (info(r) > end_match_token || info(r) < match_token)
					continue;
				break;
			}
			if (s)
			{
				if (m == 1 && info(p) < right_brace_limit && p != temp_head)
				{
					link(rbraceptr) = 0;
					link(p) = avail;
					avail = p;
					p = link(temp_head);
					pstack[n] = link(p);
					link(p) = avail;
					avail = p;
				}
				else
					pstack[n] = link(temp_head);
				n++;
				if (tracing_macros() > 0)
					diagnostic(std::string(1, matchchr)+"\n"+std::to_string(n)+"<-"+tokenlist(pstack[n-1], 0, 1000));
			}
		} while (info(r) != end_match_token); 
	}
	while (state == 0 && loc == 0 && index != 2)
		endtokenlist();
	begintokenlist(refcount, macro);
	name = warningindex;
	loc = link(r);
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
