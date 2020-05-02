#include "mathac.h"
#include "printnl.h"
#include "print.h"
#include "printesc.h"
#include "error.h"
#include "getnode.h"
#include "scanfifteenbitint.h"
#include "scanmath.h"

void mathac(void)
{
	if (curcmd == accent)
	{
		if (interaction == 3)
			printnl(262); //! 
		print(1138); //Please use 
		printesc(523); //mathaccent
		print(1139); // for accents in math mode
		helpptr = 2;
		helpline[1] = 1140; //I'm changing \accent to \mathaccent here; wish me luck.
		helpline[0] = 1141; //(Accents are not the same in formulas as they are in text.)
		error();
	}
	tail_append(getnode(5));
	type(tail) = 28;
	subtype(tail) = 0;
	mem[tail+1].hh = emptyfield;
	mem[tail+3].hh = emptyfield;
	mem[tail+2].hh = emptyfield;
	link(tail+4) = 1;
	scanfifteenbitint();
	subtype(tail+4) = curval%0x1'00;
	if (curval >= 0x7000 && int_par(cur_fam_code) >= 0 && int_par(cur_fam_code) < 0x10)
		type(tail+4) = int_par(cur_fam_code);
	else
		type(tail+4) = (curval/0x1'00)%0x10;
	scanmath(tail+1);
}
