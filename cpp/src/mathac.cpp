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
	auto n = new /*Accent*/Noad;
	n->type = accent_noad;
	n->subtype = normal;
	n->nucleus.math_type = 0; // twohalves{0, 0};
	n->subscr.math_type = 0; // = twohalves{0, 0};
	n->supscr.math_type = 0; // = twohalves{0, 0};
	math_type(accent_chr(tail->num)) = math_char;
	tail_append(n);
	int val = scanfifteenbitint();
	character(accent_chr(tail->num)) = val%0x1'00;
	if (val >= var_code && fam_in_range())
		fam(accent_chr(tail->num)) = cur_fam();
	else
		fam(accent_chr(tail->num)) = (val>>8)%0x10;
	scanmath(nucleus(tail->num));
}
