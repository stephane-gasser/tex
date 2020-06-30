#include "doregistercommand.h"
#include "getxtoken.h"
#include "impression.h"
#include "error.h"
#include "scaneightbitint.h"
#include "scanoptionalequals.h"
#include "scankeyword.h"
#include "scanint.h"
#include "scandimen.h"
#include "scanglue.h"
#include "newspec.h"
#include "deleteglueref.h"
#include "multandadd.h"
#include "xovern.h"
#include "trapzeroglue.h"
#include "geqworddefine.h"
#include "eqworddefine.h"
#include "geqdefine.h"
#include "eqdefine.h"
#include "texte.h"

void doregistercommand(smallnumber a)
{
	halfword l, q, r, s;
	char  p;
	q = curcmd;
	do 
	{
		if (q != register_)
		{
			getxtoken();
			if (curcmd >= assign_int && curcmd <= assign_mu_glue) // assign_int, assign_dimen, assign_int, assign_mu_glue
			{
				l = curchr;
				p = curcmd-assign_int;
				continue;
			}
			if (curcmd != register_)
			{
				print_err("You can't use `"+cmdchr(curcmd, curchr)+"' after "+cmdchr(q, 0));
				helpptr = 1;
				helpline[0] = "I'm forgetting what you said and not changing anything.";
				error();
				return;
			}
		}
		p = curchr;
		scaneightbitint();
		switch (p)
		{
			case int_val: 
				l = curval+count_base;
				break;
			case dimen_val: 
				l = curval+scaled_base;
				break;
			case glue_val: 
				l = curval+skip_base;
				break;
			case mu_val: 
				l = curval+mu_skip_base;
				break;
		}
	} while (false);
	if (q == register_)
		scanoptionalequals();
	else 
		if (scankeyword("by"))
			aritherror = false;
	if (q < multiply)
		if (p < glue_val)
		{
			if (p == int_val)
				scanint();
			else
				scan_normal_dimen();
			if (q == advance)
				curval += eqtb[l].int_;
		}
		else
		{
			scanglue(p);
			if (q == advance)
			{
				q = newspec(curval);
				r = equiv(l);
				deleteglueref(curval);
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
				curval = q;
			}
		}
	else
	{
		scanint();
		if (p < glue_val)
			if (q == multiply)
				if (p == int_val)
					curval = mult_integers(eqtb[l].int_, curval);
				else
					curval = nx_plus_y(eqtb[l].int_, curval, 0);
			else
				curval = xovern(eqtb[l].int_, curval);
		else
		{
			s = equiv(l);
			r = newspec(s);
			if (q == multiply)
			{
				width(r) = nx_plus_y(width(s), curval, 0);
				depth(r) = nx_plus_y(depth(s), curval, 0);
				height(r) = nx_plus_y(height(s), curval, 0);;
			}
			else
			{
				width(r) = xovern(width(s), curval);
				depth(r) = xovern(depth(s), curval);
				height(r) = xovern(height(s), curval);
			}
			curval = r;
		}
	}
	if (aritherror)
	{
		print_err("Arithmetic overflow");
		helpptr = 2;
		helpline[1] = "I can't carry out that multiplication or division,";
		helpline[0] = "since the result is out of range.";
		if (p >= 2)
			deleteglueref(curval);
		error();
		return;
	}
	if (p < 2)
		word_define(a, l, curval);
	else
	{
		trapzeroglue();
		define(a, l, glue_ref, curval);
	}
}
