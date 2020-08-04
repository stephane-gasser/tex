#include "aftermath.h"
#include "impression.h"
#include "erreur.h"
#include "flushmath.h"
#include "lecture.h"
#include "finmlist.h"
#include "mlisttohlist.h"
#include "unsave.h"
#include "hpack.h"
#include "noeud.h"
#include "half.h"
#include "resumeafterdisplay.h"
#include "texte.h"
#include "police.h"

static int display_width(void) { return dimen_par(display_width_code); }
static int math_surround(void) { return dimen_par(math_surround_code); }
static int pre_display_size(void) { return dimen_par(pre_display_size_code); }

constexpr int total_mathsy_params = 22;
constexpr int total_mathex_params = 13;

//! Action procedure for use in maincontrol()
void aftermath(void)
{
	bool danger = false; // not enough symbol fonts are present
	if (fonts[fam_fnt(2+text_size)].params < total_mathsy_params 
	 || fonts[fam_fnt(2+script_size)].params < total_mathsy_params 
	 || fonts[fam_fnt(2+script_script_size)].params < total_mathsy_params)
	{
		error("Math formula deleted: Insufficient symbol fonts", "Sorry, but I can't typeset math unless \\textfont 2\nand \\scriptfont 2 and \\scriptscriptfont 2 have all\nThe \\fontdimen values needed in math symbol fonts.");
		flushmath();
		danger = true;
	}
	else 
		if (fonts[fam_fnt(3+text_size)].params < total_mathex_params
		 || fonts[fam_fnt(3+script_size)].params < total_mathex_params
		 || fonts[fam_fnt(3+script_script_size)].params < total_mathex_params)
		{
			error("Math formula deleted: Insufficient extension fonts", "Sorry, but I can't typeset math unless \\textfont 3\nand \\scriptfont 3 and \\scriptscriptfont 3 have all\nthe \\fontdimen values needed in math extension fonts.");
			flushmath();
			danger = true;
		}
	int m = mode; // \a mmode or \a -mmode
	bool l = false; // `\\leqno' instead of `\\eqno'
	LinkedNode *p;
	p->num = finmlist(0);
	Token t;
	halfword a; // box containing equation number
	if (mode == -m)
	{
		t = getxtoken();
		backerror(t, "Display math should end with $$", "The `$' that I just saw supposedly matches a previous `$$'.\nSo I shall assume that you typed `$$' both times.");
		curmlist = p->num;
		curstyle = 2;
		mlistpenalties = false;
		mlisttohlist();
		a = hpack(temp_head->link->num, 0, additional);
		unsave();
		saveptr--;
		if (saved(0) == 1)
			l = true;
		danger = false;
		if (fonts[fam_fnt(2+text_size)].params < total_mathsy_params 
		 || fonts[fam_fnt(2+script_size)].params < total_mathsy_params 
		 || fonts[fam_fnt(2+script_script_size)].params < total_mathsy_params)
		{
			error("Math formula deleted: Insufficient symbol fonts", "Sorry, but I can't typeset math unless \\textfont 2\nand \\scriptfont 2 and \\scriptscriptfont 2 have all\nthe \\fontdimen values needed in math symbol fonts.");
			flushmath();
			danger = true;
		}
		else 
			if (fonts[fam_fnt(3+text_size)].params < total_mathex_params
			 || fonts[fam_fnt(3+script_size)].params < total_mathex_params
			 || fonts[fam_fnt(3+script_script_size)].params < total_mathex_params)
			{
				error("Math formula deleted: Insufficient extension fonts", "Sorry, but I can't typeset math unless \\textfont 3\nand \\scriptfont 3 and \\scriptscriptfont 3 have all\nthe \\fontdimen values needed in math extension fonts.");
				flushmath();
				danger = true;
			}
		m = mode;
		p->num = finmlist(0);
	}
	else
		a = 0;
	if (m < 0)
	{
		tail_append(newmath(math_surround(), before));
		curmlist = p->num;
		curstyle = 2;
		mlistpenalties = mode > 0;
		mlisttohlist();
		tail->link = temp_head->link;
		while (tail->link)
			tail = tail->link;
		tail_append(newmath(math_surround(), after));
		space_factor = 1000;
		unsave();
	}
	else
	{
		if (a == 0)
		{
			t = getxtoken();
			if (t.cmd != math_shift)
				backerror(t, "Display math should end with $$", "The `$' that I just saw supposedly matches a previous `$$'.\nSo I shall assume that you typed `$$' both times.");
		}
		curmlist = p->num;
		curstyle = 0;
		mlistpenalties = false;
		mlisttohlist();
		p = temp_head->link;
		adjusttail = adjust_head->num;
		auto b = hpack(p->num, 0, additional);
		p->num = list_ptr(b);
		auto tt = adjusttail;
		adjusttail = 0;
		auto w = width(b);
		auto z = display_width();
		auto s = display_indent();
		scaled e, q;
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
				b = hpack(p->num, z-q, exactly);
			}
			else
			{
				e = 0;
				if (w > z)
				{
					freenode(b, box_node_size);
					b = hpack(p->num, z, exactly);
				}
			}
			w = width(b);
		}
		auto d = half(z-w);
		if (e > 0 && d < 2*e)
		{
			d = half(z-w-e); 
			if (p && !p->is_char_node() && p->type == glue_node)
				d = 0;
		}
		tail_append(new PenaltyNode(pre_display_penalty()));
		smallnumber g1 = 5, g2 = 6;
		if (d+s <= pre_display_size() || l)
		{
			g1 = 3;
			g2 = 4;
		}
		if (l && e == 0)
		{
			shift_amount(a) = s;
			appendtovlist(a);
			tail_append(new PenaltyNode(10000));
		}
		else
			tail_append(new GlueNode(g1));
		if (e)
		{
			auto r = new KernNode(z-w-e-d);
			if (l)
			{
				link(a) = r->num;
				r->link->num = b;
				b = a;
				d = 0;
			}
			else
			{
				link(b) = r->num;
				r->link->num = a;
			}
			b = hpack(b, 0, additional);
		}
		shift_amount(b) = s+d;
		appendtovlist(b);
		if (a && e == 0 && !l)
		{
			tail_append(new PenaltyNode(10000));
			shift_amount(a) = s+z-width(a);
			appendtovlist(a);
			g2 = 0;
		}
		if (tt != adjust_head->num)
		{
			tail->link = adjust_head->link;
			tail->num = tt;
		}
		tail_append(new PenaltyNode(post_display_penalty()));
		if (g2 > 0)
			tail_append(new GlueNode(g2));
		resumeafterdisplay(t);
	}
}
