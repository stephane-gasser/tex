#include "scanfontident.h"
#include "getxtoken.h"
#include "scanfourbitint.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

void scanfontident(void)
{
	do
		getxtoken();
	while (curcmd == spacer);
	internalfontnumber f;
	if (curcmd == def_font)
		f = cur_font();
	else 
		if (curcmd == set_font)
			f = curchr;
		else 
			if (curcmd == def_family)
			{
				halfword m = curchr;
				scanfourbitint();
				f = equiv(m+curval);
			}
			else
			{
				backerror("Missing font identifier", "I was looking for a control sequence whose\ncurrent meaning has been defined by \\font.");
				f = null_font;
			}
	curval = f;
}
