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
				if (interaction == 3)
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
				l = curval+5318;
				break;
			case 1: 
				l = curval+5851;
				break;
			case 2: 
				l = curval+2900;
				break;
			case 3: 
				l = curval+3156;
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
				mem[q+1].int_ += mem[r+1].int_;
				if (mem[q+2].int_ == 0)
					type(q) = 0;
				if (type(q) == type(r))
					mem[q+2].int_ += mem[r+2].int_;
				else 
					if (type(q) < type(r) && mem[r+2].int_)
					{
						mem[q+2].int_ = mem[r+2].int_;
						type(q) = type(r);
					}
				if (mem[q+3].int_ == 0)
					subtype(q) = 0;
				if (subtype(q) == subtype(r))
					mem[q+3].int_ += mem[r+3].int_;
				else 
					if (subtype(q) < subtype(r) && mem[r+3].int_)
					{
						mem[q+3].int_ = mem[r+3].int_;
						subtype(q) = subtype(r);
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
					curval = multandadd(eqtb[l].int_, curval, 0, 0x7F'FF'FF'FF);
				else
					curval = multandadd(eqtb[l].int_, curval, 0, 0x3F'FF'FF'FF);
			else
				curval = xovern(eqtb[l].int_, curval);
		else
		{
			s = equiv(l);
			r = newspec(s);
			if (q == multiply)
				for (int i = 1; i <= 3; i++)
					mem[r+i].int_ = multandadd(mem[s+i].int_, curval, 0, 0x3F'FF'FF'FF);
			else
				for (int i = 1; i <= 3; i++)
					mem[r+i].int_ = xovern(mem[s+i].int_, curval);
			curval = r;
		}
	}
	if (aritherror)
	{
		if (interaction == 3)
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
