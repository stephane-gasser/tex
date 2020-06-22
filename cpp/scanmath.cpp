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
				c = curval>>12;
				break;
			default:
				backinput();
				scanleftbrace();
				savestack[saveptr++].int_ = p;
				pushmath(math_group);
				return;
		}
	} while (label21);
	math_type(p) = math_char;
	character(p) = c%0x1'00;
	if (c >= var_code && fam_in_range())
		fam(p) = cur_fam();
	else
		fam(p) = (c>>8)%0x10;
}
