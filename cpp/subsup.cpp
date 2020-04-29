#include "subsup.h"
#include "newnoad.h"
#include "printnl.h"
#include "print.h"
#include "error.h"
#include "scanmath.h"

void subsup(void)
{
	smallnumber t = 0;
	halfword p = 0;
	if (curlist.tailfield != curlist.headfield)
		if (type(curlist.tailfield) >= 16 && type(curlist.tailfield) < 30)
		{
			p = curlist.tailfield+2+curcmd-7;
			t = link(p);
		}
	if (p == 0 || t)
	{
		link(curlist.tailfield) = newnoad();
		curlist.tailfield = link(curlist.tailfield);
		p = curlist.tailfield+2+curcmd-7;
		if (t)
		{
			if (curcmd == 7)
			{
				if (interaction == 3)
					printnl(262); //! 
				print(1142); //Double superscript
				helpptr = 1;
				helpline[0] = 1143; //I treat `x^1^2' essentially like `x^1{}^2'.
			}
			else
			{
				if (interaction == 3)
					printnl(262); //! 
				print(1144); //Double subscript
				helpptr = 1;
				helpline[0] = 1145; //I treat `x_1_2' essentially like `x_1{}_2'.
			}
			error();
		}
	}
	scanmath(p);
}
