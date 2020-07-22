#include "mathac.h"
#include "impression.h"
#include "erreur.h"
#include "noeud.h"
#include "lecture.h"
#include "texte.h"

void mathac(eightbits cmd)
{
	if (cmd == accent)
		error("Please use "+esc("mathaccent")+" for accents in math mode", "I'm changing \\accent to \\mathaccent here; wish me luck.\n(Accents are not the same in formulas as they are in text.)");
	tail_append(getnode(accent_noad_size));
	type(tail) = accent_noad;
	subtype(tail) = normal;
	mem[nucleus(tail)].hh = twohalves{0, 0};
	mem[subscr(tail)].hh = twohalves{0, 0};
	mem[supscr(tail)].hh = twohalves{0, 0};
	math_type(accent_chr(tail)) = math_char;
	int val = scanfifteenbitint();
	character(accent_chr(tail)) = val%0x1'00;
	if (val >= var_code && fam_in_range())
		fam(accent_chr(tail)) = cur_fam();
	else
		fam(accent_chr(tail)) = (val>>8)%0x10;
	scanmath(nucleus(tail));
}
