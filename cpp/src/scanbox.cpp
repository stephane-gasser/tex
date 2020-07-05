#include "scanbox.h"
#include "getxtoken.h"
#include "beginbox.h"
#include "boxend.h"
#include "impression.h"
#include "erreur.h"
#include "scanrulespec.h"
#include "texte.h"

static void erreurScanbox(void)
{
	print_err("A <box> was supposed to be here");
	helpptr = 3;
	helpline[2] = "I was expecting to see \\hbox or \\vbox or \\copy or \\box or";
	helpline[1] = "something like that. So you might find something missing in";
	helpline[0] = "your output. But keep trying; you can fix this later.";
	backerror();
}

void scanbox(int boxcontext)
{
	do
		getxtoken();
	while (curcmd == spacer || curcmd == escape);
	if (curcmd == make_box)
		beginbox(boxcontext);
	else 
		if (boxcontext > leader_flag && (curcmd == hrule || curcmd == vrule))
		{
			curbox = scanrulespec();
			boxend(boxcontext);
		}
		else
			erreurScanbox();
}
