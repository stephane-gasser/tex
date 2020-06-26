#include "aftermath.h"
#include "impression.h"
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
#include "texte.h"

static int display_width(void) { return dimen_par(display_width_code); }
static int math_surround(void) { return dimen_par(math_surround_code); }
static int pre_display_size(void) { return dimen_par(pre_display_size_code); }

constexpr int total_mathsy_params = 22;
constexpr int total_mathex_params = 13;

//! Action procedure for use in maincontrol()
void aftermath(void)
{
	bool l; // `\\leqno' instead of `\\eqno'
	int m; // \a mmode or \a -mmode
	halfword a; // box containing equation number
	halfword p, b;
	scaled w, z, e, q, d, s;
	smallnumber g1, g2;
	halfword r, t;
	bool danger = false; // not enough symbol fonts are present
	if (fontparams[fam_fnt(2+text_size)] < total_mathsy_params 
	 || fontparams[fam_fnt(2+script_size)] < total_mathsy_params 
	 || fontparams[fam_fnt(2+script_script_size)] < total_mathsy_params)
	{
		print_err("Math formula deleted: Insufficient symbol fonts");
		helpptr = 3;
		helpline[2] = "Sorry, but I can't typeset math unless \\textfont 2";
		helpline[1] = "and \\scriptfont 2 and \\scriptscriptfont 2 have all";
		helpline[0] = "The \\fontdimen values needed in math symbol fonts.";
		error();
		flushmath();
		danger = true;
	}
	else 
		if (fontparams[fam_fnt(3+text_size)] < total_mathex_params
		 || fontparams[fam_fnt(3+script_size)] < total_mathex_params
		 || fontparams[fam_fnt(3+script_script_size)] < total_mathex_params)
		{
			print_err("Math formula deleted: Insufficient extension fonts"); 
			helpptr = 3;
			helpline[2] = "Sorry, but I can't typeset math unless \\textfont 3";
			helpline[1] = "and \\scriptfont 3 and \\scriptscriptfont 3 have all";
			helpline[0] = "the \\fontdimen values needed in math extension fonts.";
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
		print_err("Display math should end with $$"); 
		helpptr = 2;
		helpline[1] = "The `$' that I just saw supposedly matches a previous `$$'.";
		helpline[0] = "So I shall assume that you typed `$$' both times.";
		backerror();
		curmlist = p;
		curstyle = 2;
		mlistpenalties = false;
		mlisttohlist();
		a = hpack(link(temp_head), 0, additional);
		unsave();
		saveptr--;
		if (savestack[saveptr].int_ == 1)
			l = true;
		danger = false;
		if (fontparams[fam_fnt(2+text_size)] < total_mathsy_params 
		 || fontparams[fam_fnt(2+script_size)] < total_mathsy_params 
		 || fontparams[fam_fnt(2+script_script_size)] < total_mathsy_params)
		{
			print_err("Math formula deleted: Insufficient symbol fonts");
			helpptr = 3;
			helpline[2] = "Sorry, but I can't typeset math unless \\textfont 2";
			helpline[1] = "and \\scriptfont 2 and \\scriptscriptfont 2 have all";
			helpline[0] = "the \\fontdimen values needed in math symbol fonts.";
			error();
			flushmath();
			danger = true;
		}
		else 
			if (fontparams[fam_fnt(3+text_size)] < total_mathex_params
			 || fontparams[fam_fnt(3+script_size)] < total_mathex_params
			 || fontparams[fam_fnt(3+script_script_size)] < total_mathex_params)
			{
				print_err("Math formula deleted: Insufficient extension fonts"); 
				helpptr = 3;
				helpline[2] = "Sorry, but I can't typeset math unless \\textfont 3";
				helpline[1] = "and \\scriptfont 3 and \\scriptscriptfont 3 have all";
				helpline[0] = "the \\fontdimen values needed in math extension fonts.";
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
		tail_append(newmath(math_surround(), before));
		curmlist = p;
		curstyle = 2;
		mlistpenalties = mode > 0;
		mlisttohlist();
		link(tail) = link(temp_head);
		while (link(tail))
			tail = link(tail);
		tail_append(newmath(math_surround(), after));
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
				print_err("Display math should end with $$");
				helpptr = 2;
				helpline[1] = "The `$' that I just saw supposedly matches a previous `$$'.";
				helpline[0] = "So I shall assume that you typed `$$' both times.";
				backerror();
			}
		}
		curmlist = p;
		curstyle = 0;
		mlistpenalties = false;
		mlisttohlist();
		p = link(temp_head);
		adjusttail = adjust_head;
		b = hpack(p, 0, additional);
		p = list_ptr(b);
		t = adjusttail;
		adjusttail = 0;
		w = width(b);
		z = display_width();
		s = display_indent();
		if (a == 0 || danger)
		{
			e = 0;
			q = 0;
		}
		else
		{
			e = width(a);
			q = e+math_quad(0);
		}
		if (w+q > z)
		{
			if (e && (w-totalshrink[0]+q <= z || totalshrink[1] || totalshrink[2] || totalshrink[3]))
			{
				freenode(b, box_node_size);
				b = hpack(p, z-q, exactly);
			}
			else
			{
				e = 0;
				if (w > z)
				{
					freenode(b, box_node_size);
					b = hpack(p, z, exactly);
				}
			}
			w = width(b);
		}
		d = half(z-w);
		if (e > 0 && d < 2*e)
		{
			d = half(z-w-e);
			if (p && p < himemmin && type(p) == glue_node) //10
			d = 0;
		}
		tail_append(newpenalty(pre_display_penalty()));
		if (d+s <= pre_display_size() || l)
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
			shift_amount(a) = s;
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
			b = hpack(b, 0, additional);
		}
		shift_amount(b) = s+d;
		appendtovlist(b);
		if (a && e == 0 && !l)
		{
			tail_append(newpenalty(10000));
			shift_amount(a) = s+z-width(a);
			appendtovlist(a);
			g2 = 0;
		}
		if (t != adjust_head)
		{
			link(tail) = link(adjust_head);
			tail = t;
		}
		tail_append(newpenalty(post_display_penalty()));
		if (g2 > 0)
			tail_append(newparamglue(g2));
		resumeafterdisplay();
	}
}
