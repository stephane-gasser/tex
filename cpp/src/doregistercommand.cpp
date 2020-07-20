#include "doregistercommand.h"
#include "impression.h"
#include "erreur.h"
#include "lecture.h"
#include "noeud.h"
#include "deleteglueref.h"
#include "multandadd.h"
#include "xovern.h"
#include "trapzeroglue.h"
#include "geqworddefine.h"
#include "eqworddefine.h"
#include "geqdefine.h"
#include "eqdefine.h"
#include "texte.h"

void doregistercommand(smallnumber a, Token t)
{
	halfword l, q, r, s;
	halfword p;
	q = t.cmd;
	do 
	{
		if (q != register_)
		{
			t = getxtoken();
			if (t.cmd >= assign_int && t.cmd <= assign_mu_glue) // assign_int, assign_dimen, assign_int, assign_mu_glue
			{
				l = t.chr;
				p = t.cmd-assign_int;
				continue;
			}
			if (t.cmd != register_)
			{
				Token tk;
				tk.cmd = q;
				tk.chr = 0;
				error("You can't use `"+cmdchr(t)+"' after "+cmdchr(tk), "I'm forgetting what you said and not changing anything.");
				return;
			}
		}
		p = t.chr;
		switch (p)
		{
			case int_val: 
				l = scaneightbitint()+count_base;
				break;
			case dimen_val: 
				l = scaneightbitint()+scaled_base;
				break;
			case glue_val: 
				l = scaneightbitint()+skip_base;
				break;
			case mu_val: 
				l = scaneightbitint()+mu_skip_base;
				break;
		}
	} while (false);
	if (q == register_)
		scanoptionalequals();
	else 
		if (scankeyword("by"))
			aritherror = false;
	int val;
	if (q < multiply)
		if (p < glue_val)
		{
			if (p == int_val)
				val = scanint();
			else
				val = scan_normal_dimen();
			if (q == advance)
				val += eqtb[l].int_;
		}
		else
		{
			val = scanglue(p);
			if (q == advance)
			{
				q = newspec(val);
				r = equiv(l);
				deleteglueref(val);
				width(q) += width(r);
				if (stretch(q) == 0)
					stretch_order(q) = 0;
				if (stretch_order(q) == stretch_order(r))
					stretch(q) += stretch(r);
				else 
					if (stretch_order(q) < stretch_order(r) && stretch(r))
					{
						stretch(q) = stretch(r);
						stretch_order(q) = stretch_order(r);
					}
				if (shrink(q) == 0)
					shrink_order(q) = 0;
				if (shrink_order(q) == shrink_order(r))
					shrink(q) += shrink(r);
				else 
					if (shrink_order(q) < shrink_order(r) && shrink(r))
					{
						shrink(q) = shrink(r);
						shrink_order(q) = shrink_order(r);
					}
				val = q;
			}
		}
	else
	{
		val = scanint();
		if (p < glue_val)
			if (q == multiply)
				if (p == int_val)
					val = mult_integers(eqtb[l].int_, val);
				else
					val = nx_plus_y(eqtb[l].int_, val, 0);
			else
				val = xovern(eqtb[l].int_, val);
		else
		{
			s = equiv(l);
			r = newspec(s);
			if (q == multiply)
			{
				width(r) = nx_plus_y(width(s), val, 0);
				depth(r) = nx_plus_y(depth(s), val, 0);
				height(r) = nx_plus_y(height(s), val, 0);;
			}
			else
			{
				width(r) = xovern(width(s), val);
				depth(r) = xovern(depth(s), val);
				height(r) = xovern(height(s), val);
			}
			val = r;
		}
	}
	if (aritherror)
	{
		error("Arithmetic overflow", "I can't carry out that multiplication or division,\nsince the result is out of range.");
		if (p >= 2)
			deleteglueref(val);
		return;
	}
	if (p < 2)
		word_define(a, l, val);
	else
	{
		trapzeroglue(val);
		define(a, l, glue_ref, val);
	}
}
