#include "newfont.h"
#include "openlogfile.h"
#include "getrtoken.h"
#include "impression.h"
#include "makestring.h"
#include "geqdefine.h"
#include "eqdefine.h"
#include "scanoptionalequals.h"
#include "scanfilename.h"
#include "scankeyword.h"
#include "scandimen.h"
#include "scanint.h"
#include "erreur.h"
#include "xnoverd.h"
#include "readfontinfo.h"
#include "texte.h"

static void erreurNewfont1(scaled s)
{
	print_err("Improper `at' size ("+asScaled(s)+"pt), replaced by 10pt");
	helpptr = 2;
	helpline[1] = "I can only handle fonts at positive sizes that are";
	helpline[0] = "less than 2048pt, so I've changed what you said to 10pt.";
	error();
}

static void erreurNewfont2(void)
{
	print_err("Illegal magnification has been changed to 1000");
	helpptr = 1;
	helpline[0] = "The magnification ratio must be between 1 and 0x80'00.";
	interror(curval);
}

void newfont(smallnumber a)
{
	halfword u;
	scaled s;
	internalfontnumber f;
	std::string t;
	char oldsetting;
	if (jobname == "")
		openlogfile();
	getrtoken();
	u = curcs;
	if (u >= hash_base)
		t = TXT(text(u));
	else 
		if (u >= single_base)
			if (u == txt("char"))
				t = "FONT";
			else
				t = std::string(1, char(u-single_base));
		else
		{
			oldsetting = selector;
			selector = new_string;
			print("FONT");
			print(std::string(1, u-1));
			selector = oldsetting;
			str_room(1);
			t = makestring();
		}
	define(a, u, set_font, null_font);
	scanoptionalequals();
	scanfilename();
	nameinprogress = true;
	if (scankeyword("at"))
	{
		scan_normal_dimen();
		s = curval;
		if (s <= 0 || s >= 134217728)
		{
			erreurNewfont1(s);
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
				erreurNewfont2();
				s = -1000;
			}
		}
		else
			s = -1000;
	nameinprogress = false;
	auto flushablestring = TXT(strptr-1);
	for (f = 1; f <= fontptr; f++)
		if (fontname[f] == curname && fontarea[f] == curarea)
		{
			if (curname == flushablestring)
			{
				flush_string();
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
	text(frozen_null_font+f) = txt(t);
}
