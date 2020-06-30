#include "fetch.h"
#include "impression.h"
#include "error.h"
#include "charwarning.h"
#include "texte.h"
#include "primitive.h"

void fetch(halfword a)
{
	curc = subtype(a);
	curf = fam_fnt(type(a)+cursize);
	if (curf == null_font)
	{
		print_err(esc(primName[def_family][cursize])+" "+std::to_string(type(a))+" is undefined (character "+char(curc)+")");
		helpptr = 4;
		helpline[3] = "Somewhere in the math formula just ended, you used the";
		helpline[2] = "stated character from an undefined font family. For example,";
		helpline[1] = "plain TeX doesn't allow \\it or \\sl in subscripts. Proceed,";
		helpline[0] = "and I'll try to forget that I needed that character.";
		error();
		curi = nullcharacter;
		link(a) = 0;
	}
	else
	{
		if (curc >= fontbc[curf] && curc <= fontec[curf])
			curi = char_info(curf, curc);
		else
			curi = nullcharacter;
		if (skip_byte(curi) <= 0)
		{
			charwarning(curf, curc);
			link(a) = 0;
		}
	}
}
