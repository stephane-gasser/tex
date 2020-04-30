#include "scansomethinginternal.h"
#include "scancharnum.h"
#include "printnl.h"
#include "print.h"
#include "backerror.h"
#include "scaneightbitint.h"
#include "backinput.h"
#include "scanfontident.h"
#include "findfontdimen.h"
#include "printcmdchr.h"
#include "printesc.h"
#include "error.h"
#include "muerror.h"
#include "newspec.h"


void scansomethinginternal(smallnumber level, bool negative)
{
	halfword m = curchr;
	switch (curcmd)
	{
		case 85:
			scancharnum();
			if (m == 5007)
			{
				curval = eqtb[5007+curval].hh.rh;
				curvallevel = 0;
			}
			else 
				if (m < 5007)
				{
					curval = eqtb[m+curval].hh.rh;
					curvallevel = 0;
				}
				else
				{
					curval = eqtb[m+curval].int_;
					curvallevel = 0;
				}
			break;
		case 71:
		case 72:
		case 86:
		case 87:
		case 88:
			if (level != 5)
			{
				if (interaction == 3)
					printnl(262); //! 
				print(664); //Missing number, treated as zero
				helpptr = 3;
				helpline[2] = 665; //A number should have been here; I inserted `0'.
				helpline[1] = 666; //(If you can't figure out why I needed to see a number,
				helpline[0] = 667; //look up `weird error' in the index to The TeXbook.)
				backerror();
				curval = 0;
				curvallevel = 1;
			}
			else 
				if (curcmd <= 72)
				{
					if (curcmd < 72)
					{
						scaneightbitint;
						m = 3422+curval;
					}
					curval = eqtb[m].hh.rh;
					curvallevel = 5;
				}
				else
				{
					backinput();
					scanfontident();
					curval += 2624;
					curvallevel = 4;
				}
			break;
		case 73:
			curval = eqtb[m].int_;
			curvallevel = 0;
			break;
		case 74:
			curval = eqtb[m].int_;
			curvallevel = 1;
			break;
		case 75:
			curval = eqtb[m].hh.rh;
			curvallevel = 2;
			break;
		case 76:
			curval = eqtb[m].hh.rh;
			curvallevel = 3;
			break;
		case 79:
			if (abs(curlist.modefield) != m)
			{
				if (interaction == 3)
					printnl(262); //! 
				print(680); //Improper 
				printcmdchr(79, m);
				helpptr = 4;
				helpline[3] = 681; // You can refer to \spacefactor only in horizontal mode;
				helpline[2] = 682; //you can refer to \prevdepth only in vertical mode; and
				helpline[1] = 683; //neither of these is meaningful inside \write. So
				helpline[0] = 684; //I'm forgetting what you said and using zero instead.
				error();
				if (level != 5)
				{
					curval = 0;
					curvallevel = 1;
				}
				else
				{
					curval = 0;
					curvallevel = 0;
				}
			}
			else 
				if (m == 1)
				{
					curval = curlist.auxfield.int_;
					curvallevel = 1;
				}
				else
				{
					curval = curlist.auxfield.hh.lh;
					curvallevel = 0;
				}
			break;
		case 80:
			if (curlist.modefield == 0)
			{
				curval = 0;
				curvallevel = 0;
			}
			else
			{
				nest[nestptr] = curlist;
				auto p = nestptr;
				while (abs(nest[p].modefield) != 1)
					p--;
				curval = nest[p].pgfield;
				curvallevel = 0;
			}
			break;
		case 82:
			if (m == 0)
				curval = deadcycles;
			else
				curval = insertpenalties;
			curvallevel = 0;
			break;
		case 81:
			if (pagecontents == 0 && !outputactive)
				if (m == 0)
					curval = 1073741823;
				else
					curval = 0;
			else
				curval = pagesofar[m];
			curvallevel = 1;
			break;
		case 84:
			if (eqtb[3412].hh.rh == 0)
				curval = 0;
			else
				curval = info(eqtb[3412].hh.rh);
			curvallevel = 0;
			break;
		case 83:
			scaneightbitint();
			if (box(curval) == 0)
				curval = 0;
			else
				curval = mem[box(curval)+m].int_;
			curvallevel = 1;
		break;
		case 68:
		case 69:
			curval = curchr;
			curvallevel = 0;
			break;
		case 77:
			findfontdimen(false);
			fontinfo[fmemptr].int_ = 0;
			curval = fontinfo[curval].int_;
			curvallevel = 1;
			break;
		case 78:
			scanfontident();
			if (m == 0)
			{
				curval = hyphenchar[curval];
				curvallevel = 0;
			}
			else
			{
				curval = skewchar[curval];
				curvallevel = 0;
			};
			break;
		case 89:
			scaneightbitint();
			switch (m)
			{
				case 0: 
					curval = eqtb[5318+curval].int_;
					break;
				case 1: 
					curval = eqtb[5851+curval].int_;
					break;
				case 2: 
					curval = skip(2900);
					break;
				case 3: 
					curval = mu_skip(3156);
			};
			curvallevel = m;
			break;
		case 70:
			if (curchr > 2)
			{
				if (curchr == 3)
					curval = line;
				else
					curval = lastbadness;
				curvallevel = 0;
			}
			else
			{
				if (curchr == 2)
					curval = 0;
				else
					curval = 0;
				curvallevel = curchr;
				if (curlist.tailfield < himemmin && curlist.modefield)
					switch (curchr)
					{
						case 0: 
							if (type(curlist.tailfield) == 12)
								curval = mem[curlist.tailfield+1].int_;
							break;
						case 1: 
							if (type(curlist.tailfield) == 11)
								curval = mem[curlist.tailfield+1].int_;
							break;
						case 2: 
							if (type(curlist.tailfield) == 10)
							{
								curval = info(curlist.tailfield+1);
								if (subtype(curlist.tailfield) == 99)
									curvallevel = 3;
							}
					}
				else 
					if (curlist.modefield == 1 &&curlist.tailfield == curlist.headfield)
						switch (curchr)
						{
							case 0: 
								curval = lastpenalty;
								break;
							case 1: 
								curval = lastkern;
								break;
							case 2: 
								if (lastglue != 65535)
									curval = lastglue;
						}
			}
			break;
		default:
			if (interaction == 3)
				printnl(262); //! 
			print(685); //You can't use `
			printcmdchr(curcmd, curchr);
			print(686); //' after 
			printesc(537); //the
			helpptr = 1;
			helpline[0] = 684; //I'm forgetting what you said and using zero instead.
			error();
			if (level != 5)
			{
				curval = 0;
				curvallevel = 1;
			}
			else
			{
				curval = 0;
				curvallevel = 0;
			}
	};
	while (curvallevel > level)
	{
		if (curvallevel == 2)
			curval = mem[curval+1].int_;
		else 
			if (curvallevel == 3)
			muerror();
		curvallevel--;
	}
	if (negative)
		if (curvallevel >= 2)
		{
			curval = newspec(curval);
			mem[curval+1].int_ = -mem[curval+1].int_;
			mem[curval+2].int_ = -mem[curval+2].int_;
			mem[curval+3].int_ = -mem[curval+3].int_;
		}
		else
			curval = -curval;
	else 
		if (curvallevel >= 2 && curvallevel <= 3)
			link(curval)++;
}
