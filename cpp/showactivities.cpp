#include "showactivities.h"
#include "printchar.h"
#include "printesc.h"
#include "printscaled.h"
#include "printtotals.h"
#include "printmode.h"
#include "println.h"
#include "print.h"
#include "printnl.h"
#include "printint.h"
#include "showbox.h"
#include "xovern.h"

void showactivities(void)
/*var
  p: 0..nestsize;
  m: -203..203;
  a: memoryword;
  q, r: halfword;
  t: integer;*/
{
	nest[nestptr] = curlist;
	printnl(338); //
	println();
	for (int p = nestptr; p >= 0; p--)
	{
		int m = nest[p].modefield;
		memoryword a = nest[p].auxfield;
		printnl(363); //### 
		printmode(m);
		print(364); // entered at line 
		printint(abs(nest[p].mlfield));
		if (m == 102 && nest[p].pgfield != 8585216)
		{
			print(365); // (language
			printint(nest[p].pgfield%65536);
			print(366); //:hyphenmin
			printint(nest[p].pgfield/4194304);
			printchar(',');
			printint((nest[p].pgfield/65536)%64);
			printchar(')');
		}
		if (nest[p].mlfield < 0)
			print(367); // (\output routine)
		if (p == 0)
		{
			if (29998 != pagetail)
			{
				printnl(979); //### current page:
				if (outputactive)
					print(980); // (held over for link output)
				showbox(link(29998));
				if (pagecontents > 0)
				{
					printnl(981); //total height 
					printtotals();
					printnl(982); // goal height
					printscaled(pagesofar[0]);
					halfword r = link(30000);
					while (r != 30000)
					{
						println();
						printesc(330); //insert
						int t = subtype(r);
						printint(t);
						print(983); // adds 
						if (eqtb[5318+t].int_ == 1000)
							t = mem[r+3].int_;
						else
							t = xovern(mem[r+3].int_, 1000)*eqtb[5318+t].int_;
						printscaled(t);
						if (type(r) == 1)
						{
							halfword q = 29998;
							t = 0;
							do
							{
								q = link(q);
								if (type(q) == 3 && subtype(q) == subtype(r))
									t++;
							} while (q != info(r+1));
							print(984); //, #
							printint(t);
							print(985); // might split
						}
						r = link(r);
					}
				}
			}
			;
			if (link(29999))
			printnl(368); //### recent contributions:
		}
		showbox(link(nest[p].headfield));
		switch (abs(m)/101)
		{
			case 0:
				printnl(369); //prevdepth 
				if (a.int_ <= -65536000)
					print(370); //ignored
				else
					printscaled(a.int_);
				if (nest[p].pgfield)
				{
					print(371); //, prevgraf 
					printint(nest[p].pgfield);
					print(372); // line
					if (nest[p].pgfield != 1)
						printchar('s');
				}
				break;
			case 1:
				printnl(373); //spacefactor 
				printint(a.hh.lh);
				if (m > 0 && a.hh.rh > 0)
				{
					print(374); //, current language 
					printint(a.hh.rh);
				}
				break;
			case 2: 
				if (a.int_)
				{
					print(375); //this will be denominator of:
					showbox(a.int_);
				}
		}
	}
}
