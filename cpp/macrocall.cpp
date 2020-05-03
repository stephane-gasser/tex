#include "macrocall.h"
#include "begindiagnostic.h"
#include "print.h"
#include "println.h"
#include "printcs.h"
#include "printnl.h"
#include "gettoken.h"
#include "sprintcs.h"
#include "getavail.h"
#include "runaway.h"
#include "flushlist.h"
#include "backinput.h"
#include "backerror.h"
#include "printint.h"
#include "endtokenlist.h"
#include "begintokenlist.h"
#include "tokenshow.h"
#include "error.h"
#include "inserror.h"
#include "showtokenlist.h"
#include "enddiagnostic.h"
#include "overflow.h"

void macrocall(void)
{
	auto savescannerstatus = scannerstatus;
	auto savewarningindex = warningindex;
	warningindex = curcs;
	halfword refcount = curchr;
	halfword r = link(refcount);
	smallnumber n = 0;
	if (int_par(tracing_macros_code) > 0)
	{
		begindiagnostic();
		println();
		printcs(warningindex);
		tokenshow(refcount);
		enddiagnostic(false);
	}
	ASCIIcode matchchr;
	if (info(r) != 0x0E'00) 
	{
		scannerstatus = 3;
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
			if (info(r) > 0x0D'FF || info(r) < 0x0D'00)
				s = 0;
			else
			{
				matchchr = info(r)-0x0D'00;
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
					if (info(r) >= 0x0D'00 && info(r) <= 0x0E'00)
					{
						if (curtok < 0x02'00) // cmd < right_brace
							alignstate--;
						break;
					}
					else
						continue;
				}
				if (s != r)
					if (s == 0)
					{
						printnl(262); //! 
						print(650); //Use of 
						sprintcs(warningindex);
						print(651); // doesn't match its definition
						helpptr = 4;
						helpline[3] = 652; //If you say, e.g., `\def\a1{...}', then you must always
						helpline[2] = 653; //put `1' after `\a', since control sequence names are
						helpline[1] = 654; //made up of letters only. The macro here has not been
						helpline[0] = 655; //followed by the required stuff, so I'm ignoring it.
						error();
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
							printnl(262); //! 
							print(645); //Paragraph ended before 
							sprintcs(warningindex);
							print(646); // was complete
							helpptr = 3;
							helpline[2] = 647; //I suspect you've forgotten a `}', causing me to apply this
							helpline[1] = 648; //control sequence to too much text. How can we recover?
							helpline[0] = 649; //My plan is to forget the whole thing and hope for the best.
							backerror();
						}
						pstack[n] = link(temp_head);
						alignstate -= unbalance;
						for (int m = 0; m <= n; m++)
							flushlist(pstack[m]);
						scannerstatus = savescannerstatus;
						warningindex = savewarningindex;
						return;
					}
				if (curtok < 0x03'00) // cmd <= right_bracce
					if (curtok < 0x02'00) // cmd < right_brace
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
										printnl(262); //! 
										print(645); //Paragraph ended before 
										sprintcs(warningindex);
										print(646); // was complete
										helpptr = 3;
										helpline[2] = 647; //I suspect you've forgotten a `}', causing me to apply this
										helpline[1] = 648; //control sequence to too much text. How can we recover?
										helpline[0] = 649; //My plan is to forget the whole thing and hope for the best.
										backerror();
									}
									pstack[n] = link(temp_head);
									alignstate -= unbalance;
									for (int m = 0; m <= n; m++)
										flushlist(pstack[m]);
									scannerstatus = savescannerstatus;
									warningindex = savewarningindex;
									return;
								}
							if (curtok < 0x03'00) // cmd <= right_brace
								if (curtok < 0x02'00) // cmd < right_brace
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
						printnl(262); //! 
						print(637); //Argument of 
						sprintcs(warningindex);
						print(638); // has an extra }
						helpptr = 6;
						helpline[5] = 639; //I've run across a `}' that doesn't seem to match anything.
						helpline[4] = 640; //For example, `\def\a#1{...}' and `\a}' would produce
						helpline[3] = 641; //this error. If you simply proceed now, the `\par' that
						helpline[2] = 642; //I've just inserted will cause me to report a runaway
						helpline[1] = 643; //argument that might be the root of the problem. But if
						helpline[0] = 644; //your `}' was spurious, just type `2' and it will go away.
						alignstate++;
						longstate = 111;
						curtok = partoken;
						inserror();
						continue;
					}
				else
				{
					if (curtok == spacer*0x01'00+' ')
						if (info(r) <= 0x0E'00 && info(r) >= 0x0D'00) // cmd == 13
							continue;
					auto q = getavail();
					link(p) = q;
					info(q) = curtok;
					p = q;
				}
				m++;
				if (info(r) > 0x0E'00 || info(r) < 0x0D'00) // cmd != 13
					continue;
				break;
			}
			if (s)
			{
				if (m == 1 && info(p) < 0x03'00 && p != temp_head)
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
				if (int_par(tracing_macros_code) > 0)
				{
					begindiagnostic();
					printnl(matchchr);
					printint(n);
					print(656); //<-
					showtokenlist(pstack[n-1], 0, 1000);
					enddiagnostic(false);
				}
			}
		} while (info(r) != 0x0E'00); // cmd = end_match
	}
	while (curinput.statefield == 0 && curinput.locfield == 0 && curinput.indexfield != 2)
		endtokenlist();
	begintokenlist(refcount, 5);
	curinput.namefield = warningindex;
	curinput.locfield = link(r);
	if (n > 0)
	{
		if (paramptr+n > maxparamstack)
		{
			maxparamstack =	paramptr+n;
			if (maxparamstack > paramsize)
				overflow(636, paramsize); //parameter stack size
		}
		for (int m = 0; m < n; m++)
			paramstack[paramptr+m] = pstack[m];
		paramptr += n;
	}
	scannerstatus = savescannerstatus;
	warningindex = savewarningindex;
}
