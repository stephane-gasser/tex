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
#include "texte.h"

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
			selector = new_string;
			print("FONT");
			print(std::string(1, char(u-1)));
			selector = oldsetting;
			if (poolptr+1 > poolsize)
				overflow("pool size", poolsize-initpoolptr);
			t = makestring();
		}
	if (a >= 4)
		geqdefine(u, 87, 0);
	else
		eqdefine(u, 87, 0);
	scanoptionalequals();
	scanfilename();
	nameinprogress = true;
	if (scankeyword("at"))
	{
		scandimen(false, false, false);
		s = curval;
		if (s <= 0 || s >= 134217728)
		{
			printnl("! ");
			print("Improper `at' size (");
			printscaled(s);
			print("pt), replaced by 10pt");
			helpptr = 2;
			helpline[1] = txt("I can only handle fonts at positive sizes that are");
			helpline[0] = txt("less than 2048pt, so I've changed what you said to 10pt.");
			error();
			s = 10*0x1'00'00;
		}
	}
	else 
		if (scankeyword("scaled"))
		{
			scanint();
			s = -curval;
			if (curval <= 0 || curval > 0x80'00)
			{
				printnl("! ");
				print("Illegal magnification has been changed to 1000");
				helpptr = 1;
				helpline[0] = txt("The magnification ratio must be between 1 and 0x80'00.");
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
