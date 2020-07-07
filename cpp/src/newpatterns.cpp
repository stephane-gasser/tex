#include "newpatterns.h"
#include "lecture.h"
#include "impression.h"
#include "erreur.h"
#include "newtrieop.h"
#include "flushlist.h"
#include "texte.h"

void newpatterns(void)
{
	char k, l;
	bool digitsensed;
	quarterword v;
	triepointer p, q;
	bool firstchild;
	ASCIIcode c;
	if (trienotready)
	{
		curlang = cur_fam();
		if (curlang <= 0 || curlang > 255)
				curlang = 0;
		scanleftbrace();
		k = 0;
		hyf[0] = 0;
		digitsensed = false;
		bool keepIn = true;
		while (keepIn)
		{
			getxtoken();
			switch (curcmd)
			{
				case letter:
				case other_char:
					if (digitsensed  || curchr < '0' || curchr > '9')
					{
						if (curchr == '.')
							curchr = 0;
						else
						{
							curchr = lc_code(curchr);
							if (curchr == 0)
								error("Nonletter", "(See Appendix H.)");
						}
						if (k < 63)
						{
							k++;
							hc[k] = curchr;
							hyf[k] = 0;
							digitsensed = false;
						}
					}
					else 
						if (k < 63)
						{
							hyf[k] = curchr-'0';
							digitsensed = true;
						}
					break;
				case spacer:
				case right_brace:
					if (k > 0)
					{
						if (hc[1] == 0)
							hyf[0] = 0;
						if (hc[k] == 0)
							hyf[k] = 0;
						l = k;
						v = 0;
						while (true)
						{
							if (hyf[l] != 0)
							v = newtrieop(k-l, hyf[l], v);
							if (l > 0)
								l--;
							else
								break;
						}
						q = 0;
						hc[0] = curlang;
						while (l <= k)
						{
							c = hc[l];
							l++;
							p = triel[q];
							firstchild = true;
							while (p > 0 && c > triec[p])
							{
								q = p;
								p = trier[q];
								firstchild = false;
							}
							if (p == 0 || c < triec[p])
							{
								if (trieptr == triesize)
									overflow("pattern memory", triesize);
								trieptr++;
								trier[trieptr] = p;
								p = trieptr;
								triel[p] = 0;
								if (firstchild)
									triel[q] = p;
								else
									trier[q] = p;
								triec[p] = c;
								trieo[p] = 0;
							}
							q = p;
						}
						if (trieo[q])
							error("Duplicate pattern", "(See Appendix H.)");
						trieo[q] = v;
					}
					if (curcmd == right_brace)
					{
						keepIn = false;
						continue;
					}
					k = 0;
					hyf[0] = 0;
					digitsensed = false;
					break;
				default:
					error("Bad "+esc("patterns"), "(See Appendix H.)");
			}
		}
	}
	else
	{
		error("Too late for "+esc("patterns"), "All patterns must be given before typesetting begins.");
		link(garbage) = scantoks(false, false);
		flushlist(defref);
	}
}
