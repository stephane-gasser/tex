#include "scanmath.h"
#include "getxtoken.h"
#include "xtoken.h"
#include "backinput.h"
#include "scancharnum.h"
#include "scanfifteenbitint.h"
#include "scantwentysevenbitint.h"
#include "backinput.h"
#include "scanleftbrace.h"
#include "pushmath.h"

void scanmath(halfword p)
{
	do
		getxtoken();
	while (curcmd == spacer || curcmd == escape);
	bool label21;
	do
	{
		label21 = false;
		int c;
		switch (curcmd)
		{
			case letter:
			case other_char:
			case char_given:
				c = math_code(curchr);
				if (c == 0x80'00)
				{
					curcs = curchr+1;
					curcmd = eq_type(curcs);
					curchr = equiv(curcs);
					xtoken();
					backinput();
					do
						getxtoken();
					while (curcmd == spacer || curcmd == escape);
					label21 = true;
					continue;
				}
				break;
			case char_num:
				scancharnum();
				curchr = curval;
				curcmd = char_given;
				label21 = true;
				continue;
			case math_char_num:
				scanfifteenbitint();
				c = curval;
				break;
			case math_given: 
				c = curchr;
				break;
			case delim_num:
				scantwentysevenbitint();
				c = curval/0x10'00;
				break;
			default:
				backinput();
				scanleftbrace();
				savestack[saveptr++].int_ = p;
				pushmath(9);
				return;
		}
	} while (label21);
	link(p) = 1;
	subtype(p) = c%0x1'00;
	if (c >= 0x7000 && int_par(cur_fam_code) >= 0 && int_par(cur_fam_code) < 0x10)
		type(p) = int_par(cur_fam_code);
	else
		type(p) = (c/0x1'00)%0x10;
}
