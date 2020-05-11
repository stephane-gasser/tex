#include "doregistercommand.h"
#include "getxtoken.h"
#include "printnl.h"
#include "print.h"
#include "printcmdchr.h"
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
				printnl(262); //! 
				print(685); //You can't use `
				printcmdchr(curcmd, curchr);
				print(686); //' after 
				printcmdchr(q, 0);
				helpptr = 1;
				helpline[0] = 1209; //I'm forgetting what you said and not changing anything.
				error();
				return;
			}
		}
		p = curchr;
		scaneightbitint();
		switch (p)
		{
			case 0: 
				l = curval+count_base;
				break;
			case 1: 
				l = curval+scaled_base;
				break;
			case 2: 
				l = curval+skip_base;
				break;
			case 3: 
				l = curval+mu_skip_base;
				break;
		}
	} while (false);
	if (q == register_)
		scanoptionalequals();
	else 
		if (scankeyword(1205)) //by
			aritherror = false;
	if (q < multiply)
		if (p < 2)
		{
			if (p == 0)
				scanint();
			else
				scandimen(false, false, false);
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
		if (p < 2)
			if (q == multiply)
				if (p == 0)
					curval = multandadd(eqtb[l].int_, curval, 0, infinity);
				else
					curval = multandadd(eqtb[l].int_, curval, 0, max_dimen);
			else
				curval = xovern(eqtb[l].int_, curval);
		else
		{
			s = equiv(l);
			r = newspec(s);
			if (q == multiply)
			{
				width(r) = multandadd(width(s), curval, 0, max_dimen);
				depth(r) = multandadd(depth(s), curval, 0, max_dimen);
				height(r) = multandadd(height(s), curval, 0, max_dimen);
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
		printnl(262); //! 
		print(1206); //Arithmetic overflow
		helpptr = 2;
		helpline[1] = 1207; //I can't carry out that multiplication or division,
		helpline[0] = 1208; //since the result is out of range.
		if (p >= 2)
			deleteglueref(curval);
		error();
		return;
	}
	if (p < 2)
		if (a >= 4)
			geqworddefine(l, curval);
		else
		eqworddefine(l, curval);
	else
	{
		trapzeroglue();
		if (a >= 4)
			geqdefine(l, 117, curval);
		else
			eqdefine(l, 117, curval);
	}
}
