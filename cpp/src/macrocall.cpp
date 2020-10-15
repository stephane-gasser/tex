#include "macrocall.h"
#include "impression.h"
#include "equivalent.h"
#include "noeud.h"
#include "runaway.h"
#include "erreur.h"
#include "lecture.h"
#include "getnext.h"
#include "alignement.h"
#include "etat.h"
#include "initprim.h"

static TokenList pstack[9];

void macrocall(Token t)
{
	auto savewarningindex = warningindex;
	warningindex = t.cs;
	TokenList refcount;
	refcount.token_ref_count = t.chr;
	halfword r = 0;
	smallnumber n = 0;
	if (tracing_macros() > 0)
		diagnostic("\n"+cs(warningindex)+tokenshow(&refcount));
	ASCIIcode matchchr;
	if (refcount.list.back() != end_match_token) 
	{
		halfword unbalance = 0;
		longstate = t.cs >= hash_base ? eqtb_cs[t.cs-hash_base].type : eqtb_active[t.cs-active_base].type;
		if (longstate >= outer_call)
			longstate -= 2;
		do
		{
			halfword s;
			halfword m;
			if (refcount.list[r] > match_token+255 || refcount.list[r] < match_token)
				s = 0;
			else
			{
				matchchr = refcount.list.back()-match_token;
				s = ++r;
				m = 0;
			}
			while (true)
			{
				t = gettoken(matching);
				if (t.tok == refcount.list[r])
				{
					r++;
					if (refcount.list[r] >= match_token && refcount.list[r] <= end_match_token)
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
						warningindex = savewarningindex;
						return;
					}
					else
					{
						auto tt = s;
						bool l22 = false;
						do
						{
							tempHead.list.push_back(refcount.list[tt]);
							m++;
							
							for (halfword u = tt+1, v = s; true; u++, v++)
							{
								if (u == r)
									if (t.tok != refcount.list[v])
										break;
									else
									{
										r = v+1;
										l22 = true;
										break;
									}
								if (refcount.list[u] != refcount.list[v])
									break;
							}
							if (!l22)
								tt++;
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
							runaway(matching);
							backerror(t, "Paragraph ended before "+scs(warningindex)+" was complete", "I suspect you've forgotten a `}', causing me to apply this\ncontrol sequence to too much text. How can we recover?\nMy plan is to forget the whole thing and hope for the best.");
						}
						pstack[n].list = tempHead.list;
						alignstate -= unbalance;
						for (int m = 0; m <= n; m++)
							pstack[m].list.clear();
						warningindex = savewarningindex;
						return;
					}
				if (t.tok < right_brace_limit)
					if (t.tok < left_brace_limit)
					{
						unbalance = 1;
						while (unbalance)
						{
							tempHead.list.push_back(t.tok);
							t = gettoken(matching);
							if (t.tok == partoken)
								if (longstate != long_call)
								{
									if (longstate == call)
									{
										runaway(matching);
										backerror(t, "Paragraph ended before "+scs(warningindex)+" was complete", "I suspect you've forgotten a `}', causing me to apply this\ncontrol sequence to too much text. How can we recover?\nMy plan is to forget the whole thing and hope for the best.");
									}
									pstack[n].list = tempHead.list;
									alignstate -= unbalance;
									for (int m = 0; m <= n; m++)
										pstack[m].list.clear();
									warningindex = savewarningindex;
									return;
								}
							if (t.tok < right_brace_limit)
								if (t.tok < left_brace_limit)
									unbalance++;
								else
									unbalance--;
						}
						tempHead.list.push_back(t.tok);
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
					if (t.tok == space_token && refcount.list[r] <= end_match_token && refcount.list[r] >= match_token)
						continue;
					tempHead.list.push_back(t.tok);
				}
				m++;
				if (refcount.list[r] > end_match_token || refcount.list[r] < match_token)
					continue;
				break;
			}
			if (s)
			{
				if (m == 1 && tempHead.list.size() && tempHead.list.back() < right_brace_limit )
				{
					pstack[n].list = tempHead.list;
					pstack[n].list.erase(pstack[n].list.begin());
				}
				else
					pstack[n].list = tempHead.list;
				n++;
				if (tracing_macros() > 0)
					diagnostic(std::string(1, matchchr)+"\n"+std::to_string(n)+"<-"+tokenlist(&pstack[n-1], 1000));
			}
		} while (refcount.list[r] != end_match_token); 
	}
	while (state == 0 && loc == 0 && index != 2)
		endtokenlist();
	beginTokenListMacro(&refcount);
	name = warningindex;
	Loc = r+1;
	if (n > 0)
	{
		if (paramstack.size()+n > paramsize)
			overflow("parameter stack size", paramsize);
		for (int m = 0; m < n; m++)
			paramstack.push_back(pstack[m]);
	}
	warningindex = savewarningindex;
}
