#include "macrocall.h"
#include "impression.h"
#include "gettoken.h"
#include "getavail.h"
#include "runaway.h"
#include "flushlist.h"
#include "backinput.h"
#include "endtokenlist.h"
#include "begintokenlist.h"
#include "erreur.h"
#include "texte.h"

void macrocall(void)
{
	auto savescannerstatus = scannerstatus;
	auto savewarningindex = warningindex;
	warningindex = curcs;
	halfword refcount = curchr;
	halfword r = link(refcount);
	smallnumber n = 0;
	if (tracing_macros() > 0)
	{
		begindiagnostic();
		print("\n"+cs(warningindex)+tokenshow(refcount));
		print(enddiagnostic(false));
	}
	ASCIIcode matchchr;
	if (info(r) != end_match_token) 
	{
		scannerstatus = matching;
		halfword unbalance = 0;
		longstate = type(curcs);
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
				gettoken();
				if (curtok = info(r))
				{
					r = link(r);
					if (info(r) >= match_token && info(r) <= end_match_token)
					{
						if (curtok < left_brace_limit) // cmd < right_brace
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
									if (curtok != info(v))
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
				if (curtok == partoken)
					if (longstate != long_call)
					{
						if (longstate == call)
						{
							runaway();
							backerror("Paragraph ended before "+scs(warningindex)+" was complete", "I suspect you've forgotten a `}', causing me to apply this\ncontrol sequence to too much text. How can we recover?\nMy plan is to forget the whole thing and hope for the best.");
						}
						pstack[n] = link(temp_head);
						alignstate -= unbalance;
						for (int m = 0; m <= n; m++)
							flushlist(pstack[m]);
						scannerstatus = savescannerstatus;
						warningindex = savewarningindex;
						return;
					}
				if (curtok < right_brace_limit)
					if (curtok < left_brace_limit)
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
							info(q) = curtok;
							p = q;
							gettoken();
							if (curtok == partoken)
								if (longstate != long_call)
								{
									if (longstate == call)
									{
										runaway();
										backerror("Paragraph ended before "+scs(warningindex)+" was complete", "I suspect you've forgotten a `}', causing me to apply this\ncontrol sequence to too much text. How can we recover?\nMy plan is to forget the whole thing and hope for the best.");
									}
									pstack[n] = link(temp_head);
									alignstate -= unbalance;
									for (int m = 0; m <= n; m++)
										flushlist(pstack[m]);
									scannerstatus = savescannerstatus;
									warningindex = savewarningindex;
									return;
								}
							if (curtok < right_brace_limit)
								if (curtok < left_brace_limit)
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
						info(q) = curtok;
						p = q;
					}
					else
					{
						backinput();
						inserror("Argument of "+scs(warningindex)+" has an extra }", "I've run across a `}' that doesn't seem to match anything.\nFor example, `\\def\\a#1{...}' and `\\a}' would produce\nthis error. If you simply proceed now, the `\\par' that\nI've just inserted will cause me to report a runaway\nargument that might be the root of the problem. But if\nyour `}' was spurious, just type `2' and it will go away.");
						alignstate++;
						longstate = call;
						curtok = partoken;
						continue;
					}
				else
				{
					if (curtok == space_token)
						if (info(r) <= end_match_token && info(r) >= match_token)
							continue;
					auto q = getavail();
					link(p) = q;
					info(q) = curtok;
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
				{
					begindiagnostic();
					print(std::string(1, matchchr));
					printnl(std::to_string(n)+"<-"+tokenlist(pstack[n-1], 0, 1000));
					print(enddiagnostic(false));
				}
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
