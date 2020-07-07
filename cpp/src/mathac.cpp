#include "mathac.h"
#include "impression.h"
#include "erreur.h"
#include "getnode.h"
#include "lecture.h"
#include "texte.h"

void mathac(void)
{
	if (curcmd == accent)
		error("Please use "+esc("mathaccent")+" for accents in math mode", "I'm changing \\accent to \\mathaccent here; wish me luck.\n(Accents are not the same in formulas as they are in text.)");
	tail_append(getnode(accent_noad_size));
	type(tail) = accent_noad;
	subtype(tail) = normal;
	mem[nucleus(tail)].hh = emptyfield;
	mem[subscr(tail)].hh = emptyfield;
	mem[supscr(tail)].hh = emptyfield;
	math_type(accent_chr(tail)) = math_char;
	curval = scanfifteenbitint();
	character(accent_chr(tail)) = curval%0x1'00;
	if (curval >= var_code && fam_in_range())
		fam(accent_chr(tail)) = cur_fam();
	else
		fam(accent_chr(tail)) = (curval>>8)%0x10;
	scanmath(nucleus(tail));
}
