#include "scandelimiter.h"
#include "scantwentysevenbitint.h"
#include "getxtoken.h"
#include "impression.h"
#include "backerror.h"
#include "texte.h"

void scandelimiter(halfword p, bool r)
{
	if (r)
		scantwentysevenbitint();
	else
	{
		do
			getxtoken();
		while (curcmd == spacer || curcmd == escape);
		switch (curcmd)
		{
			case letter:
			case other_char: 
				curval = del_code(curchr);
				break;
			case delim_num: 
				scantwentysevenbitint();
				break;
			default: 
				curval = -1;
		}
	}
	if (curval < 0)
	{
		print_err("Missing delimiter (. inserted)");
		helpptr = 6;
		helpline[5] = "I was expecting to see something like `(' or `\\{' or";
		helpline[4] = "`\\}' here. If you typed, e.g., `{' instead of `\\{', you";
		helpline[3] = "should probably delete the `{' by typing `1' now, so that";
		helpline[2] = "braces don't get unbalanced. Otherwise just proceed.";
		helpline[1] = "Acceptable delimiters are characters whose \\delcode is";
		helpline[0] = "nonnegative, or you can use `\\delimiter <delimiter code>'.";
		backerror();
		curval = 0;
	}
	;
	mem[p].qqqq.b0 = (curval/0x10'00'00)%0x10;
	mem[p].qqqq.b1 = (curval/0x10'00)%0x1'00;
	mem[p].qqqq.b2 = (curval/0x1'00)%0x10;
	mem[p].qqqq.b3 = curval%0x1'00;
}
