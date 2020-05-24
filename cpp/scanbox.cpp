#include "scanbox.h"
#include "getxtoken.h"
#include "beginbox.h"
#include "boxend.h"
#include "printnl.h"
#include "print.h"
#include "backerror.h"
#include "scanrulespec.h"
#include "texte.h"

void scanbox(int boxcontext)
{
	do
		getxtoken();
	while (curcmd == spacer || curcmd == escape);
	if (curcmd == make_box)
		beginbox(boxcontext);
	else 
		if (boxcontext > 0x40'00'02'00 && (curcmd == hrule || curcmd == vrule))
		{
			curbox = scanrulespec();
			boxend(boxcontext);
		}
		else
		{
			printnl("! ");
			print("A <box> was supposed to be here");
			helpptr = 3;
			helpline[2] = "I was expecting to see \\hbox or \\vbox or \\copy or \\box or";
			helpline[1] = "something like that. So you might find something missing in";
			helpline[0] = "your output. But keep trying; you can fix this later.";
			backerror();
		}
}
