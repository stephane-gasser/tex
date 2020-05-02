#include "newpatterns.h"
#include "scanleftbrace.h"
#include "getxtoken.h"
#include "printnl.h"
#include "print.h"
#include "error.h"
#include "newtrieop.h"
#include "overflow.h"
#include "printesc.h"
#include "scantoks.h"
#include "flushlist.h"

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
		if (int_par(cur_fam_code) <= 0)
			curlang = 0;
		else 
			if (int_par(cur_fam_code) > 255)
				curlang = 0;
			else
				curlang = int_par(cur_fam_code);
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
							{
								if (interaction == 3)
									printnl(262); //! 
								print(956); //Nonletter
								helpptr = 1;
								helpline[0] = 955; //(See Appendix H.)
								error();
							}
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
									overflow(950, triesize); //pattern memory
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
						{
							if (interaction == 3)
								printnl(262); //! 
							print(957); //Duplicate pattern
							helpptr = 1;
							helpline[0] = 955; //(See Appendix H.)
							error();
						}
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
					if (interaction == 3)
						printnl(262); //! 
					print(954); //Bad 
					printesc(952); //patterns
					helpptr = 1;
					helpline[0] = 955; //(See Appendix H.)
					error();
			}
		}
	}
	else
	{
		if (interaction == 3)
			printnl(262); //! 
		print(951); //Too late for 
		printesc(952); //patterns
		helpptr = 1;
		helpline[0] = 953; //All patterns must be given before typesetting begins.
		error();
		link(garbage) = scantoks(false, false);
		flushlist(defref);
	}
}
