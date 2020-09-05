#include "fetch.h"
#include "impression.h"
#include "erreur.h"
#include "charwarning.h"
#include "primitive.h"
#include "formule.h"

[[nodiscard]] std::tuple<Font, quarterword> fetch(NoadContent &a)
{
	auto curc = a.character;
	auto curf = fam_fnt(a.fam+cursize);
	auto &ft = fonts[curf];
	try
	{
		if (curf == null_font)
			throw 1;
		if (curc < ft.bc || curc > ft.ec)
			throw 0;
		if (!char_exists(ft.char_info(curc)))
			throw 0;
	}
	catch (int e)
	{
		if (e == 1)
			error(esc(primName[def_family][cursize])+" "+std::to_string(a.fam)+" is undefined (character "+char(curc)+")", "Somewhere in the math formula just ended, you used the\nstated character from an undefined font family. For example,\nplain TeX doesn't allow \\it or \\sl in subscripts. Proceed,\nand I'll try to forget that I needed that character.");
		else
			charwarning(ft, curc);
		a.fam = 0;
		a.character = 0;
	}
	return std::tuple(ft, curc);
}
