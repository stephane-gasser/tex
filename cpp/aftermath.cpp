#include "aftermath.h"
#include "printnl.h"
#include "print.h"
#include "error.h"
#include "flushmath.h"
#include "getxtoken.h"
#include "finmlist.h"
#include "mlisttohlist.h"
#include "backerror.h"
#include "unsave.h"
#include "hpack.h"
#include "newmath.h"
#include "freenode.h"
#include "half.h"
#include "newpenalty.h"
#include "appendtovlist.h"
#include "newparamglue.h"
#include "newkern.h"
#include "resumeafterdisplay.h"

void aftermath(void)
{
	bool l;
	int m;
	halfword p, a, b;
	scaled w, z, e, q, d, s;
	smallnumber g1, g2;
	halfword r, t;
	bool danger = false;
	if (fontparams[eqtb[3937].hh.rh] < 22 || fontparams[eqtb[3953].hh.rh] < 22 || fontparams[eqtb[3969].hh.rh] < 22)
	{
		if (interaction == 3)
			printnl(262); //! 
		print(1157); //Math formula deleted: Insufficient symbol fonts
		helpptr = 3;
		helpline[2] = 1158; //0Sorry, but I can't typeset math unless \textfont 2
		helpline[1] = 1159; //and \scriptfont 2 and \scriptscriptfont 2 have all
		helpline[0] = 1160; //The \fontdimen values needed in math symbol fonts.
		error();
		flushmath();
		danger = true;
	}
	else if (fontparams[eqtb[3938].hh.rh] < 13 || fontparams[eqtb[3954].hh.rh] < 13 || fontparams[eqtb[3970].hh.rh] < 13)
	{
		if (interaction == 3)
			printnl(262); //! 
		print(1161); //Math formula deleted: Insufficient extension fonts
		helpptr = 3;
		helpline[2] = 1162; //Sorry, but I can't typeset math unless \textfont 3
		helpline[1] = 1163; //and \scriptfont 3 and \scriptscriptfont 3 have all
		helpline[0] = 1164; //the \fontdimen values needed in math extension fonts.
		error();
		flushmath();
		danger = true;
	}
	m = curlist.modefield;
	l = false;
	p = finmlist(0);
	if (curlist.modefield == -m)
	{
		getxtoken();
		if (curcmd != 3)
			if (interaction == 3)
				printnl(262); //! 
		print(1165); //Display math should end with $$
		helpptr = 2;
		helpline[1] = 1166; //The `$' that I just saw supposedly matches a previous `$$'.
		helpline[0] = 1167; //So I shall assume that you typed `$$' both times.
		backerror();
		curmlist = p;
		curstyle = 2;
		mlistpenalties = false;
		mlisttohlist();
		a = hpack(link(29997), 0, 1);
		unsave();
		saveptr--;
		if (savestack[saveptr].int_ == 1)
			l = true;
		danger = false;
		if (fontparams[eqtb[3937].hh.rh] < 22 || fontparams[eqtb[3953].hh.rh] < 22 || fontparams[eqtb[3969].hh.rh] < 22)
		{
			if (interaction == 3)
				printnl(262); //! 
			print(1157); //Math formula deleted: Insufficient symbol fonts
			helpptr = 3;
			helpline[2] = 1158; //Sorry, but I can't typeset math unless \textfont 2
			helpline[1] = 1159; //and \scriptfont 2 and \scriptscriptfont 2 have all
			helpline[0] = 1160; //the \fontdimen values needed in math symbol fonts.
			error();
			flushmath();
			danger = true;
		}
		else 
			if (fontparams[eqtb[3938].hh.rh] < 13 || fontparams[eqtb[3954].hh.rh] < 13 || fontparams[eqtb[3970].hh.rh] < 13)
			{
				if (interaction == 3)
					printnl(262); //! 
				print(1161); //Math formula deleted: Insufficient extension fonts
				helpptr = 3;
				helpline[2] = 1162; //Sorry, but I can't typeset math unless \textfont 3
				helpline[1] = 1163; //and \scriptfont 3 and \scriptscriptfont 3 have all
				helpline[0] = 1164; //the \fontdimen values needed in math extension fonts.
				error();
				flushmath();
				danger = true;
			}
		m = curlist.modefield;
		p = finmlist(0);
	}
	else
		a = 0;
	if (m < 0)
	{
		link(curlist.tailfield) = newmath(eqtb[5831].int_, 0);
		curlist.tailfield = link(curlist.tailfield);
		curmlist = p;
		curstyle = 2;
		mlistpenalties = curlist.modefield > 0;
		mlisttohlist();
		link(curlist.tailfield) = link(29997);
		while (link(curlist.tailfield))
			curlist.tailfield = link(curlist.tailfield);
		link(curlist.tailfield) = newmath(eqtb[5831].int_, 1);
		curlist.tailfield = link(curlist.tailfield);
		curlist.auxfield.hh.lh = 1000;
		unsave();
	}
	else
	{
		if (a == 0)
		{
			getxtoken();
			if (curcmd != 3)
			{
				if (interaction == 3)
					printnl(262); //! 
				print(1165); //Display math should end with $$
				helpptr = 2;
				helpline[1] = 1166; //The `$' that I just saw supposedly matches a previous `$$'.
				helpline[0] = 1167; //So I shall assume that you typed `$$' both times.
				backerror();
			}
		}
		curmlist = p;
		curstyle = 0;
		mlistpenalties = false;
		mlisttohlist();
		p = link(29997);
		adjusttail = 29995;
		b = hpack(p, 0, 1);
		p = link(b+5);
		t = adjusttail;
		adjusttail = 0;
		w = mem[b+1].int_;
		z = eqtb[5844].int_;
		s = eqtb[5845].int_;
		if (a == 0 || danger)
		{
			e = 0;
			q = 0;
		}
		else
		{
			e = mem[a+1].int_;
			q = e+fontinfo[6+parambase[eqtb[3937].hh.rh]].int_;
		}
		if (w+q > z)
		{
			if (e && (w-totalshrink[0]+q <= z || totalshrink[1] || totalshrink[2] || totalshrink[3]))
			{
				freenode(b, 7);
				b = hpack(p, z-q, 0);
			}
			else
			{
				e = 0;
				if (w > z)
				{
					freenode(b, 7);
					b = hpack(p, z, 0);
				}
			}
			w = mem[b+1].int_;
		}
		d = half(z-w);
		if (e > 0 && d < 2*e)
		{
			d = half(z-w-e);
			if (p && p < himemmin && type(p) == glue_node) //10
			d = 0;
		}
		link(curlist.tailfield) = newpenalty(eqtb[5274].int_);
		curlist.tailfield = link(curlist.tailfield);
		if (d+s <= eqtb[5843].int_ || l)
		{
			g1 = 3;
			g2 = 4;
		}
		else
		{
			g1 = 5;
			g2 = 6;
		}
		if (l && e == 0)
		{
			mem[a+4].int_ = s;
			appendtovlist(a);
			link(curlist.tailfield) = newpenalty(10000);
			curlist.tailfield = link(curlist.tailfield);
		}
		else
		{
			link(curlist.tailfield) = newparamglue(g1);
			curlist.tailfield = link(curlist.tailfield);
		}
		if (e)
		{
			r = newkern(z-w-e-d);
			if (l)
			{
				link(a) = r;
				link(r) = b;
				b = a;
				d = 0;
			}
			else
			{
				link(b) = r;
				link(r) = a;
			}
			b = hpack(b, 0, 1);
		}
		mem[b+4].int_ = s+d;
		appendtovlist(b);

		if (a && e == 0 && !l)
		{
			link(curlist.tailfield) = newpenalty(10000);
			curlist.tailfield = link(curlist.tailfield);
			mem[a+4].int_ = s+z-mem[a+1].int_;
			appendtovlist(a);
			g2 = 0;
		}
		if (t != 29995)
		{
			link(curlist.tailfield) = link(29995);
			curlist.tailfield = t;
		}
		link(curlist.tailfield) = newpenalty(eqtb[5275].int_);
		curlist.tailfield = link(curlist.tailfield);
		if (g2 > 0)
		{
			link(curlist.tailfield) = newparamglue(g2);
			curlist.tailfield = link(curlist.tailfield);
		}
		resumeafterdisplay();
	}
}
