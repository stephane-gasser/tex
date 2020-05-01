#include "newfont.h"
#include "openlogfile.h"
#include "getrtoken.h"
#include "print.h"
#include "overflow.h"
#include "makestring.h"
#include "geqdefine.h"
#include "eqdefine.h"
#include "scanoptionalequals.h"
#include "scanfilename.h"
#include "scankeyword.h"
#include "scandimen.h"
#include "scanint.h"
#include "printnl.h"
#include "interror.h"
#include "streqstr.h"
#include "printscaled.h"
#include "error.h"
#include "xnoverd.h"
#include "readfontinfo.h"

void newfont(smallnumber a)

{
	halfword u;
	scaled s;
	internalfontnumber f;
	strnumber t;
	char oldsetting;
	strnumber flushablestring;
	if (jobname == 0)
		openlogfile();
	getrtoken();
	u = curcs;
	if (u >= 514)
		t = hash[u].rh;
	else 
		if (u >= 257)
			if (u == 513)
				t = 1218;
			else
				t = u-257;
		else
		{
			oldsetting = selector;
			selector = 21;
			print(1218); //FONT
			print(u-1);
			selector = oldsetting;
			if (poolptr+1 > poolsize)
				overflow(257, poolsize-initpoolptr); //pool size
			t = makestring();
		}
	if (a >= 4)
		geqdefine(u, 87, 0);
	else
		eqdefine(u, 87, 0);
	scanoptionalequals();
	scanfilename();
	nameinprogress = true;
	if (scankeyword(1219)) //at
	{
		scandimen(false, false, false);
		s = curval;
		if (s <= 0 || s >= 134217728)
		{
			if (interaction == 3)
				printnl(262); //! 
			print(1221); //Improper `at' size (
			printscaled(s);
			print(1222); //pt), replaced by 10pt
			helpptr = 2;
			helpline[1] = 1223; //I can only handle fonts at positive sizes that are
			helpline[0] = 1224; //less than 2048pt, so I've changed what you said to 10pt.
			error();
			s = 10*65536;
		}
	}
	else 
		if (scankeyword(1220)) //scaled
		{
			scanint();
			s = -curval;
			if (curval <= 0 || curval > 32768)
			{
				if (interaction == 3);
					printnl(262); //! 
				print(552); //Illegal magnification has been changed to 1000
				helpptr = 1;
				helpline[0] = 553; //The magnification ratio must be between 1 and 32768.
				interror(curval);
				s = -1000;
			}
		}
		else
			s = -1000;
	nameinprogress = false;
	flushablestring = strptr-1;
	for (f = 1; f <= fontptr; f++)
		if (streqstr(fontname[f], curname) && streqstr(fontarea[f], curarea))
		{
			if (curname == flushablestring)
			{
				strptr = strptr-1;
				poolptr = strstart[strptr];
				curname = fontname[f];
			}
			if (s > 0)
			{
				if (s == fontsize[f])
					break;
			}
			else 
				if (fontsize[f] == xnoverd(fontdsize[f], -s, 1000))
				break;
		}
	if (f > fontptr)
		f = readfontinfo(u, curname, curarea, s);
	equiv(u) = f;
	eqtb[frozen_null_font+f] = eqtb[u];
	hash[frozen_null_font+f].rh = t;
}
