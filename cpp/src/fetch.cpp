#include "fetch.h"
#include "impression.h"
#include "erreur.h"
#include "charwarning.h"
#include "texte.h"
#include "primitive.h"

void fetch(halfword a)
{
	curc = subtype(a);
	curf = fam_fnt(type(a)+cursize);
	if (curf == null_font)
	{
		error(esc(primName[def_family][cursize])+" "+std::to_string(type(a))+" is undefined (character "+char(curc)+")", "Somewhere in the math formula just ended, you used the\nstated character from an undefined font family. For example,\nplain TeX doesn't allow \\it or \\sl in subscripts. Proceed,\nand I'll try to forget that I needed that character.");
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