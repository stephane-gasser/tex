#include "aftermath.h"
#include "impression.h"
#include "erreur.h"
#include "flushmath.h"
#include "lecture.h"
#include "formule.h"
#include "sauvegarde.h"
#include "boite.h"
#include "noeud.h"
#include "half.h"
#include "resumeafterdisplay.h"
#include "alignement.h"
#include "police.h"

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
	auto p = finmlist(nullptr);
	BoxNode *a; // box containing equation number
	Token t;
	if (mode == -m)
	{
		t = getxtoken();
		backerror(t, "Display math should end with $$", "The `$' that I just saw supposedly matches a previous `$$'.\nSo I shall assume that you typed `$$' both times.");
		curmlist = p;
		curstyle = 2;
		mlistpenalties = false;
		mlisttohlist();
		a = hpack(temp_head->link, 0, additional);
		unsave();
		auto s0 = savestack.back()->int_;
		savestack.pop_back();
		if (s0 == 1)
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
		p = finmlist(nullptr);
	}
	else
		a = nullptr;
	if (m < 0)
	{
		tail_append(new MathNode(math_surround(), before));
		curmlist = p;
		curstyle = 2;
		mlistpenalties = mode > 0;
		mlisttohlist();
		followUntilEnd(temp_head, tail);
		tail_append(new MathNode(math_surround(), after));
		space_factor = 1000;
		unsave();
	}
	else
	{
		if (a == nullptr)
		{
			t = getxtoken();
			if (t.cmd != math_shift)
				backerror(t, "Display math should end with $$", "The `$' that I just saw supposedly matches a previous `$$'.\nSo I shall assume that you typed `$$' both times.");
		}
		curmlist = p; 
		curstyle = 0;
		mlistpenalties = false;
		mlisttohlist();
		auto p = temp_head->link;
		adjusttail = adjust_head;
		auto b = hpack(p, 0, additional);
		p = b->list_ptr;
		auto tt = adjusttail;
		adjusttail = nullptr;
		auto w = b->width;
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
			e = a->width;
			q = e+math_quad(0);
		}
		if (w+q > z)
		{
			if (e && (w-totalshrink[0]+q <= z || totalshrink[1] || totalshrink[2] || totalshrink[3]))
			{
				delete b;
				b = hpack(p, z-q, exactly);
			}
			else
			{
				e = 0;
				if (w > z)
				{
					delete b;
					b = hpack(p, z, exactly);
				}
			}
			w = b->width;
		}
		auto d = half(z-w);
		if (e > 0 && d < 2*e)
		{
			d = half(z-w-e); 
			if (p && p->type == glue_node)
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
			a->shift_amount = s;
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
				a->link = r;
				r->link = b;
				b = a;
				d = 0;
			}
			else
			{
				b->link = r;
				r->link = a;
			}
			b = hpack(b, 0, additional);
		}
		b->shift_amount = s+d;
		appendtovlist(b);
		if (a && e == 0 && !l)
		{
			tail_append(new PenaltyNode(10000));
			a->shift_amount = s+z-a->width;
			appendtovlist(a);
			g2 = 0;
		}
		if (tt != adjust_head)
		{
			tail->link = adjust_head->link;
			tail = tt;
		}
		tail_append(new PenaltyNode(post_display_penalty()));
		if (g2 > 0)
			tail_append(new GlueNode(g2));
		resumeafterdisplay(t);
	}
}
