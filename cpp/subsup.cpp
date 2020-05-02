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
	if (tail != head)
		if (type(tail) >= 16 && type(tail) < 30)
		{
			p = tail+2+curcmd-sup_mark;
			t = link(p);
		}
	if (p == 0 || t)
	{
		tail_append(newnoad());
		p = tail+2+curcmd-sup_mark;
		if (t)
		{
			if (curcmd == sup_mark)
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
