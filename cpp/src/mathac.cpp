#include "mathac.h"
#include "impression.h"
#include "erreur.h"
#include "noeud.h"
#include "lecture.h"
#include "equivalent.h"

void mathac(eightbits cmd)
{
	if (cmd == accent)
		error("Please use "+esc("mathaccent")+" for accents in math mode", "I'm changing \\accent to \\mathaccent here; wish me luck.\n(Accents are not the same in formulas as they are in text.)");
	auto n = new AccentNoad;
	n->subtype = normal;
	n->nucleus.math_type = 0; // twohalves{0, 0};
	n->subscr.math_type = 0; // = twohalves{0, 0};
	n->supscr.math_type = 0; // = twohalves{0, 0};
	int val = scanfifteenbitint();
	n->accent_chr.character = val%0x1'00;
	if (val >= var_code && fam_in_range())
		n->accent_chr.fam = cur_fam();
	else
		n->accent_chr.fam = (val>>8)%0x10;
	scanmath(n->nucleus);
	tail_append(n);	
}
