#include "headforvmode.h"
#include "offsave.h"
#include "printnl.h"
#include "printesc.h"
#include "print.h"
#include "error.h"
#include "backinput.h"

void headforvmode(void)
{
	if (mode < 0)
		if (curcmd != hrule)
			offsave();
		else
		{
			if (interaction == 3)
				printnl(262); //! 
			print(685); //You can't use `
			printesc(521); //hrule
			print(1081); //' here except with leaders
			helpptr = 2;
			helpline[1] = 1082; //To put a horizontal rule in an hbox or an alignment,
			helpline[0] = 1083; //you should use \leaders or \hrulefill (see The TeXbook).
			error();
		}
	else
	{
		backinput();
		curtok = partoken;
		backinput();
		curinput.indexfield = 4;
	}
}
