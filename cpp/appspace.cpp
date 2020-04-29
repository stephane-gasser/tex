#include "appspace.h"
#include "newparamglue.h"
#include "newspec.h"
#include "xnoverd.h"
#include "newglue.h"

void appspace(void)
{
	halfword q;
	if (curlist.auxfield.hh.lh >= 2000 && eqtb[2895].hh.rh)
		q = newparamglue(13);
	else
	{
		if (eqtb[2894].hh.rh)
			mainp = eqtb[2894].hh.rh;
		else
		{
			mainp = fontglue[eqtb[3934].hh.rh];
			if (mainp == 0)
			{
				mainp = newspec(0);
				maink = parambase[eqtb[3934].hh.rh]+2;
				mem[mainp+1].int_ = fontinfo[maink].int_;
				mem[mainp+2].int_ = fontinfo[maink+1].int_;
				mem[mainp+3].int_ = fontinfo[maink+2].int_;
				fontglue[eqtb[3934].hh.rh] = mainp;
			}
		}
		mainp = newspec(mainp);
		if (curlist.auxfield.hh.lh >= 2000)
			mem[mainp+1].int_ += fontinfo[7+parambase[eqtb[3934].hh.rh]].int_;
		mem[mainp+2].int_ = xnoverd(mem[mainp+2].int_, curlist.auxfield.hh.lh, 1000);
		mem[mainp+3].int_ = xnoverd(mem[mainp+3].int_, 1000, curlist.auxfield.hh.lh);
		q = newglue(mainp);
		link(mainp) = 0;
	}
	link(curlist.tailfield) = q;
	curlist.tailfield = q;
}
