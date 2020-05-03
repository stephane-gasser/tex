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
	if (fontparams[fam_fnt(2)] < 22 || fontparams[fam_fnt(18)] < 22 || fontparams[fam_fnt(34)] < 22)
	{
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
	else if (fontparams[fam_fnt(3)] < 13 || fontparams[fam_fnt(19)] < 13 || fontparams[fam_fnt(35)] < 13)
	{
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
	m = mode;
	l = false;
	p = finmlist(0);
	if (mode == -m)
	{
		getxtoken();
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
		a = hpack(link(temp_head), 0, 1);
		unsave();
		saveptr--;
		if (savestack[saveptr].int_ == 1)
			l = true;
		danger = false;
		if (fontparams[fam_fnt(2)] < 22 || fontparams[fam_fnt(18)] < 22 || fontparams[fam_fnt(34)] < 22)
		{
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
			if (fontparams[fam_fnt(3)] < 13 || fontparams[fam_fnt(19)] < 13 || fontparams[fam_fnt(35)] < 13)
			{
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
		m = mode;
		p = finmlist(0);
	}
	else
		a = 0;
	if (m < 0)
	{
		tail_append(newmath(dimen_par(math_surround_code), 0));
		curmlist = p;
		curstyle = 2;
		mlistpenalties = mode > 0;
		mlisttohlist();
		link(tail) = link(temp_head);
		while (link(tail))
			tail = link(tail);
		tail_append(newmath(dimen_par(math_surround_code), 1));
		space_factor = 1000;
		unsave();
	}
	else
	{
		if (a == 0)
		{
			getxtoken();
			if (curcmd != math_shift)
			{
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
		p = link(temp_head);
		adjusttail = adjust_head;
		b = hpack(p, 0, 1);
		p = link(b+5);
		t = adjusttail;
		adjusttail = 0;
		w = mem[b+1].int_;
		z = dimen_par(display_width_code);
		s = dimen_par(display_indent_code);
		if (a == 0 || danger)
		{
			e = 0;
			q = 0;
		}
		else
		{
			e = mem[a+1].int_;
			q = e+fontinfo[6+parambase[fam_fnt(2)]].int_;
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
		tail_append(newpenalty(int_par(pre_display_penalty_code)));
		if (d+s <= dimen_par(pre_display_size_code) || l)
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
			tail_append(newpenalty(10000));
		}
		else
			tail_append(newparamglue(g1));
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
			tail_append(newpenalty(10000));
			mem[a+4].int_ = s+z-mem[a+1].int_;
			appendtovlist(a);
			g2 = 0;
		}
		if (t != adjust_head)
		{
			link(tail) = link(adjust_head);
			tail = t;
		}
		tail_append(newpenalty(int_par(post_display_penalty_code)));
		if (g2 > 0)
			tail_append(newparamglue(g2));
		resumeafterdisplay();
	}
}
