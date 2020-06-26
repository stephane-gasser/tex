#include "mathac.h"
#include "impression.h"
#include "error.h"
#include "getnode.h"
#include "scanfifteenbitint.h"
#include "scanmath.h"
#include "texte.h"

void mathac(void)
{
	if (curcmd == accent)
	{
		print_err("Please use "+esc("mathaccent")+" for accents in math mode");
		helpptr = 2;
		helpline[1] = "I'm changing \\accent to \\mathaccent here; wish me luck.";
		helpline[0] = "(Accents are not the same in formulas as they are in text.)";
		error();
	}
	tail_append(getnode(accent_noad_size));
	type(tail) = accent_noad;
	subtype(tail) = normal;
	mem[nucleus(tail)].hh = emptyfield;
	mem[subscr(tail)].hh = emptyfield;
	mem[supscr(tail)].hh = emptyfield;
	math_type(accent_chr(tail)) = math_char;
	scanfifteenbitint();
	character(accent_chr(tail)) = curval%0x1'00;
	if (curval >= var_code && fam_in_range())
		fam(accent_chr(tail)) = cur_fam();
	else
		fam(accent_chr(tail)) = (curval>>8)%0x10;
	scanmath(nucleus(tail));
}
