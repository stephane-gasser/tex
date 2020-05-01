#include "scandelimiter.h"
#include "scantwentysevenbitint.h"
#include "getxtoken.h"
#include "printnl.h"
#include "print.h"
#include "backerror.h"

void scandelimiter(halfword p, bool r)
{
	if (r)
		scantwentysevenbitint();
	else
	{
		do
			getxtoken();
		while (curcmd == 10 || curcmd == 0);
		switch (curcmd)
		{
			case 11:
			case 12: 
				curval = del_code(curchr);
				break;
			case 15: 
				scantwentysevenbitint();
				break;
			default: 
				curval = -1;
		}
	}
	if (curval < 0)
	{
		if (interaction == 3)
			printnl(262); //! 
		print(1131); //Missing delimiter (. inserted)
		helpptr = 6;
		helpline[5] = 1132; //I was expecting to see something like `(' or `\{' or
		helpline[4] = 1133; //`\}' here. If you typed, e.g., `{' instead of `\{', you
		helpline[3] = 1134; //should probably delete the `{' by typing `1' now, so that
		helpline[2] = 1135; //braces don't get unbalanced. Otherwise just proceed.
		helpline[1] = 1136; //Acceptable delimiters are characters whose \delcode is
		helpline[0] = 1137; //nonnegative, or you can use `\delimiter <delimiter code>'.
		backerror();
		curval = 0;
	}
	;
	mem[p].qqqq.b0 = (curval/1048576)%16;
	mem[p].qqqq.b1 = (curval/4096)%256;
	mem[p].qqqq.b2 = (curval/256)%16;
	mem[p].qqqq.b3 = curval%256;
}
