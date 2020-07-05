#include "scanfontident.h"
#include "getxtoken.h"
#include "scanfourbitint.h"
#include "impression.h"
#include "erreur.h"
#include "texte.h"

static void erreurScanfontident(void)
{
	print_err("Missing font identifier");
	helpptr = 2;
	helpline[1] = "I was looking for a control sequence whose";
	helpline[0] = "current meaning has been defined by \\font.";
	backerror();
}

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
				erreurScanfontident();
				f = null_font;
			}
	curval = f;
}
