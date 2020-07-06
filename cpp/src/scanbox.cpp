#include "scanbox.h"
#include "getxtoken.h"
#include "beginbox.h"
#include "boxend.h"
#include "impression.h"
#include "erreur.h"
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
		if (boxcontext > leader_flag && (curcmd == hrule || curcmd == vrule))
		{
			curbox = scanrulespec();
			boxend(boxcontext);
		}
		else
			backerror("A <box> was supposed to be here", "I was expecting to see \\hbox or \\vbox or \\copy or \\box or\nsomething like that. So you might find something missing in\nyour output. But keep trying; you can fix this later.");
}
